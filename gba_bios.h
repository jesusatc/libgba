/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones BIOS de la GBA                                    */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_gba_h
#define gba_gba_h

#include "gba.h"

/*****************************************************************************/

/*
 * Constantes para crear la máscara de bits de gba_register_ram_reset.
 */
#define RESET_EWRAM    (1 << 0) /* No usar cuando se retorna a WRAM */
#define RESET_IWRAM    (1 << 1) /* Excluye los últimos 0x200 bytes */
#define RESET_PALETTE  (1 << 2)
#define RESET_VRAM     (1 << 3)
#define RESET_OAM      (1 << 4) /* La rellena con ceros: no oculta los sprites */
#define RESET_SIO      (1 << 5) /* Se cambia al modo de propósito general */
#define RESET_SOUND    (1 << 6)
#define RESET_REMAINIG (1 << 7) /* Resto de los registros (menos SIO y sonido) */

/*****************************************************************************/

/*
 * Función 0x00:
 * Soft reset.
 *  - Limpia la zona de IWRAM desde 0x03007e00-0x03007fff
 *  - Inicializa r0-r12 a cero
 *  - Inicializa los punteros de pila de los modos USER, SVC e IRQ
 *  - Cambia al modo de ejecución USER
 *  - Salta a la dirección 0x08000000 o 0x02000000 dependiendo del contenido
 *    de RETURN_ADDRESS_SEL (0x03007ffa):
 *      - 0x00: Salta a la 0x08000000 (defecto)
 *      - otro: Salta a la dirección 0x02000000
 */
extern void gba_soft_reset(void);

/*****************************************************************************/

/*
 * Función 0x01:
 * Register RAM reset.
 *  - Limpia los registros de E/S y las zonas de memoria especificadas en la
 *    máscara de bits flags.
 *  - El área comprendida entre 0x3007E00-0x3007FFF se se altera.
 *
 * @param flags: Máscara formada con las constantes RESET_X
 *
 * Bugs:
 * - Los LSBs de SIODATA siempre se destruyen, aunque no se fije el bit 5
 * - Siempre pone la pantalla en blanco porque se inicializa DISPCNT a 0x0080
 */
extern void gba_register_ram_reset(int flags);

/*****************************************************************************/

/*
 * Función 0x02:
 * Halt.
 *  - Cambia la CPU al modo de bajo consumo, pero el resto de circuitos
 *    (video, sonido, serie, etc.) siguen funcionando.
 *  - Se sale de este modo cuando se produce una IRQ (deben estar habilitadas)
 */
extern void gba_halt(void);

/*****************************************************************************/

/*
 * Función 0x03:
 * Stop.
 *
 * - Cambia la GBA al modo de muy bajo consumo. Se detiene la CPU, el reloj,
 *   el sonido, el vídeo el reloj del SIO, los DMAs y temporizadores
 * - Sólo se sale de este estado si se recibe una interrupción del teclado,
 *   el cartucho, o el puerto serie
 * - Preparación antes de llamara la función stop:
 *     - Hay que deshabilitar el vídeo. De no hacerlo, se congela la imagen,
 *       pero se sigue gastando batería
 */
extern void gba_stop(void);

/*****************************************************************************/

/*
 * Función 0x06:
 * División entera.
 * Retorna la parte entera de la división.
 * @param numerator   Numerador   (32 bits con signo)
 * @param denominator Denominador (32 bits con signo)
 */
extern int gba_div(int numerator, int denominator);

/*****************************************************************************/

/*
 * Función 0x06:
 * Resto de la división entera.
 * Retorna el resto de la división.
 * @param numerator   Numerador   (32 bits con signo)
 * @param denominator Denominador (32 bits con signo)
 */
extern int gba_mod(int numerator, int denominator);

/*****************************************************************************/

/*
 * Función 0x06:
 * División entera.
 * Retorna el valor absoluto de la parte entera de la división.
 * @param numerator   Numerador   (32 bits con signo)
 * @param denominator Denominador (32 bits con signo)
 */
extern int gba_abs_div(int numerator, int denominator);

/*****************************************************************************/

/*
 * Función 0x08:
 * Raiz cuadrada.
 * @param val Valor (32 bits sin signo)
 * @return La raiz cuadrada de val (16 bits sin signo). El resultado es entero.
 *         Se aconseja desplazar el valor a la izquierda 2*N bits para obtener
 *         el resultado N bits desplazado a la izquierda.
 */          
extern u_int gba_sqrt(u_int val);

/*****************************************************************************/

/*
 * Función 0xff:
 * Imprime una cadena de caracteres en la consola del depurador. Sólo funciona
 * en el simulador Visualboy Advance, si se realiza en la consola, la deja
 * colgada.
 * @param str  Puntero a la cadena
 */
extern void gba_vba_print(const char *str);

/*****************************************************************************/

#endif /* gba_gba_h */
