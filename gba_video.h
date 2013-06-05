/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas de vídeo                                  */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_video_h
#define gba_video_h

#include "gba.h"

/*****************************************************************************/

/*
 * Dimensiones de la pantalla LCD
 */
#define SCREEN_WIDTH           240
#define SCREEN_HEIGHT          160

/*
 * Identificadores de las capas para los efectos especiales de color
 */
#define VIDEO_BLD_BG0          ((short) (1 << 0))
#define VIDEO_BLD_BG1          ((short) (1 << 1))
#define VIDEO_BLD_BG2          ((short) (1 << 2))
#define VIDEO_BLD_BG3          ((short) (1 << 3))
#define VIDEO_BLD_OBJ          ((short) (1 << 4))
#define VIDEO_BLD_BD           ((short) (1 << 5))

/*
 * Identificadores de las interrupciones que puede generar el controlador de vídeo
 */
#define VIDEO_INT_VBLANK       ((short) (1 << 3))
#define VIDEO_INT_HBLANK       ((short) (1 << 4))
#define VIDEO_INT_VCOUNTER     ((short) (1 << 5))

/*****************************************************************************/

/*
 * Cambia el buffer de vídeo (en los modos con doble buffer)
 */
inline void gba_video_swap_buffer();

/*****************************************************************************/

/*
 * Espera hasta que se llegue a un periodo de VBLANK.
 */
inline void gba_video_wait_vblank();

/*****************************************************************************/

/*
 * Fija el límite de líneas dibujadas para generar la interrupción VIDEO_INT_VCOUNTER
 * @limit Limite 
 */
inline void gba_video_set_vcounter_limit(u_char limit);

/*****************************************************************************/

/*
 * Habilita la generación de interrupciones.
 * @mask Máscara de las interrupciones que se deben generar.
 */
inline void gba_video_enable_int(u_char mask);

/*****************************************************************************/

/*
 * Deshabilita la generación de interrupciones.
 * @mask Máscara de las interrupciones que se deben generar.
 */
inline void gba_video_disable_int(u_char mask);

/*****************************************************************************/

/*
 * Habilita el alpha-blending.
 * Los niveles de transparencia son valores discretos de 0 a 16, indicando el
 * valor 0 total transparencia y el valor 16 total opacidad
 * @param layer1 Primera capa (VIDEO_BLD_X)
 * @param layer2 Segunda capa (VIDEO_BLD_X)
 * @param level1 Nivel de transparencia de la primera capa
 * @param level2 Nivel de transparencia de la segunda capa
 */
inline void gba_video_enable_bld_alpha(short layer1, short layer2, char level1, char level2);

/*****************************************************************************/

/*
 * Habilita el fade-in de una capa (incremento del brillo).
 * Los niveles de incremento son valores discretos de 0 a 16, indicando el
 * valor 0 ningún incremento y el 16 la saturación al blanco
 * @param layer Capa (VIDEO_BLD_X)
 * @param level Nivel de incremento
 */
inline void gba_video_enable_bld_fade_in(short layer, char level);

/*****************************************************************************/

/*
 * Habilita el fade-out de una capa (decremento del brillo).
 * Los niveles de decremento son valores discretos de 0 a 16, indicando el
 * valor 0 ningún decremento y el 16 la saturación al negro
 * @param layer Capa (VIDEO_BLD_X)
 * @param level Nivel de decremento
 */
inline void gba_video_enable_bld_fade_out(short layer, char level);

/*****************************************************************************/

/*
 * Deshabilita los efectos especiales de color (alpha-blending, fade-in/fade-out)
 */
inline void gba_video_disable_bld();

/*****************************************************************************/

#endif /* gba_video_h */
