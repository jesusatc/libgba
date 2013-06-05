/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas de vídeo                                  */
/*                                                                           */
/*****************************************************************************/

#include "gba_video.h"

/*****************************************************************************/

/*
 * Cambia el buffer de vídeo (en los modos con doble buffer)
 */
inline void gba_video_swap_buffer()
{
  gba_video_regs.DISPCNT ^= VIDEO_BACKBUFFER;
}

/*****************************************************************************/

/*
 * Espera hasta que se llegue a un periodo de VBLANK.
 */
inline void gba_video_wait_vblank()
{
  while(!(gba_video_regs.DISPSTAT & VIDEO_VBLANK));
  while(gba_video_regs.DISPSTAT & VIDEO_VBLANK);
}

/*****************************************************************************/

/*
 * Fija el límite de líneas dibujadas para generar la interrupción VIDEO_INT_VCOUNTER
 * @limit Limite 
 */
inline void gba_video_set_vcounter_limit(u_char limit)
{
  gba_video_regs.DISPSTAT |= VIDEO_VCOUNT_SETTING(limit);
}

/*****************************************************************************/

/*
 * Habilita la generación de interrupciones.
 * @mask Máscara de las interrupciones que se deben generar.
 */
inline void gba_video_enable_int(u_char mask)
{
  gba_video_regs.DISPSTAT |= mask;
}

/*****************************************************************************/

/*
 * Deshabilita la generación de interrupciones.
 * @mask Máscara de las interrupciones que se deben generar.
 */
inline void gba_video_disable_int(u_char mask)
{
  /* Fijo la máscara para las interrupciones */
  gba_video_regs.DISPSTAT &= ~mask;
}

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
inline void gba_video_enable_bld_alpha(short layer1, short layer2, char level1, char level2)
{
  gba_video_regs.BLDCNT = layer1 | (layer2 << 8) | VIDEO_BLD_ALPHA;
  gba_video_regs.BLDALPHA = VIDEO_BLD_EVA(level1) | VIDEO_BLD_EVB(level2);
}

/*****************************************************************************/

/*
 * Habilita el fade-in de una capa (incremento del brillo).
 * Los niveles de incremento son valores discretos de 0 a 16, indicando el
 * valor 0 ningún incremento y el 16 la saturación al blanco
 * @param layer Capa (VIDEO_BLD_X)
 * @param level Nivel de incremento
 */
inline void gba_video_enable_bld_fade_in(short layer, char level)
{
  gba_video_regs.BLDCNT = layer | VIDEO_BLD_BRIGHT_INC;
  gba_video_regs.BLDY = VIDEO_BLD_EVA(level);
}

/*****************************************************************************/

/*
 * Habilita el fade-out de una capa (decremento del brillo).
 * Los niveles de decremento son valores discretos de 0 a 16, indicando el
 * valor 0 ningún decremento y el 16 la saturación al negro
 * @param layer Capa (VIDEO_BLD_X)
 * @param level Nivel de decremento
 */
inline void gba_video_enable_bld_fade_out(short layer, char level)
{
  gba_video_regs.BLDCNT = layer | VIDEO_BLD_BRIGHT_DEC;
  gba_video_regs.BLDY = VIDEO_BLD_EVA(level);
}

/*****************************************************************************/

/*
 * Deshabilita los efectos especiales de color (alpha-blending, fade-in/fade-out)
 */
inline void gba_video_disable_bld()
{
  gba_video_regs.BLDCNT &= ~VIDEO_BLD_BRIGHT_DEC;
}

/*****************************************************************************/

