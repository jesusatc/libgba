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
#ifndef gba_bg_h
#define gba_bg_h

#include "gba.h"

/*****************************************************************************/

/*
 * Identificadores de los modos de gestionar los fondos
 */
#define BG_MODE0               0
#define BG_MODE1               1
#define BG_MODE2               2
#define BG_MODE3               3
#define BG_MODE4               4
#define BG_MODE5               5

/*
 * Identificadores de los fondos
 */
#define BG0                    0
#define BG1                    1
#define BG2                    2
#define BG3                    3

/*
 * Modos de color
 */
#define BG_COLOR16             VIDEO_BG_COLOR16
#define BG_COLOR256            VIDEO_BG_COLOR256

/*
 * Tamaños en pixels para los fondos de texto sin rotación
 */
#define BG_SIZE_TEXT_256x256   VIDEO_BG_SIZE_TEXT_256x256
#define BG_SIZE_TEXT_512x256   VIDEO_BG_SIZE_TEXT_512x256
#define BG_SIZE_TEXT_256x512   VIDEO_BG_SIZE_TEXT_256x512
#define BG_SIZE_TEXT_512x512   VIDEO_BG_SIZE_TEXT_512x512

#define BG_SIZE_ROT_128x128    VIDEO_BG_SIZE_ROT_128x128
#define BG_SIZE_ROT_256x256    VIDEO_BG_SIZE_ROT_256x256
#define BG_SIZE_ROT_512x512    VIDEO_BG_SIZE_ROT_512x512
#define BG_SIZE_ROT_1024x1024  VIDEO_BG_SIZE_ROT_512x512

/*****************************************************************************/

/*
 * Estructura de datos para manejar fondos
 */
typedef struct
{
  short      mask;         /* Máscara en DISPCNT (VIDEO_BG0, ..., VIDEO_BG3) */
  gba_word16 BGCNT;        /* Puntero al registro de control */
  gba_word16 BGHOFS;       /* Puntero al registro de desplazamiento horizontal */
  gba_word16 BGVOFS;       /* Puntero al registro de desplazamiento vertical */
  gba_word16 BGPA;         /* Puntero al registro PA (sólo para los fondos de rotación) */
  gba_word16 BGPB;         /* Puntero al registro PB (sólo para los fondos de rotación) */
  gba_word16 BGPC;         /* Puntero al registro PC (sólo para los fondos de rotación) */
  gba_word16 BGPD;         /* Puntero al registro PD (sólo para los fondos de rotación) */
  gba_word32 BGX;          /* Puntero a la coordenada x del punto de referencia (sólo para los fondos de rotación) */
  gba_word32 BGY;          /* Puntero a la coordenada y del punto de referencia (sólo para los fondos de rotación) */
  short      char_block;   /* Bloque para almacenar los caracteres */
  short      screen_block; /* Bloque para almacenar el mapa que define el fondo */
  short      ofs_h;        /* Desplazamiento horizontal */
  short      ofs_v;        /* Desplazamiento vertical */
  short      width;        /* Ancho en pixels */
  short      height;       /* Alto en pixels */
  fixed_p    scale_h;      /* Factor de escalado horizontal*/
  fixed_p    scale_v;      /* Factor de escalado vertical */
  int        rot_angle;    /* Angulo de rotación en grados */
  int        rot_x;        /* Punto de referencia para la rotación - x */
  int        rot_y;        /* Punto de referencia para la rotación - y */
} bg_struct;

/*****************************************************************************/

/*
 * Función que retorna el modo de los fondos.
 */
inline short gba_bg_get_mode(void);

/*****************************************************************************/

/*
 * Función para fijar el modo de los fondos.
 * @param mode Modo (BG_MODE0, BG_MODE1, BG_MODE2, BG_MODE3, BG_MODE4, BG_MODE5)
 */
void gba_bg_set_mode(u_char mode);

/*****************************************************************************/

/*
 * Función para inicializar un fondo en modo texto.
 * @param id           Identificador (BG0, BG1, BG2, BG3)
 * @param color        Configuración del color (BG_COLOR16 o BG_COLOR256)
 * @param size         Tamaño del fondo (BG_SIZE_X)
 * @param char_block   Bloque para almacenar los caracteres (0-3)
 * @param screen_block Bloque para almacenar el mapa que define el fondo (0-31)
 * @param sizeof_chars Tamaño del buffer de caracteres en bytes
 * @param chars        Puntero al buffer de caracteres
 * @param map          Puntero al buffer que almacena al mapa
 */
void gba_bg_init_text(short id, short color, short size,
                      short char_block, short screen_block,
                      short sizeof_chars, const void* chars, const void* map);
                      
/*****************************************************************************/

/*
 * Función para inicializar el frontbuffer en modo bitmap (BG2, modos 3-5).
 * @param bitmap Puntero al buffer de pixels
 */
void gba_bg_init_front_buffer(const void* bitmap);

/*****************************************************************************/

/*
 * Función para inicializar el backbuffer en modo bitmap (BG2, modos 4-5).
 * @param bitmap Puntero al buffer de pixels
 */
void gba_bg_init_back_buffer(const void* bitmap);

/*****************************************************************************/

/*
 * Iniciliza una paleta de 256 colores para el fondo.
 * @param palette La paleta
 */
inline void gba_bg_init_palette256(const void * palette);

/*****************************************************************************/

/*
 * Iniciliza una de las 16 paletas de 16 colores para el fondo.
 * @param index   Indice de la paleta (0..15)
 * @param palette La paleta
 */
inline void gba_bg_init_palette16(short index, const void * palette);

/*****************************************************************************/

/*
 * Muestra un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_show(short id);

/*****************************************************************************/

/*
 * Oculta un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_hide(short id);

/*****************************************************************************/

/*
 * Retorna el ancho en pixels de un fondo
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline short gba_bg_width(short id);

/*****************************************************************************/

/*
 * Retorna el alto en pixels de un fondo
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline short gba_bg_height(short id);

/*****************************************************************************/

/*
 * Fija el tamaño de los pixels de los fondos en modo mosaico.
 * @param h_size Tamaño horizontal del mosaico de los fondos (1-16)
 * @param v_size Tamaño vertical del mosaico de los fondos (1-16)
 */
inline void gba_bg_set_mosaic_size(short h_size, short v_size);

/*****************************************************************************/

/*
 * Habilita el modo mosaico en un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_enable_mosaic(short id);

/*****************************************************************************/

/*
 * Deshabilita el modo mosaico en un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_disable_mosaic(short id);

/*****************************************************************************/

/*
 * Función para aplicar desplazamiento hardware a los fondos.
 * @param bg Puntero al fondo
 * @param dx Desplazamiento horizontal
 * @param dy Desplazamiento vertical
 */
inline void gba_bg_scroll(short id, short dx, short dy);

/*****************************************************************************/


/*
 * Función para actualizar los atributos de rotación/escalado.
 * @param id Identificador (BG2, BG3)
 */
void gba_bg_update_rotation(short id);

/*****************************************************************************/

/*
 * Modifica el centro de rotación actual del fondo.
 * @param id Identificador (BG2, BG3)
 * @param dx Incremento/decremento horizontal
 * @param dy Incremento/decremento vertical
 */
inline void gba_bg_move_rotation_center(short id, int dx, int dy);

/*****************************************************************************/

/*
 * Modifica el ángulo de rotación actual del fondo.
 * @param id     Identificador (BG2, BG3)
 * @param dangle Incremento/decremento al angulo actual de rotación
 */
inline void gba_bg_rotate(short id, int dangle);

/*****************************************************************************/

/*
 * Modifica el escalado actual del fondo.
 * @param id       Identificador (BG2, BG3)
 * @param dscale_h Incremento/decremento escalado horizontal
 * @param dscale_v Incremento/decremento escalado vertical
 */
inline void gba_bg_scale(short id, fixed_p dscale_h, fixed_p dscale_v);

/*****************************************************************************/

/*
 * Repite el fondo para llenar la pantalla.
 * @param id Identificador (BG2, BG3)
 */
inline void gba_bg_overflow_wraparound(short id);

/*****************************************************************************/

/*
 * Deja transparente la parte de pantalla que no ocupe un fondo de rotación.
 * @param id Identificador (BG2, BG3)
 */
inline void gba_bg_overflow_transparent(short id);

/*****************************************************************************/

#endif /* gba_bg_h */
