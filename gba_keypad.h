/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para manejar los botones en la GBA        */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_keypad_h
#define gba_keypad_h

#include "gba.h"

/*****************************************************************************/

/*
 * Retorna el estatus de los botones (0 -> pulsado)
 */
inline short gba_keypad_getstatus();

/*****************************************************************************/

/*
 * Retorna 0 si alguno de los botones seleccionados en la máscara está pulsado.
 * @param masc   Máscara para seleccionar los botones
 */
inline short gba_keypad_released(short masc);

/*****************************************************************************/

/*
 * Retorna 0 si ninguno de los botones seleccionados en la máscara está pulsado.
 * @param status Estado de los botones
 * @param masc   Máscara para seleccionar los botones
 */
inline short gba_keypad_pressed(short masc);

/*****************************************************************************/

#endif /* gba_keypad_h */
