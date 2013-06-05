/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Constantes utiles para el manejo de la GBA                                */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_h
#define gba_h

/*****************************************************************************/
/* Tipos de datos                                                            */
/*****************************************************************************/

typedef volatile short * gba_word16;       /* Palabra de memoria de 16 bits */
typedef volatile int   * gba_word32;       /* Palabra de memoria de 32 bits */


/*****************************************************************************/
/* Procesador                                                                */
/*****************************************************************************/

#include "arm.h"
#define MCK                    (16*1024*1024)  /* Master clock */
#define MCK_KHz                (MCK/1000)


/*****************************************************************************/
/* Mapa de memoria                                                           */
/*****************************************************************************/

#include "palette.h"   /* Memoria para la paleta de colores */
#include "vram.h"      /* VRAM */
#include "oam.h"       /* Memoria para los atributos de objetos */


/*****************************************************************************/
/* Periféricos                                                               */
/*****************************************************************************/

#include "video.h"     /* Controlador de vídeo */
#include "gamepack.h"  /* Controlador de acceso al cartucho */
#include "sound.h"     /* Controlador de sonido */
#include "dma.h"       /* Controlador de DMA */
#include "timer.h"     /* Temporizadores */
#include "serial.h"    /* Puerto serie */
#include "keypad.h"    /* Botones */
#include "irq.h"       /* Controlador de interrupciones */

/*****************************************************************************/

#endif /* gba_h */
