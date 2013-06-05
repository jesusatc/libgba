/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para generar números aleatorios           */
/*                                                                           */
/*****************************************************************************/

/*
 * Como la GBA no implementa ni la división ni el resto en hardware, y las
 * implementaciónes software de estas operaciones son lentas, los generadores
 * de números aleatorios habituales, que se basan en la utilización de estas
 * dos operaciones, son muy lentos para genetar números aleatorios en tiempo
 * real.
 *
 * Sin embargo, el algoritmo de generación de números aleatorios de "Mersenne
 * Twister", desarrollado por Makoto Matsumoto y Takuji Nishimura en 1997, no
 * necesita usar estas dos operaciones. Sólo se usan 4 XORs, 2 ANDs y 4
 * desplazamientos de registro, lo que lo hace muy adecuado para su uso en la
 * GBA. 
 *
 * El algoritmo original, tal y como se describe el trabajo Matsumoto y
 * Nishimura, necesita un búfer de 2496 bytes para almacenar el estado actual
 * del generador y tiene un periodo de 2^19937. Sin embargo, se puede reducir
 * el tamaño del búfer, reduciendo el periodo del algoritmo, para ahorrar algún
 * K de memoria. Concretamente, este código implementa la versión MT19937, que
 * genera números aleatorios equidistribuidos en el intervalo 0..(2^32 - 1).
 * 
 * Esta versión está basada en un código de Rafael Baptista, basado en otro de
 * Shawn Cokus que partía de la versión original del algoritmo. 
 */

/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_rand_h
#define gba_rand_h

#include "gba.h"

/*****************************************************************************/

/*
 * Constantes y macros necesarias.
 */
#define RAND_N       (624)                /* Longitud del vector de estado */
#define RAND_M       (397)                /* Parámetro de periodo */
#define RAND_K       (0x9908B0DFU)        /* Constante mágica */
#define MSBit(u)     ((u) & 0x80000000U)  /* Máscara para el More Significant Bit de u */
#define LSBit(u)     ((u) & 0x00000001U)  /* Máscara para el Less Significant Bit de u */
#define LSBits(u)    ((u) & 0x7FFFFFFFU)  /* Máscara para todos los bits de u menos el MSB */
#define mixBits(u,v) (MSBit(u)|LSBits(v)) /* Mezcla el signo de u y el resto de v */

/*****************************************************************************/

/*
 * Fija la semilla del generador.
 * @param seed Semilla
 */
void gba_srand(u_int seed);

/*****************************************************************************/

/*
 * Devuelve el siguiente número aleatorio
 */
u_int gba_rand();

/*****************************************************************************/

/*
 * Devuelve un número aleatorio en el intervalo [0, max_val).
 * @param max_val Máximo valor para el número aleatorio
 */
u_int gba_rand_mod(u_int max);

/*****************************************************************************/

#endif /* gba_rand_h */
