/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para operar en coma fija                  */
/*                                                                           */
/* Formato utilizado: SEEEEEEEFFFFFFFF                                       */
/*  - 1 bit de signo (bit 15),                                               */
/*  - 7 de parte entera (bits 8-14),                                         */
/*  - 8 de parte fraccionaria (bits 0-7).                                    */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_fp_h
#define gba_fp_h

#include "std_c.h"

/*****************************************************************************/

/*
 * Macros para la conversión de tipos desde y hacia fixed_p
 */
#define I2FP(i)               ((fixed_p) (((int) i) << 8))
#define FP2I(fp)              ((signed int) (((fixed_p) fp) >> 8))
#define F2FP(f)               ((fixed_p) (((float) f) * 256))
#define FP2F(fp)              (((float) fp) / 256)

/*****************************************************************************/

/*
 * Suma dos números en coma fija
 * @param a Primer número
 * @param b Segundo número
 */
inline fixed_p gba_fp_add(fixed_p a, fixed_p b);

/*****************************************************************************/

/*
 * Resta dos números en coma fija
 * @param a Primer número
 * @param b Segundo número
 */
inline fixed_p gba_fp_sub(fixed_p a, fixed_p b);

/*****************************************************************************/

/*
 * Multiplica dos números en coma fija
 * @param a Primer número
 * @param b Segundo número
 */
inline fixed_p gba_fp_mult(fixed_p a, fixed_p b);

/*****************************************************************************/

/*
 * Divide dos números en coma fija
 * @param a Primer número
 * @param b Segundo número
 */
inline fixed_p gba_fp_div(fixed_p a, fixed_p b);

/*****************************************************************************/

/*
 * Retorna el seno de un ángulo
 * @param ang Angulo
 */
inline fixed_p gba_fp_sin(signed int ang);

/*****************************************************************************/

/*
 * Retorna el coseno de un ángulo
 * @param ang Angulo
 */
inline fixed_p gba_fp_cos(signed int ang);

/*****************************************************************************/

#endif /* gba_fp_h */
