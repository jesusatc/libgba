/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para manejar la memoria OAM de la GBA         */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef oam_h
#define oam_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz de la memoria OAM                                                */
/*****************************************************************************/

/*
 * Atributos de cada sprite
 */
typedef struct
{
  u_short ATTRIBUTE[3];  /* atributos de cada sprite */
  u_short filler;        /* relleno */
}gba_oam_obj_entry;

/*
 * Parámetros para la rotación/escalado de sprites
 */
typedef struct
{
  u_short filler1[3];  /* relleno */
  u_short PA;          /* rotation/scaling parameter a (dx) */
  u_short filler2[3];  /* relleno */
  u_short PB;          /* rotation/scaling parameter b (dmx) */
  u_short filler3[3];  /* relleno */
  u_short PC;          /* rotation/scaling parameter c (dy) */
  u_short filler4[3];  /* relleno */
  u_short PD;          /* rotation/scaling parameter d (dmy) */
}gba_oam_rotation_entry;

/*
 * Estructura para manejar la OAM
 */
typedef union
{
  gba_oam_obj_entry obj[128];
  gba_oam_rotation_entry rotation[32];
}gba_oam_struct;

extern volatile gba_oam_struct gba_oam;


/*****************************************************************************/
/* Atributo 0                                                                */
/*****************************************************************************/

/*
 * Coordenada Y del sprite ([-128,127])
 */
#define OBJ_Y(n)                   (((short)(n)) & 0x00ff)

/*
 * Activa la rotación del sprite
 */
#define OBJ_ROTATION               ((short) (1 << 8))

/*
 * Si está activada la rotación, el bit 9 dobla el tamaño del sprite
 */
#define OBJ_SIZE_DOUBLE            ((short) (1 << 9))
                                              
/*
 * Si NO está activada la rotación, el bit 9 impide que se muestre el sprite
 */
#define OBJ_SPRITE_OFF             ((short) (1 << 9))

/*
 * Flags de modo. Controlan el alpha blending
 */
#define OBJ_MODE_NORMAL            ((short) (0 << 10))
#define OBJ_MODE_BLD               ((short) (1 << 10))
#define OBJ_MODE_WINDOWED          ((short) (1 << 11))

/*
 * Activa el modo mosaico
 */
#define OBJ_MOSAIC                 ((short) (1 << 12))

/*
 * Selecciona entre 16 o 256 colores
 */
#define OBJ_COLOR16                ((short) (0 << 13))
#define OBJ_COLOR256               ((short) (1 << 13))

/*
 * Forma del sprite
 */
#define OBJ_SQUARE                 ((short) (0 << 14))
#define OBJ_WIDE                   ((short) (1 << 14))
#define OBJ_TALL                   ((short) (1 << 15))


/*****************************************************************************/
/* Atributo 1                                                                */
/*****************************************************************************/

/*
 * Coordenada X del sprite ([-256,255])
 */
#define OBJ_X(n)                   (((short)(n)) & 0x01ff)

/*
 * Selección de los parámetros de rotación/escalado (si la rotación está habilitada)
 */
#define OBJ_ROTDATA(n)			       ((((short) (n)) & 0x001f) << 9)

/*
 * Flags para voltear el sprite (si la rotación no está activa)
 */
#define OBJ_HORIZONTAL_FLIP		     ((short) (1 << 12))
#define OBJ_VERTICAL_FLIP		       ((short) (1 << 13))

/*
 * Tamaño del sprite
 */
#define OBJ_SIZE8			             ((short) (0 << 14))
#define OBJ_SIZE16			           ((short) (1 << 14))
#define OBJ_SIZE32		 	           ((short) (2 << 14))
#define OBJ_SIZE64	 		           ((short) (3 << 14))

/*****************************************************************************/
/* Atributo 2                                                                */
/*****************************************************************************/

/*
 * Índice del primer carácter del sprite en la memoria de vídeo
 */
#define OBJ_NAME(n)                (((short)(n)) & 0x03ff)

/*
 * Prioridad del sprite
 */
#define OBJ_MAX_PRIOR              ((short) (0 << 10)) /* Prioridad máxima*/
#define OBJ_MEDIUM_PRIOR           ((short) (1 << 10)) /* Prioridad media */
#define OBJ_LOW_PRIOR              ((short) (2 << 10)) /* Prioridad baja */
#define OBJ_MIN_PRIOR              ((short) (3 << 10)) /* Prioridad mínima */

/*
 * Paleta del sprite (sólo para los de 16 colores)
 */
#define OBJ_PALETTE_16(n)		       ((((short) (n)) & 0x000f) << 12)

/*****************************************************************************/

#endif /* oam_h */
