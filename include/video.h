/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para el controlador de vídeo de la GBA        */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef video_h
#define video_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz del controlador de vídeo de la consola                           */
/*****************************************************************************/

typedef struct
{
  short DISPCNT;       /* lcd control */
  short undocumented;  /* green swap */
  short DISPSTAT;      /* general lcd status (stat,lyc) */
  short VCOUNT;        /* vertical counter (ly) */
  short BG0CNT;        /* bg0 control */
  short BG1CNT;        /* bg1 control */
  short BG2CNT;        /* bg2 control */
  short BG3CNT;        /* bg3 control */
  short BG0HOFS;       /* bg0 x-offset */
  short BG0VOFS;       /* bg0 y-offset */
  short BG1HOFS;       /* bg1 x-offset */
  short BG1VOFS;       /* bg1 y-offset */
  short BG2HOFS;       /* bg2 x-offset */
  short BG2VOFS;       /* bg2 y-offset */
  short BG3HOFS;       /* bg3 x-offset */
  short BG3VOFS;       /* bg3 y-offset */
  short BG2PA;         /* bg2 rotation/scaling parameter a (dx) */
  short BG2PB;         /* bg2 rotation/scaling parameter b (dmx) */
  short BG2PC;         /* bg2 rotation/scaling parameter c (dy) */
  short BG2PD;         /* bg2 rotation/scaling parameter d (dmy) */
  int   BG2X;          /* bg2 reference point x-coordinate */
  int   BG2Y;          /* bg2 reference point y-coordinate */
  short BG3PA;         /* bg3 rotation/scaling parameter a (dx) */
  short BG3PB;         /* bg3 rotation/scaling parameter b (dmx) */
  short BG3PC;         /* bg3 rotation/scaling parameter c (dy) */
  short BG3PD;         /* bg3 rotation/scaling parameter d (dmy) */
  int   BG3X;          /* bg3 reference point x-coordinate */
  int   BG3Y;          /* bg3 reference point y-coordinate */
  short WIN0H;         /* window 0 horizontal dimensions */
  short WIN1H;         /* window 1 horizontal dimensions */
  short WIN0V;         /* window 0 vertical dimensions */
  short WIN1V;         /* window 1 vertical dimensions */
  short WININ;         /* control inside of window(s) */
  short WINOUT;        /* control outside of windows & inside of obj window */
  short MOSAIC;        /* mosaic size */
  short filler;        /* not used */
  short BLDCNT;        /* color special effects selection (antes bldmod) */
  short BLDALPHA;      /* alpha blending coefficients (antes colev) */
  short BLDY;          /* brightness (fade-in/out) coefficient (antes coly) */
} gba_video_regs_struct;

extern volatile gba_video_regs_struct gba_video_regs;


/*****************************************************************************/
/* DISPCNT: Control de la pantalla                                           */
/*****************************************************************************/

/*
 * BG Mode
 */
#define VIDEO_BG_MODE0             ((short) 0)         /* Video mode 0 */
#define VIDEO_BG_MODE1             ((short) 1)         /* Video mode 1 */
#define VIDEO_BG_MODE2             ((short) 2)         /* Video mode 2 */
#define VIDEO_BG_MODE3             ((short) 3)         /* Bitmap, 240x160, 15 bits */
#define VIDEO_BG_MODE4             ((short) 4)         /* Bitmap, 240x160, 8 bits, doble buffer */
#define VIDEO_BG_MODE5             ((short) 5)         /* Bitmap, 160x128, 15 bits, doble buffer */

/*
 * Display Frame Selection (0 -> Frontbuffer, 1 -> Backbuffer)
 */
#define VIDEO_FRONTBUFFER          ((short) (0 << 4))  /* (Sólo modos 4 y 5) */
#define VIDEO_BACKBUFFER           ((short) (1 << 4))  /* (Sólo modos 4 y 5) */

/*
 * H-Blank Interval OBJ Processing Flag
 */
#define VIDEO_HBLANK_OAM           ((short) (1 << 5))  /* Allow access to OAM during H-Blank */

/*
 * OBJ Character VRAM Mapping Format
 */
#define VIDEO_OBJ_MAP_2D           ((short) (0 << 6))  /* Two dimensional mapping */
#define VIDEO_OBJ_MAP_1D           ((short) (1 << 6))  /* One dimensional mapping */

/*
 * Forced Blank
 */
#define VIDEO_FORCE_BLANK          ((short) (1 << 7))  /* Allow access to VRAM,Palette,OAM */

/*
 * Individual Screens Display Flag
 */
#define VIDEO_BG0                  ((short) (1 << 8))  /* Display background 0 */
#define VIDEO_BG1                  ((short) (1 << 9))  /* Display background 1 */
#define VIDEO_BG2                  ((short) (1 << 10)) /* Display background 2 */
#define VIDEO_BG3                  ((short) (1 << 11)) /* Display background 3 */
#define VIDEO_OBJ                  ((short) (1 << 12)) /* Display OBJ */

/*
 * Display Flags for Windows 0 and 1
 */
#define VIDEO_WIN0                 ((short) (1 << 13)) /* Display window 0 */
#define VIDEO_WIN1                 ((short) (1 << 14)) /* Display window 1 */

/*
 * OBJ Window Display Flag
 */
#define VIDEO_WINOBJ               ((short) (1 << 15)) /* Display OBJ window */


/*****************************************************************************/
/* UNDOCUMENTED: Intercambio del verde entre dos pixels consecutivos         */
/*****************************************************************************/

#define VIDEO_GREEN_SWAP           ((short) 1)         /* Intercambio del verde */


/*****************************************************************************/
/* DISPSTAT: Estado de la pantalla y generación de interrupciones            */
/*****************************************************************************/

/*
 * Status
 */
#define VIDEO_VBLANK               ((short) (1 << 0))  /* 1 = V_Blank (Solo lectura) */
#define VIDEO_HBLANK               ((short) (1 << 1))  /* 1 = H_Blank (Solo lectura) */
#define VIDEO_VCOUNTER             ((short) (1 << 2))  /* 1 = Match (Solo lectura) */

/*
 * Interrupt Request Enable Flags
 */
#define VIDEO_VBLANK_INT           ((short) (1 << 3))  /* 1 = Generación de int. */
#define VIDEO_HBLANK_INT           ((short) (1 << 4))  /* 1 = Generación de int. */
#define VIDEO_VCOUNTER_INT         ((short) (1 << 5))  /* 1 = Generación de int. */

/*
 * V Count Setting
 * Cuando n (0-227) alcance al valor de VCOUNT se generará una interrupción
 * (si está habilitada)
 */
#define VIDEO_VCOUNT_SETTING(n)    ((((short)(n)) & 0x00ff) << 8)

/*****************************************************************************/
/* BGxCNT: Control de fondos                                                 */
/*****************************************************************************/

/*
 * Priority Among BGs
 */
#define VIDEO_BG_MAX_PRIOR         ((short) 0)         /* Prioridad máxima*/
#define VIDEO_BG_MEDIUM_PRIOR      ((short) 1)         /* Prioridad media */
#define VIDEO_BG_LOW_PRIOR         ((short) 2)         /* Prioridad baja */
#define VIDEO_BG_MIN_PRIOR         ((short) 3)         /* Prioridad mínima */

/*
 * Character Base Block Specification - n = (0-3)
 * Especifica el bloque de memoria VRAM en el que están los caracteres que se
 * usarán para definir el fondo de pantalla.
 * La VRAM se divide en 4 bloques de 16Kb en los que pueden alojar caracteres
 * que se usarán para diseñar los fondos.
 */
#define VIDEO_CHAR_BLOCK(n)        ((((short)(n)) & 0x0003) << 2)

/*
 * Mosaic
 */
#define VIDEO_BG_MOSAIC            ((short) (1 << 6))  /* Activa el modo mosaico */

/*
 * Color Mode
 */
#define VIDEO_BG_COLOR16           ((short) (0 << 7))
#define VIDEO_BG_COLOR256          ((short) (1 << 7))

/*
 * Screen Base Block Specification - n = (0-31)
 * Especifica el bloque de memoria VRAM en el que está el mapa que define qué
 * caracteres se usan para diseñar la pantalla.
 * La VRAM se divide en 32 bloques de 2Kb en los que pueden los mapas de los
 * diseños de diferentes pantallas.
 */
#define VIDEO_SCREEN_BLOCK(n)      ((((short)(n)) & 0x001f) << 8)

/*
 * Area Overflow Processing (Solo en los fondos de rotación)
 */
#define VIDEO_BG_WRAPAROUND        ((short) (1 << 13))

/*
 * Screen Size
 */
#define VIDEO_BG_WIDTH_TEXT_256     ((short) (0 << 14))
#define VIDEO_BG_WIDTH_TEXT_512     ((short) (1 << 14))
#define VIDEO_BG_HEIGHT_TEXT_256    ((short) (0 << 15))
#define VIDEO_BG_HEIGHT_TEXT_512    ((short) (1 << 15))

#define VIDEO_BG_SIZE_TEXT_256x256  (VIDEO_BG_WIDTH_TEXT_256|VIDEO_BG_HEIGHT_TEXT_256)
#define VIDEO_BG_SIZE_TEXT_512x256  (VIDEO_BG_WIDTH_TEXT_512|VIDEO_BG_HEIGHT_TEXT_256)
#define VIDEO_BG_SIZE_TEXT_256x512  (VIDEO_BG_WIDTH_TEXT_256|VIDEO_BG_HEIGHT_TEXT_512)
#define VIDEO_BG_SIZE_TEXT_512x512  (VIDEO_BG_WIDTH_TEXT_512|VIDEO_BG_HEIGHT_TEXT_512)

#define VIDEO_BG_SIZE_ROT_128x128   ((short) (0 << 14))
#define VIDEO_BG_SIZE_ROT_256x256   ((short) (1 << 14))
#define VIDEO_BG_SIZE_ROT_512x512   ((short) (2 << 14))
#define VIDEO_BG_SIZE_ROT_1024x1024 ((short) (3 << 14))


/*****************************************************************************/
/* WINxH: Dimensiones horizontales de las ventanas                           */
/*****************************************************************************/

/*
 * x1 y x2 son las coordenadas izquierda y derecha de la ventana
 */
#define VIDEO_WIN_HSIZE(x1,x2) ((short) ((((x1) & 0x00ff)<<8) + (((x2)+1) & 0x00ff)))


/*****************************************************************************/
/* WINxV: Dimensiones verticales de las ventanas                             */
/*****************************************************************************/

/*
 * y1 e y2 son las coordenadas superior e inferior de la ventana
 */
#define VIDEO_WIN_VSIZE(y1,y2) ((short) ((((y1) & 0x00ff)<<8) + (((y2)+1) & 0x00ff)))


/*****************************************************************************/
/* WININ: Control dentro de las ventanas 0 y 1                               */
/*****************************************************************************/

/*
 * Window 0 Flags
 */
#define VIDEO_WIN0_BG0             ((short) (1 << 0))  /* Enable BG0 in Window 0 */
#define VIDEO_WIN0_BG1             ((short) (1 << 1))  /* Enable BG1 in Window 0 */
#define VIDEO_WIN0_BG2             ((short) (1 << 2))  /* Enable BG2 in Window 0 */
#define VIDEO_WIN0_BG3             ((short) (1 << 3))  /* Enable BG3 in Window 0 */
#define VIDEO_WIN0_OBJ             ((short) (1 << 4))  /* Enable OBJ in Window 0 */
#define VIDEO_WIN0_BLD             ((short) (1 << 5))  /* Enable Color BLD in Window 0 */

/*
 * Window 1 Flags
 */
#define VIDEO_WIN1_BG0             ((short) (1 << 8))  /* Enable BG0 in Window 1 */
#define VIDEO_WIN1_BG1             ((short) (1 << 9))  /* Enable BG1 in Window 1 */
#define VIDEO_WIN1_BG2             ((short) (1 << 10)) /* Enable BG2 in Window 1 */
#define VIDEO_WIN1_BG3             ((short) (1 << 11)) /* Enable BG3 in Window 1 */
#define VIDEO_WIN1_OBJ             ((short) (1 << 12)) /* Enable OBJ in Window 1 */
#define VIDEO_WIN1_BLD             ((short) (1 << 13)) /* Enable Color BLD in Window 1 */


/*****************************************************************************/
/* WINOUT: Control fuera de las ventanas y dentro de la ventana OBJ          */
/*****************************************************************************/

/*
 * Flags para el área fuera de las ventanas 
 */
#define VIDEO_OUT_BG0              ((short) (1 << 0))  /* Enable BG0 outside windows */
#define VIDEO_OUT_BG1              ((short) (1 << 1))  /* Enable BG1 outside windows */
#define VIDEO_OUT_BG2              ((short) (1 << 2))  /* Enable BG2 outside windows */
#define VIDEO_OUT_BG3              ((short) (1 << 3))  /* Enable BG3 outside windows */
#define VIDEO_OUT_OBJ              ((short) (1 << 4))  /* Enable OBJ outside windows */
#define VIDEO_OUT_BLD              ((short) (1 << 5))  /* Enable Color BLD outside windows */

/*
 * Flags para la ventana OBJ
 */
#define VIDEO_WINOBJ_BG0           ((short) (1 << 8))  /* Enable BG0 in OBJ Window */
#define VIDEO_WINOBJ_BG1           ((short) (1 << 9))  /* Enable BG1 in OBJ Window */
#define VIDEO_WINOBJ_BG2           ((short) (1 << 10)) /* Enable BG2 in OBJ Window */
#define VIDEO_WINOBJ_BG3           ((short) (1 << 11)) /* Enable BG3 in OBJ Window */
#define VIDEO_WINOBJ_OBJ           ((short) (1 << 12)) /* Enable OBJ in OBJ Window */
#define VIDEO_WINOBJ_BLD           ((short) (1 << 13)) /* Enable Color BLD in OBJ Window */


/*****************************************************************************/
/* MOSAIC: Tamaño del mosaico                                                */
/*****************************************************************************/

/*
 * n es de 4 bits (0-31)
 */
#define VIDEO_BG_MOSAIC_HSIZE(n)  (((((short)(n)) - 1) & 0x000f) << 0)
#define VIDEO_BG_MOSAIC_VSIZE(n)  (((((short)(n)) - 1) & 0x000f) << 4)
#define VIDEO_OBJ_MOSAIC_HSIZE(n) (((((short)(n)) - 1) & 0x000f) << 8)
#define VIDEO_OBJ_MOSAIC_VSIZE(n) (((((short)(n)) - 1) & 0x000f) << 12)


/*****************************************************************************/
/* BLDCNT (antes BLDMOD): Selec. de los efectos especiales de color (BLEND)  */
/*****************************************************************************/

#define VIDEO_BLD_BG0_1ST          ((short) (1 << 0))  /* BG0 es la primera capa para aplicar los efectos */
#define VIDEO_BLD_BG1_1ST          ((short) (1 << 1))  /* BG1 es la primera capa para aplicar los efectos */
#define VIDEO_BLD_BG2_1ST          ((short) (1 << 2))  /* BG2 es la primera capa para aplicar los efectos */
#define VIDEO_BLD_BG3_1ST          ((short) (1 << 3))  /* BG3 es la primera capa para aplicar los efectos */
#define VIDEO_BLD_OBJ_1ST          ((short) (1 << 4))  /* OBJ es la primera capa para aplicar los efectos */
#define VIDEO_BLD_BD_1ST           ((short) (1 << 5))  /* BD es la primera capa para aplicar los efectos */
#define VIDEO_BLD_ALPHA            ((short) (1 << 6))  /* Habilita alpha-blending */
#define VIDEO_BLD_BRIGHT_INC       ((short) (2 << 6))  /* Incrementa el brillo */
#define VIDEO_BLD_BRIGHT_DEC       ((short) (3 << 6))  /* Decrementa el brillo */
#define VIDEO_BLD_BG0_2ND          ((short) (1 << 8))  /* BG0 es la segunda capa para aplicar los efectos */
#define VIDEO_BLD_BG1_2ND          ((short) (1 << 9))  /* BG1 es la segunda capa para aplicar los efectos */
#define VIDEO_BLD_BG2_2ND          ((short) (1 << 10)) /* BG2 es la segunda capa para aplicar los efectos */
#define VIDEO_BLD_BG3_2ND          ((short) (1 << 11)) /* BG3 es la segunda capa para aplicar los efectos */
#define VIDEO_BLD_OBJ_2ND          ((short) (1 << 12)) /* OBJ es la segunda capa para aplicar los efectos */
#define VIDEO_BLD_BD_2ND           ((short) (1 << 13)) /* BD es la segunda capa para aplicar los efectos */


/*****************************************************************************/
/* BLDALPHA (antes COLEV) y BLDY (antes COLY): Coeficientes para             */
/*****************************************************************************/

/*
 * Coeficiente EVA (para la primera capa seleccionada en BLDCNT)
 * 0..16 = 0/16..16/16, 17..31=16/16
 */
#define VIDEO_BLD_EVA(n)           ((((short)(n)) & 0x000f) << 0)

/*
 * Coeficiente EVB (para la segunda capa seleccionada en BLDCNT) (sólo para BLDALPHA)
 * 0..16 = 0/16..16/16, 17..31=16/16
 */
#define VIDEO_BLD_EVB(n)           ((((short)(n)) & 0x000f) << 8)

/*****************************************************************************/

#endif /* video_h */
