/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para transferencias DMA                   */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_dma_h
#define gba_dma_h

#include "gba.h"

/*****************************************************************************/

/*
 * Identificadores de los canales de DMA
 */
#define DMA0               0
#define DMA1               1
#define DMA2               2
#define DMA3               3

/*****************************************************************************/

/*
 * Estructura de datos para manejar los canales de DMA
 */
typedef struct
{
  gba_word32 DMASAD;       /* Dirección fuente */
  gba_word32 DMADAD;       /* Dirección de destino */
  gba_word16 DMACNT_L;     /* Número de bloque a transmitir */
  gba_word16 DMACNT_H;     /* Registro de control */
} dma_struct;

/*****************************************************************************/

/*
 * Habilita el canal de DMA.
 * @param channel Número de canal
 */
inline void gba_dma_enable(u_char channel);

/*****************************************************************************/

/*
 * Deshabilita el canal de DMA
 * @param channel Número de canal
 */
inline void gba_dma_disable(u_char channel);

/*****************************************************************************/

/*
 * Copia un área de memoria mediante el canal DMA3 en bloques de 32 bits, por
 * lo tanto, LAS DIRECCIONES DEBEN ESTAR ALINEADAS A UNA FRONTERA DE 32 BITS
 * @param channel Número de canal
 * @param dest    Dirección de destino
 * @param source  Dirección de origen
 * @param size    Tamaño en bytes de la transferencia
 */
inline void gba_dma_memcpy(void* dest, const void* source, u_int size);

/*****************************************************************************/

/*
 * Inicializa una transferencia de sonido directo.
 * @param channel Canal (sólo DMA1 y DMA2)
 * @param fifo    Cola FIFO del canal de sonido
 * @param buffer  Buffer con las muestras de sonido
 */
inline void gba_dma_sound_init(u_char channel, void* fifo, const void* buffer);

/*****************************************************************************/

#endif /* gba_dma_h */
