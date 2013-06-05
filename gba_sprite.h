/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para manejar sprites                      */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_sprite_h
#define gba_sprite_h

#include "gba.h"

/*****************************************************************************/

/*
 * Modos de color
 */
#define SPRITE_COLOR16             OBJ_COLOR16
#define SPRITE_COLOR256            OBJ_COLOR256

/*
 * Formas de los sprites
 */
#define SPRITE_SQUARE              0
#define SPRITE_WIDE                1
#define SPRITE_TALL                2

/*
 * Tamaños en pixels para los fondos de texto sin rotación
 */
#define SPRITE_SIZE_8x8            (SPRITE_SQUARE | OBJ_SIZE8)
#define SPRITE_SIZE_16x16          (SPRITE_SQUARE | OBJ_SIZE16)
#define SPRITE_SIZE_32x32          (SPRITE_SQUARE | OBJ_SIZE32)
#define SPRITE_SIZE_64x64          (SPRITE_SQUARE | OBJ_SIZE64)
#define SPRITE_SIZE_16x8           (SPRITE_WIDE   | OBJ_SIZE8)
#define SPRITE_SIZE_32x8           (SPRITE_WIDE   | OBJ_SIZE16)
#define SPRITE_SIZE_32x16          (SPRITE_WIDE   | OBJ_SIZE32)
#define SPRITE_SIZE_64x32          (SPRITE_WIDE   | OBJ_SIZE64)
#define SPRITE_SIZE_8x16           (SPRITE_TALL   | OBJ_SIZE8)
#define SPRITE_SIZE_8x32           (SPRITE_TALL   | OBJ_SIZE16)
#define SPRITE_SIZE_16x32          (SPRITE_TALL   | OBJ_SIZE32)
#define SPRITE_SIZE_32x64          (SPRITE_TALL   | OBJ_SIZE64)

/*****************************************************************************/

/*
 * Estructura de datos para manejar sprites
 */
typedef struct
{
  short oam_entry;         /* Entrada en la OAM */
  short is_shown;          /* Si es distinto de cero se muestra el sprite */
  char  width;             /* Ancho del sprite */
  char  height;            /* Alto del sprite */
  short pos_x;             /* Posición en el eje x */
  short pos_y;             /* Posición en el eje y */
  fixed_p scale_h;         /* Factor de escalado horizontal*/
  fixed_p scale_v;         /* Factor de escalado vertical */
  int angle;               /* Angulo de rotación en grados */
  char rotated;            /* TRUE si se ha rotado/estalado el sprite */
  const void  *data;       /* Puntero a los caracteres del sprite */
  short frame_size;        /* Tamaño de un frame en bytes */
  const short *frame_seq;  /* Secuencia de frames para definir una animación */
  short frame_seq_len;     /* Longitud de la secuencia */
  short frame_index;       /* Indice en la secuencia del frame actual */
} sprite_struct;


/*****************************************************************************/

/*
 * Configura el modo de almacenamiento de los sprites en la VRAM en 1 dimensión
 * e inicializa la OAM (oculta todos los sprites y fija los parámetros de rotación).
 */
inline void gba_oam_init();

/*****************************************************************************/

/*
 * Refresca los sprites en la pantalla
 */
inline void gba_oam_update(void);

/*****************************************************************************/

/*
 * Función para habilitar los sprites.
 */
inline void gba_sprite_enable();

/*****************************************************************************/

/*
 * Función para deshabilitar los sprites.
 */
inline void gba_sprite_disable();

/*****************************************************************************/

/*
 * Iniciliza una paleta de 256 colores para los sprites.
 * @param palette La paleta
 */
inline void gba_sprite_init_palette256(const void * palette);

/*****************************************************************************/

/*
 * Iniciliza una de las 16 paletas de 16 colores para los sprites.
 * @param index   Indice de la paleta (0..15)
 * @param palette La paleta
 */
inline void gba_sprite_init_palette16(short index, const void * palette);

/*****************************************************************************/

/*
 * Crea un nuevo sprite
 * @param sp    Puntero al sprite
 * @param size  Tamaño del sprite (SPRITE_SIZE_X)
 * @param color Formato del color (SPRITE_COLOR16, SPRITE_COLOR256)
 * @param data  Puntero al buffer que contiene los frames que definen el sprite
 * @return El sprite creado.
 */
void gba_sprite_new(sprite_struct * sp, short size, short color, const void *data);

/*****************************************************************************/

/*
 * Función para actualizar la posición, rotación y escalado de un sprite en la
 * OAM.
 * @param sp Puntero al sprite
 */
void gba_sprite_update(sprite_struct * sp);

/*****************************************************************************/

/*
 * Muestra un sprite.
 * @param sp  El sprite
 */
inline void gba_sprite_show(sprite_struct *sp);

/*****************************************************************************/

/*
 * Oculta un sprite.
 * @param sp  El sprite
 */
inline void gba_sprite_hide(sprite_struct *sp);

/*****************************************************************************/

/*
 * Fija la posición inicial de un sprite.
 * @param sp  El sprite
 * @param x   Posición en x
 * @param y   Posición en y
 */
inline void gba_sprite_set_pos(sprite_struct *sp, short x, short y);

/*****************************************************************************/

/*
 * Mueve un sprite en la dirección indicada por la máscara.
 * @param sp El sprite
 * @param dx Desplazamiento en x
 * @param dy Desplazamiento en y
 */
void gba_sprite_move(sprite_struct *sp, short dx, short dy);

/*****************************************************************************/

/*
 * Habilita el alpha-blending para un sprite
 * @param sp Puntero al sprite
 */
inline void gba_sprite_enable_bld(sprite_struct * sp);

/*****************************************************************************/

/*
 * Anula el alpha-blending para un sprite
 * @param sp Puntero al sprite
 */
inline void gba_sprite_disable_bld(sprite_struct * sp);

/*****************************************************************************/

/*
 * Voltea el sprite horizontalmente
 * @param sp Puntero al sprite
 */
inline void gba_sprite_flip_h(sprite_struct * sp);

/*****************************************************************************/

/*
 * Voltea el sprite verticalmente
 * @param sp Puntero al sprite
 */
inline void gba_sprite_flip_v(sprite_struct * sp);

/*****************************************************************************/

/*
 * Habilita la rotación y escalado de un sprite
 * @param sp        Puntero al sprite
 * @param rot_index Indice en la tabla de rotaciones para los parámetros
 */
inline void gba_sprite_enable_rotation(sprite_struct * sp, short rot_index);

/*****************************************************************************/

/*
 * Fija el ańgulo inicial de rotación hardware para un sprite.
 * @param sp     Puntero al sprite
 * @param angle  Angulo de rotación en grados enteros
 */
inline void gba_sprite_set_angle(sprite_struct * sp, int angle);

/*****************************************************************************/

/*
 * Modifica el ángulo de rotación actual del sprite.
 * @param sp     Puntero al sprite
 * @param dangle Incremento/decremento al angulo actual de rotación
 */
inline void gba_sprite_rotate(sprite_struct * sp, int dangle);

/*****************************************************************************/

/*
 * Fija el escalado hardware inicial para un sprite.
 * @param sp      Puntero al sprite
 * @param scale_h Escalado horizontal
 * @param scale_v Escalado vertical
 */
inline void gba_sprite_set_scale(sprite_struct * sp, fixed_p scale_h, fixed_p scale_v);

/*****************************************************************************/

/*
 * Si la rotación del sprite está activada, dobla el tamaño del sprite.
 * En caso contrario, el sprite se oculta
 * @param sp       Puntero al sprite
 */
void inline gba_sprite_enable_double_size(sprite_struct * sp);

/*****************************************************************************/

/*
 * Si la rotación del sprite está activada, restaura el tamaño del sprite
 * En caso contrario, vuelve a mostrar el sprite
 * @param sp       Puntero al sprite
 */
void inline gba_sprite_disable_double_size(sprite_struct * sp);

/*****************************************************************************/

/*
 * Define una secuencia de frames para crear la animación del sprite
 * @param sp  Puntero al sprite
 * @param seq Vector que define la secuencia
 * @param len Longitud de la secuencia
 */
void inline gba_sprite_set_frame_seq(sprite_struct * sp, const short* seq, short len);

/*****************************************************************************/

/*
 * Avanza al siguiente frame de la animación
 * @param sp  Puntero al sprite
 */
void gba_sprite_next_frame(sprite_struct * sp);

/*****************************************************************************/

/*
 * Fija el tamaño de los pixels de los sprites en modo mosaico
 * @param h_size Tamaño horizontal del mosaico de los fondos (1-16)
 * @param v_size Tamaño vertical del mosaico de los fondos (1-16)
 */
inline void gba_sprite_set_mosaic_size(short h_size, short v_size);

/*****************************************************************************/

/*
 * Habilita el modo mosaico en el sprite.
 * @param sp  Puntero al sprite
 */
void gba_sprite_enable_mosaic(sprite_struct * sp);

/*****************************************************************************/

/*
 * Deshabilita el modo mosaico en el sprite.
 * @param sp  Puntero al sprite
 */
void gba_sprite_disable_mosaic(sprite_struct * sp);

/*****************************************************************************/

/*
 * Comprueba si dos sprites se solapan.
 * @param sp1  Puntero al primer sprite
 * @param sp2  Puntero al segundo sprite
 * @return TRUE si hay solapamiento o FALSE en otro caso
 */
char gba_sprite_overlap(sprite_struct * sp1, sprite_struct * sp2);

/*****************************************************************************/

#endif /* gba_sprite_h */
