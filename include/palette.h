/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para manejar la memoria de paleta de la GBA   */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef palette_h
#define palette_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz de la memoria para almacenar las paletas                         */
/*****************************************************************************/

/*
 * En la GBA se pueden usar o bien una paleta de 256 colores o bien 16 paletas
 * de 16 colores tanto para los fondos como para los sprites
 */
typedef short gba_palette16[16];
typedef short gba_palette256[256];

typedef struct
{
  union  /* Paleta para los fondos */
  {
    gba_palette16 bg16[16];
    gba_palette256 bg256;
  } __attribute__ ((packed));

  union  /* Paleta para los sprites */
  {
    gba_palette16 obj16[16];
    gba_palette256 obj256;
  };
} gba_palette_struct;

extern volatile gba_palette_struct gba_palette;

/*****************************************************************************/

#endif /* palette_h */
