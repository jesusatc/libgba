@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Sistemas operativos empotrados                                              @
@                                                                             @
@ Segundo ejemplo: El "hola mundo" en la GBA en C                             @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Constantes                                                                  @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               .include "arm.inc"

             @ Relleno para las pilas (para detectar desbordamientos)
               .set RELLENO_PILA,     0xcadacafe

             @ Flags de interrupción
               .set IRQ_VBLANK,       (1 << 0)
               .set IRQ_HBLANK,       (1 << 1)
               .set IRQ_VCOUNT,       (1 << 2)
               .set IRQ_TIMER0,       (1 << 3)
               .set IRQ_TIMER1,       (1 << 4)
               .set IRQ_TIMER2,       (1 << 5)
               .set IRQ_TIMER3,       (1 << 6)
               .set IRQ_SERIAL,       (1 << 7)
               .set IRQ_DMA0,         (1 << 8)
               .set IRQ_DMA1,         (1 << 9)
               .set IRQ_DMA2,         (1 << 10)
               .set IRQ_DMA3,         (1 << 11)
               .set IRQ_KEYPAD,       (1 << 12)
               .set IRQ_CART,         (1 << 13)


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Se usará el repertorio de instrucciones de 32 bits                          @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

             @ Creamos una nueva sección para indicarle al script del linker
             @ que la coloque al principio de la ROM
               .section .boot

             @ El código de arranque debe ser de 32 bits
               .code 32

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Punto de entrada                                                            @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               .globl inicio
inicio:


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Incluimos la cabecera del cartucho                                          @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               .include "cabecera.inc"   


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Copiamos el código de procesamiento de interrupciones a la IWRAM.           @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               ldr     r1, =__inicio_intr__
               ldr     r2, =__fin_intr__
               ldr     r3, =__inicio_intr_rom__
               bl      copiar


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Inicializamos las pilas                                                     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               ldr     r1, =__fondo_pila_user__
               ldr     r2, =__tope_pila_svc__
               ldr     r3, =RELLENO_PILA
               bl      inicializar


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Inicializamos los punteros de pila para cada modo                           @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

             @ Cambiamos al modo IRQ
             @ Deshabilitamos las interrupciones IRQ y FIQ en este modo
               msr     CPSR_c, #(ARM_MODE_IRQ | ARM_I_BIT | ARM_F_BIT)

             @ Inicializamos el puntero de pila
               ldr     sp, =__tope_pila_irq__


             @ Cambiamos al modo supervisor
             @ Deshabilitamos las interrupciones IRQ y FIQ en este modo
               msr     CPSR_c, #(ARM_MODE_SVC | ARM_I_BIT | ARM_F_BIT)

             @ Inicializamos el puntero de pila
               ldr     sp, =__tope_pila_svc__


             @ Cambiamos al modo usuario (el que se quedará partir de ahora)
             @ Deshabilitamos las interrupciones FIQ (no se usan en la GBA)
               msr     CPSR_c, #(ARM_MODE_USER | ARM_F_BIT)
 
             @ Inicializamos el puntero de pila
               ldr     sp, =__tope_pila_user__

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Preparamos el soporte de las interrupciones                                 @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

             @ Cuando se produzca uan interrupción, la GBA salta a la dirección
             @ que esté almacenada en IRQ_HANDLER (0x03007ffc), por tanto,
             @ almacenanos en esta dirección la rutina de atención a las
             @ interrupciones (definida más abajo)
               ldr     r1, =gba_intr_handler_address
               ldr     r0, =intr_main
               str     r0, [r1]


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Copiamos las variables inicializadas de su dirección LMA a la VMA.          @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               ldr     r1, =__inicio_datos__
               ldr     r2, =__fin_datos__
               ldr     r3, =__inicio_datos_rom__
               bl      copiar

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Fijamos a 0 la memoria RAM reservada para las variables sin inicializar.    @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               ldr     r1, =__inicio_bss__
               ldr     r2, =__fin_bss__
               ldr     r3, =0
               bl      inicializar

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Empieza el código en C                                                      @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               ldr     r0, =main         @ Llamamos a la funcion main
               bx      r0                @ Llamamos a la funcion main
               b       .                 @ Colgamos el sistema si main retorna


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Funciones auxiliares                                                        @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

             @ Las colocamos en la sección de código
               .section .text

             @ De momento usamos código de 32 bits
               .code 32

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Rutina para copiar código o datos de la memoria ROM a la RAM                @
@ Parámetros:                                                                 @
@   r1: Puntero a la posición inicial en la memoria RAM                       @
@   r2: Puntero a la posición final en la memoria RAM                         @
@   r3: Puntero a la posición inicial en la memoria ROM                       @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

copiar:        cmp     r1, r2
               bge     copia_hecha
               ldrb    r4, [r3], #+1
               strb    r4, [r1], #+1
               b       copiar
               
copia_hecha:   mov     pc, lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Rutina para inicializar una zona de memoria RAM a un valor fijo             @
@ Parámetros:                                                                 @
@   r1: Puntero a la posición inicial en la memoria RAM                       @
@   r2: Puntero a la posición final en la memoria RAM                         @
@   r3: Valor para la inicialización                                          @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

inicializar:   cmp     r1, r2
               strne   r3, [r1], #+4
               bne     inicializar

               mov     pc, lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Procesamiento de interrupciones                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

             @ Creamos una nueva sección (.intr), que alojeremos en el script
             @ del linker en la memoria iwram para que su procesamiento sea
             @ rápido
               .section .intr, "ax", %progbits

             @ El código debe ser de 32 bits
               .code 32

             @ Vectores de interrupción
intr_vectors:
vblank_vec:    .word   vblank_handler
hblank_vec:    .word   hblank_handler
vcount_vec:    .word   vcount_handler
timer0_vec:    .word   timer0_handler
timer1_vec:    .word   timer1_handler
timer2_vec:    .word   timer2_handler
timer3_vec:    .word   timer3_handler
serial_vec:    .word   serial_handler
dma0_vec:      .word   dma0_handler
dma1_vec:      .word   dma1_handler
dma2_vec:      .word   dma2_handler
dma3_vec:      .word   dma3_handler
keypad_vec:    .word   keypad_handler
cart_vec:      .word   cart_handler

             @ Manejadores de interrupión por defecto
vblank_handler:b       .
hblank_handler:b       .
vcount_handler:b       .
timer0_handler:b       .
timer1_handler:b       .
timer2_handler:b       .
timer3_handler:b       .
serial_handler:b       .
dma0_handler:  b       .
dma1_handler:  b       .
dma2_handler:  b       .
dma3_handler:  b       .
keypad_handler:b       .
cart_handler:  b       .

             @ Tabla de vectores de interrupción
               .globl gba_irq_handler_table
gba_irq_handler_table: .word intr_vectors

             @ Manejador principal de interrupciones. Es llamado directamente
             @ por el controlador de interrupciones, detecta el origen de la
             @ interrupción y llama al manejador apropiado.

             @ Esta rutina no permite manejar múltiples interrupciones
             @ anidadas. Si fuera necesario, se puede cambiar por la que
             @ propone Jeff Frohwein (http://www.devrs.com)
intr_main:
               ldr     r3, =gba_ioregs
               ldr     r2, [r3,#0x200]!         @ r2 = (IF,IE)
               and     r1, r2, r2, lsr #16      @ r1 = IE & IF

             @ Comprobamos la interrupción del periodo V-Blank
               ldr     r2, =vblank_vec
               ands    r0, r1, #IRQ_VBLANK
               bne     jump_intr

             @ Comprobamos la interrupción del periodo H-Blank
               ldr     r2, =hblank_vec
               ands    r0, r1, #IRQ_HBLANK
               bne     jump_intr

             @ Comprobamos la interrupción del contador de líneas
               ldr     r2, =vcount_vec
               ands    r0, r1, #IRQ_VCOUNT
               bne     jump_intr

             @ Comprobamos la interrupción del Timer0
               ldr     r2, =timer0_vec
               ands    r0, r1, #IRQ_TIMER0
               bne     jump_intr

             @ Comprobamos la interrupción del Timer1
               ldr     r2, =timer1_vec
               ands    r0, r1, #IRQ_TIMER1
               bne     jump_intr

             @ Comprobamos la interrupción del Timer2
               ldr     r2, =timer2_vec
               ands    r0, r1, #IRQ_TIMER2
               bne     jump_intr

             @ Comprobamos la interrupción del Timer3
               ldr     r2, =timer3_vec
               ands    r0, r1, #IRQ_TIMER3
               bne     jump_intr

             @ Comprobamos la interrupción del puerto serie
               ldr     r2, =serial_vec
               ands    r0, r1, #IRQ_SERIAL
               bne     jump_intr

             @ Comprobamos la interrupción del DMA0
               ldr     r2, =dma0_vec
               ands    r0, r1, #IRQ_DMA0
               bne     jump_intr

             @ Comprobamos la interrupción del DMA1
               ldr     r2, =dma1_vec
               ands    r0, r1, #IRQ_DMA1
               bne     jump_intr

             @ Comprobamos la interrupción del DMA2
               ldr     r2, =dma2_vec
               ands    r0, r1, #IRQ_DMA2
               bne     jump_intr

             @ Comprobamos la interrupción del DMA3
               ldr     r2, =dma3_vec
               ands    r0, r1, #IRQ_DMA3
               bne     jump_intr

             @ Comprobamos la interrupción del teclado
               ldr     r2, =keypad_vec
               ands    r0, r1, #IRQ_KEYPAD
               bne     jump_intr

             @ Comprobamos la interrupción del cartucho
               ldr     r2, =cart_vec
               ands    r0, r1, #IRQ_CART

             @ Si se ha extraído el cartucho, detenemos el sonido y entramos
             @ en un bucle infinito
               strneb  r0, [r3, #0x84 - 0x200] @ (REG_SOUNDCNT_X)
               bne     .

jump_intr:     strh    r0, [r3, #2]            @ Reconocemos la interrupción
               ldr     r0, [r2]
               bx      r0                      @ Saltamos al manejador

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Fin                                                                         @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

               .end

