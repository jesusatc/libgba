/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para manejar interrupciones en la GBA     */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_irq_h
#define gba_irq_h

#include "gba.h"

/*****************************************************************************/

/*
 * Habilita la gestión de interrupciones
 */
inline void gba_irq_enable_all();

/*****************************************************************************/

/*
 * Deshabilita la gestión de interrupciones
 */
inline void gba_irq_disable_all();

/*****************************************************************************/

/*
 * Función para habilitar la atención de interrupciones concretas
 * @param masc    Máscara para seleccionar interrupciones 
 * @param handler Función para gestionar las interrupciones
 */
void gba_irq_enable(short masc, gba_irq_handler handler);

/*****************************************************************************/

/*
 * Deshabilita interrupciones concretas
 * @param masc Máscara para seleccionar interrupciones 
 */
inline void gba_irq_disable(short masc);

/*****************************************************************************/

#endif /* gba_irq_h */
