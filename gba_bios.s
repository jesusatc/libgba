@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Sistemas operativos empotrados                                              @
@                                                                             @
@ Biblioteca de funciones BIOS de la GBA                                      @
@                                                                             @
@ Las llamadas a la BIOS en este fichero están hechas en modo ARM             @
@ (desplazando el número de función 16 bits a la izquierda)                   @
@                                                                             @
@ La mayoría de las veces, es preferible usar la sentencia asm para           @
@ ejecutar ensamblador empotrado en C. Por ejemplo:                           @
@                                                                             @
@ asm volatile("mov r0, %3       \n\t"                                        @
@              "mov r1, %4       \n\t"                                        @
@              "swi (0x06 << 16) \n\t" /* modo ARM, en modo thumb 0x06 */     @
@              "mov %0, r0       \n\t"                                        @
@              "mov %1, r1       \n\t"                                        @
@              "mov %2, r3       \n\t"                                        @
@              : "=&r" (*quot), "=&r" (*remain), "=&r" (*abs_quot)            @
@              : "r" (num), "r" (denom)                                       @
@              : "r0", "r1", "r3")/;                                          @
@                                                                             @
@ El problema, es que dependiendo del modo (thumb, o ARM, serían necesarias   @
@ dos implementaciones, en thumb swi n y en ARM swi n<<16, para llamar a la   @
@ función n de la bios. Para evitar este problema, y aprovechando que el      @
@ AAPCS (ARM Architecture Procedure Call Standard) introduce los cuatro       @
@ primeros argumentos de entrada en r0-r3 (el resto en la pila) y los dos     @
@ primeros argumentos de salida en r0-r1, es más sencillo implementar las     @
@ llamadas a la bios directamente en ensamblador y definir un fichero .h para @
@ que se puedan llamar desde C.                                               @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ De momento vamos a implementar las funciones en modo ARM. El modo thumb     @
@ ahorra código, pero en cada llamada habría que hacer un cambio de modo,     @
@ poco adecuado para funciones codificadas en modo ARM críticas               @
@ (interrupciones). Además habría que compilar con la opción -mthumb-interwork@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               .code 32
               .section .text

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0x00:                                                               @
@ Soft reset.                                                                 @
@  - Limpia la zona de IWRAM desde 0x03007e00-0x03007fff                      @
@  - Inicializa r0-r12 a cero                                                 @
@  - Inicializa los punteros de pila de los modos USER, SVC e IRQ             @
@  - Cambia al modo de ejecución USER                                         @
@  - Salta a la dirección 0x08000000 o 0x02000000 dependiendo del contenido   @
@    de RETURN_ADDRESS_SEL (0x03007ffa):                                      @
@      * 0x00: Salta a la 0x08000000 (defecto)                                @
@      * otro: Salta a la dirección 0x02000000                                @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern void gba_soft_reset(void);
@
               .global gba_soft_reset
gba_soft_reset:
@            swi      (0x01 << 16)
            swi      (0x00 << 16)

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0x01:                                                               @
@ Register RAM reset.                                                         @
@  - Limpia los registros de E/S y las zonas de memoria especificadas en la   @
@    máscara de bits flags.                                                   @
@  - El área comprendida entre 0x3007E00-0x3007FFF se se altera.              @
@                                                                             @
@ Parámetros:                                                                 @
@  - r0: Flags que indican qué se resetea. Significado de cada bit:           @
@     0 Limpia los 256K de EWRAM (No usar cuando se retorna a WRAM)           @
@     1 Limpia los 32K de IWRAM (exclye los últimos 0x200 bytes)              @
@     2 Limpia la memoria de paleta                                           @
@     3 Limpia la VRAM                                                        @
@     4 Limpia la OAM (la rellena con ceros -> no oculta los sprites!!)       @
@     5 Limpia los registros SIO (se cambia al modo de propósito general)     @
@     6 Limpia los registros de sonido                                        @
@     7 Limpia el resto de registros (excepto SIO y sonido)                   @
@                                                                             @
@ Bugs:                                                                       @
@ - Los LSBs de SIODATA siempre se destruyen, aunque no se fije el bit 5      @
@ - Siempre pone la pantalla en blanco porque se inicializa DISPCNT a 0x0080  @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern void gba_register_ram_reset(int flags);
@
               .global gba_register_ram_reset
gba_register_ram_reset:
            swi      (0x01 << 16)
            bx       lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0x02:                                                               @
@ Halt.                                                                       @
@  - Cambia la CPU al modo de bajo consumo, pero el resto de circuitos        @
@    (video, sonido, serie, etc.) siguen funcionando.                         @
@  - Se sale de este modo cuando se produce una IRQ (deben estar habilitadas) @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern void gba_halt(void);
@
               .global gba_halt
gba_halt:
            swi      (0x02 << 16)
            bx       lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0x03:                                                               @
@ Stop.                                                                       @
@                                                                             @
@ - Cambia la GBA al modo de muy bajo consumo. Se detiene la CPU, el reloj,   @
@   el sonido, el vídeo el reloj del SIO, los DMAs y temporizadores           @
@ - Sólo se sale de este estado si se recibe una interrupción del teclado,    @
@   el cartucho, o el puerto serie                                            @
@ - Preparación antes de llamara la función stop:                             @
@     * Hay que deshabilitar el vídeo. De no hacerlo, se congela la imagen,   @
@       pero se sigue gastando batería                                        @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern void gba_stop(void);
@
               .global gba_stop
gba_stop:
            swi      (0x03 << 16)
            bx       lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0x06:                                                               @
@ División entera.                                                            @
@                                                                             @
@ Parámetros:                                                                 @
@  - r0: Numerador   (32 bits con signo)                                      @
@  - r1: Denominador (32 bits con signo)                                      @
@                                                                             @
@ Retorno:                                                                    @
@  - r0: Parte entera de la división (con signo)                              @
@  - r1: Resto de la división (con signo)                                     @
@  - r3: Valor absoluto de la parte entera de la división (con signo)         @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern int gba_div(int numerator, int denominator);
@
               .global gba_div
gba_div:
            swi      (0x06 << 16)
            bx       lr

@
@ extern int gba_mod(int numerator, int denominator);
@
               .global gba_mod
gba_mod:
            swi      (0x06 << 16)
            mov      r0, r1
            bx       lr

@
@ extern int gba_abs_div(int numerator, int denominator);
@
               .global gba_abs_div
gba_abs_div:
            swi      (0x06 << 16)
            mov      r0, r3
            bx       lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0x07:                                                               @
@ División entera (formato ARM).                                              @
@                                                                             @
@ Parámetros:                                                                 @
@  - r0: Denominador (32 bits con signo)                                      @
@  - r1: Numerador   (32 bits con signo)                                      @
@                                                                             @
@ Retorno:                                                                    @
@  - r0: Parte entera de la división (con signo)                              @
@  - r1: Resto de la división (con signo)                                     @
@  - r3: Valor absoluto de la parte entera de la división (con signo)         @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern int gba_arm_div(int denominator, int numerator);
@
               .global gba_arm_div
gba_arm_div:
            swi      (0x07 << 16)
            bx       lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0x08:                                                               @
@ Raiz cuadrada.                                                              @
@                                                                             @
@ Parámetros:                                                                 @
@  - r0: Valor (32 bits sin signo)                                            @
@                                                                             @
@ Retorno:                                                                    @
@  - r0: Resultado (16 bits sin signo)                                        @
@                                                                             @
@ Notas:                                                                      @
@  - El resultado es entero. Se aconseja desplazar el valor a la izquierda    @
@    2*N bits para obtener el resultado N bits desplazado a la izquierda      @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern u_int gba_sqrt(u_int val);
@
               .global gba_sqrt
gba_sqrt:
            swi      (0x08 << 16)
            bx       lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Función 0xff:                                                               @
@ Imprime una cadena de caracteres en la consola del depurador.               @
@                                                                             @
@ Parámetros:                                                                 @
@  - r0:       Puntero a la cadena                                            @
@                                                                             @
@ Notas:                                                                      @
@  - Sólo funciona en el simulador Visualboy Advance, si se realiza en la     @
@    consola, la deja colgada                                                 @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@
@ extern void gba_vba_print(const char *str);
@
               .global gba_vba_print
gba_vba_print:
            swi      (0xff << 16)
            bx       lr

