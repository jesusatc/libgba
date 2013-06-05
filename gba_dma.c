/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para transferencias DMA                   */
/*                                                                           */
/*****************************************************************************/

#include "gba_dma.h"

/*****************************************************************************/

/*
 * Variables estáticas de la biblioteca
 */

dma_struct gba_dmas[4]=
{
  /* DMA 0 */
  {
    (gba_word32) &(gba_dma_regs.DMA0SAD),     /* Dirección fuente */
    (gba_word32) &(gba_dma_regs.DMA0DAD),     /* Dirección de destino */
    (gba_word16) &(gba_dma_regs.DMA0CNT_L),   /* Número de bloque a transmitir */
    (gba_word16) &(gba_dma_regs.DMA0CNT_H)    /* Registro de control */
  },

  /* DMA 1 */
  {
    (gba_word32) &(gba_dma_regs.DMA1SAD),     /* Dirección fuente */
    (gba_word32) &(gba_dma_regs.DMA1DAD),     /* Dirección de destino */
    (gba_word16) &(gba_dma_regs.DMA1CNT_L),   /* Número de bloque a transmitir */
    (gba_word16) &(gba_dma_regs.DMA1CNT_H)    /* Registro de control */
  },

  /* DMA 2 */
  {
    (gba_word32) &(gba_dma_regs.DMA2SAD),     /* Dirección fuente */
    (gba_word32) &(gba_dma_regs.DMA2DAD),     /* Dirección de destino */
    (gba_word16) &(gba_dma_regs.DMA2CNT_L),   /* Número de bloque a transmitir */
    (gba_word16) &(gba_dma_regs.DMA2CNT_H)    /* Registro de control */
  },

  /* DMA 3 */
  {
    (gba_word32) &(gba_dma_regs.DMA3SAD),     /* Dirección fuente */
    (gba_word32) &(gba_dma_regs.DMA3DAD),     /* Dirección de destino */
    (gba_word16) &(gba_dma_regs.DMA3CNT_L),   /* Número de bloque a transmitir */
    (gba_word16) &(gba_dma_regs.DMA3CNT_H)    /* Registro de control */
  }
};

/*****************************************************************************/

/*
 * Habilita el canal de DMA.
 * @param channel Número de canal
 */
inline void gba_dma_enable(u_char channel)
{
  *(gba_dmas[channel].DMACNT_H) |= DMA_ENABLE;
}

/*****************************************************************************/

/*
 * Deshabilita el canal de DMA
 * @param channel Número de canal
 */
inline void gba_dma_disable(u_char channel)
{
  *(gba_dmas[channel].DMACNT_H) &= ~DMA_ENABLE;
}

/*****************************************************************************/

/*
 * Copia un área de memoria mediante el canal DMA3 en bloques de 32 bits, por
 * lo tanto, LAS DIRECCIONES DEBEN ESTAR ALINEADAS A UNA FRONTERA DE 32 BITS
 * @param channel Número de canal
 * @param dest    Dirección de destino
 * @param source  Dirección de origen
 * @param size    Tamaño en bytes de la transferencia
 */
inline void gba_dma_memcpy(void* dest, const void* source, u_int size)
{
  short shadow = *(gba_dmas[DMA3].DMACNT_H);
  
  *(gba_dmas[DMA3].DMASAD)   = (int) source;
  *(gba_dmas[DMA3].DMADAD)   = (int) dest;
  *(gba_dmas[DMA3].DMACNT_L) = (u_short) (size >> 2);
  *(gba_dmas[DMA3].DMACNT_H) = DMA_ENABLE | DMA_TIMING_IMMEDIATE | DMA_32;
  
  *(gba_dmas[DMA3].DMACNT_H) = shadow;
}

/*****************************************************************************/

/*
 * Inicializa una transferencia de sonido directo.
 * @param channel Canal (sólo DMA1 y DMA2)
 * @param fifo    Cola FIFO del canal de sonido
 * @param buffer  Buffer con las muestras de sonido
 */
inline void gba_dma_sound_init(u_char channel, void* fifo, const void* buffer)
{
  *(gba_dmas[channel].DMASAD) = (int)buffer;
  *(gba_dmas[channel].DMADAD) = (int)fifo;
  *(gba_dmas[channel].DMACNT_H) = DMA_DEST_FIXED | DMA_SOURCE_INCREMENT |
                                  DMA_REPEAT | DMA_32 | DMA_TIMING_DSOUND;
}

/*****************************************************************************/

