/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para el controlador de DMA de la GBA          */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef dma_H
#define dma_H

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz del controlador de DMA de la consola                             */
/*****************************************************************************/

typedef struct
{
  int   DMA0SAD;       /* DMA 0 source address */
  int   DMA0DAD;       /* DMA 0 destination address */
  short DMA0CNT_L;     /* DMA 0 word count */
  short DMA0CNT_H;     /* DMA 0 control */
  int   DMA1SAD;       /* DMA 1 source address */
  int   DMA1DAD;       /* DMA 1 destination address */
  short DMA1CNT_L;     /* DMA 1 word count */
  short DMA1CNT_H;     /* DMA 1 control */
  int   DMA2SAD;       /* DMA 2 source address */
  int   DMA2DAD;       /* DMA 2 destination address */
  short DMA2CNT_L;     /* DMA 2 word count */
  short DMA2CNT_H;     /* DMA 2 control */
  int   DMA3SAD;       /* DMA 3 source address */
  int   DMA3DAD;       /* DMA 3 destination address */
  short DMA3CNT_L;     /* DMA 3 word count */
  short DMA3CNT_H;     /* DMA 3 control */
} gba_dma_regs_struct;

extern volatile gba_dma_regs_struct gba_dma_regs;


/*****************************************************************************/
/* DMAxCNT_H: Control de DMA                                                 */
/*****************************************************************************/

/*
 * Control de la dirección de destino
 */
#define DMA_DEST_INCREMENT         ((short) (0 << 5))  /* Incremento */
#define DMA_DEST_DECREMENT         ((short) (1 << 5))  /* Decremento */
#define DMA_DEST_FIXED             ((short) (2 << 5))  /* Fijo */
#define DMA_DEST_RELOAD            ((short) (3 << 5))  /* Incremento/Recarga */

/*
 * Control de la dirección de origen
 */
#define DMA_SOURCE_INCREMENT       ((short) (0 << 7))  /* Incremento */
#define DMA_SOURCE_DECREMENT       ((short) (1 << 7))  /* Decremento */
#define DMA_SOURCE_FIXED           ((short) (2 << 7))  /* Fijo */

/*
 * Repetición de la transferencia
 */
#define DMA_REPEAT                 ((short) (1 << 9))  /* Activar repetición */
 
/*
 * Tipo de transferencia
 */
#define DMA_16                     ((short) (0 << 10)) /* Transferencia en unidades de 16 bits */
#define DMA_32                     ((short) (1 << 10)) /* Transferencia en unidades de 32 bits */

/*
 * DMA hacia/desde el cartucho  (Sólo para el canal 3)
 */
#define DMA_GAME_PACK_DRQ          ((short) (1 << 11))

/*
 * Temporización del comienzo de la transferencia
 */
#define DMA_TIMING_IMMEDIATE       ((short) (0 << 12))
#define DMA_TIMING_VBLANK          ((short) (1 << 12))
#define DMA_TIMING_HBLANK          ((short) (2 << 12))
#define DMA_TIMING_SYNC_TO_DISPLAY ((short) (3 << 12)) /* Sólo para el DMA3 */
#define DMA_TIMING_DSOUND          ((short) (3 << 12)) /* Sólo para el DMA1 y DMA2 */

/*
 * Generación de una interrupción cuando acabe la copia
 */
#define DMA_INT                    ((short) (1 << 14))

/*
 * Habilitación de DMA
 */
#define DMA_ENABLE                 ((short) (1 << 15))

/*****************************************************************************/

#endif /* dma_H */
