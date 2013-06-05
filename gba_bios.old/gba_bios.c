/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones BIOS de la GBA                                    */
/*                                                                           */
/* Las llamadas a la BIOS en este fichero están hechas en modo ARM           */
/* (desplazando el número de función 16 bits a la izquierda)                 */
/*                                                                           */
/*****************************************************************************/

#include "gba_bios.h"

/*****************************************************************************/

/*
 * Función 0x00:
 * Soft reset.
 *   - Limpia la zona de IWRAM desde 0x03007e00-0x03007fff
 *   - Inicializa r0-r12 a cero
 *   - Inicializa los punteros de pila de los modos USER, SVC e IRQ
 *   - Cambia al modo de ejecución USER
 *   - Salta a la dirección 0x08000000 o 0x02000000 dependiendo del contenido
 *     de RETURN_ADDRESS_SEL (0x03007ffa):
 *         * 0x00: Salta a la 0x08000000 (defecto)
 *         * otro: Salta a la dirección 0x02000000
 */
inline void gba_softreset()
{
  asm volatile("swi 0x000000");
}

/*****************************************************************************/

/*
 * Función 0x02:
 * Halt.
 * Cambia la CPU al modo de bajo consumo, pero el resto de circuitos (video,
 * sonido, serie, etc.) siguen funcionando.
 * Se sale de este modo cuando se produce una IRQ (deben estar habilitadas).
 */
inline void gba_halt()
{
  asm volatile("swi 0x000002");
}

/*****************************************************************************/

/*
 * Función 0x06:
 * División entera.
 * @param num      Numerador
 * @param denom    Denominador
 * @param quot     Cociente
 * @param remain   Resto
 * @param abs_quot Valor absoluto del cociente
 */
inline void gba_div(int num, int denom, int *quot, int *remain, u_int *abs_quot)
{
  asm volatile("mov r0, %3       \n\t"
               "mov r1, %4       \n\t"
               "swi 0x060000     \n\t"
               "mov %0, r0       \n\t"
               "mov %1, r1       \n\t"
               "mov %2, r3       \n\t"
               : "=&r" (*quot), "=&r" (*remain), "=&r" (*abs_quot)
               : "r" (num), "r" (denom)
               : "r0", "r1", "r3");
}

/*****************************************************************************/

/*
 * Función 0x07:
 * División entera (para compatibilidad con la biblioteca de ARM).
 * Igual que la anterior pero tres ciclos más lenta.
 * @param num      Numerador
 * @param denom    Denominador
 * @param quot     Cociente
 * @param remain   Resto
 * @param abs_quot Valor absoluto del cociente
 */
inline void gba_armdiv(int num, int denom, int *quot, int *remain, u_int *abs_quot)
{
  asm volatile("mov r0, %4       \n\t"
               "mov r1, %3       \n\t"
               "swi 0x070000     \n\t"
               "mov %0, r0       \n\t"
               "mov %1, r1       \n\t"
               "mov %2, r3       \n\t"
               : "=&r" (*quot), "=&r" (*remain), "=&r" (*abs_quot)
               : "r" (num), "r" (denom)
               : "r0", "r1", "r3");
}

/*****************************************************************************/

/*
 * Función 0x08:
 * Raiz cuadrada.
 * @param val Valor
 * @param res Resultado
 */
inline void gba_sqrt(u_int val, u_int *res)
{
  asm volatile("mov r0, %1       \n\t"
               "swi 0x080000     \n\t"
               "mov %0, r0       \n\t"
               : "=&r" (*res)
               : "r" (val)
               : "r0");
}

/*****************************************************************************/

/*
 * Función 0x09:
 * Arco tangente.
 * @param val Valor (16 bits: 1 signo, 1 parte entera, 14 parte decimal)
 * @param res Resultado (-PI/2 < res < PI/2 en el rango 0xc000 - 0x4000)
 * Nota: Hay un problema de precisión si res < -PI/4 o res > PI/4
 */
inline void gba_arctan(int val, int *res)
{
  asm volatile("mov r0, %1       \n\t"
               "swi 0x090000     \n\t"
               "mov %0, r0       \n\t"
               : "=&r" (*res)
               : "r" (val)
               : "r0");
}

/*****************************************************************************/

/*
 * Función 0x0a:
 * Arco tangente tras el proceso de corrección.
 * @param x Valor (16 bits: 1 signo, 1 parte entera, 14 parte decimal)
 * @param y Valor (16 bits: 1 signo, 1 parte entera, 14 parte decimal)
 * @param res Resultado (0 <= res < 2*PI en el rango 0x0000 - 0xffff)
 */
inline void gba_arctan2(int x, int y, int *res)
{
  asm volatile("mov r0, %1       \n\t"
               "mov r1, %2       \n\t"
               "swi 0x0a0000     \n\t"
               "mov %0, r0       \n\t"
               : "=&r" (*res)
               : "r" (x), "r" (y)
               : "r0");
}

/*****************************************************************************/

/*
 * Función 0xff:
 * Imprime una cadena a la consola del depurador.
 * Esta llamada a la BIOS sólo funciona en el simulador Visualboy Advance,
 * si se realiza en la consola, la deja colgada.
 * @param str la cadena
 */
inline void gba_vba_print(char *str)
{
  asm volatile("mov r0, %0       \n\t"
               "swi 0xff0000     \n\t"
               : // no ouput
               : "r" (str)
               : "r0");
}

/*****************************************************************************/

