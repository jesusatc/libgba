/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para manejar sprites                      */
/*                                                                           */
/*****************************************************************************/

#include "gba_sprite.h"
#include "gba_video.h"
#include "gba_bg.h"
#include "gba_dma.h"
#include "gba_fp.h"
#include "gba_bios.h"

/*****************************************************************************/

/*
 * Variables estáticas de la biblioteca
 */

/*
 * Copia de la OAM para modificar los sprites antes de refrescarlos
 */
gba_oam_struct gba_sprite_oam_shadow;

/*
 * Entrada en la OAM para el proximo sprite que se cree
 */
u_short gba_sprite_next_obj_entry = 0;

/*
 * Desplazamiento en la memoria de caracteres para el proximo sprite
 */
u_short gba_sprite_next_obj_name = 0;

/*
 * Copia del registro MOSAIC. Es necesaria porque el registro MOSAIC no se
 * puede leer. Es de sólo escritura. Definida en gba_bg.c.
 */
extern short gba_bg_mosaic_shadow;

/*****************************************************************************/

/*
 * Configura el modo de almacenamiento de los sprites en la VRAM en 1 dimensión
 * e inicializa la OAM (oculta todos los sprites y fija los parámetros de rotación).
 */
inline void gba_oam_init()
{
  int i;

  /* Ocultamos los sprites */
  for(i = 0; i < 128; i++)
  {
    gba_sprite_oam_shadow.obj[i].ATTRIBUTE[0] = SCREEN_HEIGHT;
    gba_sprite_oam_shadow.obj[i].ATTRIBUTE[1] = SCREEN_WIDTH;
  }

  /* Fijamos todas las matrices de rotación a la matriz identidad en punto fijo */
  for(i = 0; i < 32; i++)
  {
    gba_sprite_oam_shadow.rotation[i].PA = I2FP(1); /* dx */
    gba_sprite_oam_shadow.rotation[i].PC = I2FP(0); /* dy */
    gba_sprite_oam_shadow.rotation[i].PB = I2FP(0); /* dmx */
    gba_sprite_oam_shadow.rotation[i].PD = I2FP(1); /* dmy */
  }
}

/*****************************************************************************/

/*
 * Refresca los sprites en la pantalla
 */
inline void gba_oam_update(void)
{
  gba_dma_memcpy((void*) &gba_oam, (void*)&gba_sprite_oam_shadow, sizeof(gba_oam_struct));
}

/*****************************************************************************/

/*
 * Función para habilitar los sprites.
 */
inline void gba_sprite_enable()
{
  /* Los sprites se almacenan en 1D */
  gba_video_regs.DISPCNT |= VIDEO_OBJ_MAP_1D | VIDEO_OBJ;
}

/*****************************************************************************/

/*
 * Función para deshabilitar los sprites.
 */
inline void gba_sprite_disable()
{
  gba_video_regs.DISPCNT &= ~VIDEO_OBJ;
}

/*****************************************************************************/

/*
 * Iniciliza una paleta de 256 colores para los sprites.
 * @param palette La paleta
 */
inline void gba_sprite_init_palette256(const void * palette)
{
  gba_dma_memcpy((void*) gba_palette.obj256, palette, sizeof(gba_palette256));
}

/*****************************************************************************/

/*
 * Iniciliza una de las 16 paletas de 16 colores para los sprites.
 * @param index   Indice de la paleta (0..15)
 * @param palette La paleta
 */
inline void gba_sprite_init_palette16(short index, const void * palette)
{
  gba_dma_memcpy((void*) gba_palette.obj16[index], palette, sizeof(gba_palette16));
}

/*****************************************************************************/

/*
 * Crea un nuevo sprite
 * @param sp    Puntero al sprite
 * @param size  Tamaño del sprite (SPRITE_SIZE_X)
 * @param color Formato del color (SPRITE_COLOR16, SPRITE_COLOR256)
 * @param data  Puntero al buffer que contiene los frames que definen el sprite
 * @return El sprite creado.
 */
void gba_sprite_new(sprite_struct * sp, short size, short color, const void *data)
{
  short obj_size = (size & 0xc000);
  short obj_shape = (size & 0x0003) << 14;
  
  /*
   * Si la pantalla está en modo gráfico, sólo tenemos disponible la mitad de
   * la memoria para los sprites
   */
  if (gba_sprite_next_obj_name==0 && (gba_bg_get_mode() & (BG_MODE3|BG_MODE4|BG_MODE5)))
    gba_sprite_next_obj_name = 512;

  /* Inicializamos los campos del sprite */
  sp->oam_entry = gba_sprite_next_obj_entry++; /* Entrada en la OAM */
  sp->is_shown = FALSE;             /* Inicialmente está oculto */
  sp->pos_x=0;                      /* Posición por defecto */
  sp->pos_y=0;
  sp->scale_h=I2FP(1);              /* Escalado por defecto */
  sp->scale_v=I2FP(1);
  sp->angle=0;                      /* Rotación por defecto */
  sp->rotated=FALSE;                /* No se aplicado rotación/escalado */
  sp->data = data;
  
  /* Inicializamos el alto y el ancho */
  switch (obj_shape)
  {
    case OBJ_SQUARE:
      switch (obj_size)
      {
        case OBJ_SIZE8:
          sp->width = 8;
          sp->height = 8;
          break;
        case OBJ_SIZE16:
          sp->width = 16;
          sp->height = 16;
          break;
        case OBJ_SIZE32:
          sp->width = 32;
          sp->height = 32;
          break;
        case OBJ_SIZE64:
          sp->width = 64;
          sp->height = 64;
          break;
      }  
      break;

    case OBJ_WIDE:
      switch (obj_size)
      {
        case OBJ_SIZE8:
          sp->width = 16;
          sp->height = 8;
          break;
        case OBJ_SIZE16:
          sp->width = 32;
          sp->height = 8;
          break;
        case OBJ_SIZE32:
          sp->width = 32;
          sp->height = 16;
          break;
        case OBJ_SIZE64:
          sp->width = 64;
          sp->height = 32;
          break;
      }  
      break;
      
    case OBJ_TALL:
      switch (obj_size)
      {
        case OBJ_SIZE8:
          sp->width = 8;
          sp->height = 16;
          break;
        case OBJ_SIZE16:
          sp->width = 8;
          sp->height = 32;
          break;
        case OBJ_SIZE32:
          sp->width = 16;
          sp->height = 32;
          break;
        case OBJ_SIZE64:
          sp->width = 32;
          sp->height = 64;
          break;
      }  
      break;
  }

  /* En principio suponemos que sólo hay un frame */  
  sp->frame_seq_len = 1;
  sp->frame_seq = NULL;
  sp->frame_index = 0;

  /* Inicializamos sus atributos (pos_x y pos_y se fijan a 0) */
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] |= color | obj_shape;
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] |= obj_size;
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[2] |= gba_sprite_next_obj_name;
  
  /* tamaño en pixels de la transferencia */
  sp->frame_size = sp->width * sp->height;

  /* tamaño de la transferencia en bytes */
  if (color == SPRITE_COLOR16)
    sp->frame_size /= 2;

  /* Copiamos los caracteres del primer frame al sprite */
  gba_dma_memcpy((void*)gba_vram.obj_data[gba_sprite_next_obj_name], data, sp->frame_size);
  
  /* Fijamos el desplazamiento para el proximo sprite */
  gba_sprite_next_obj_name += sp->frame_size/sizeof(gba_video_char16);
}

/*****************************************************************************/

/*
 * Función para actualizar la posición, rotación y escalado de un sprite en la
 * OAM.
 * @param sp Puntero al sprite
 */
void gba_sprite_update(sprite_struct * sp)
{
  fixed_p dx, dy, dmx, dmy;
  short rot_index;
 
  if (sp->is_shown)
  {
    gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] &= 0xfe00;
    gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] |= (sp->pos_x & 0x01ff);

    gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] &= 0xff00;
    gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] |= (sp->pos_y & 0x00ff);
    
    /* Si se le ha aplicado alguna rotación/escalado */
    if(sp->rotated)
    {
      sp->rotated = FALSE;
      /* Desplazamiento en el eje x de la misma línea */
      dx = gba_fp_mult(sp->scale_h, gba_fp_cos(sp->angle));

      /* Desplazamiento en el eje y de la misma línea */
      dy = gba_fp_mult(sp->scale_h, -gba_fp_sin(sp->angle));

      /* Desplazamiento en el eje x de la siguiente línea */
      dmx = gba_fp_mult(sp->scale_v, gba_fp_sin(sp->angle));

      /* Desplazamiento en el eje y de la siguiente línea */
      dmy = gba_fp_mult(sp->scale_v, gba_fp_cos(sp->angle));

      rot_index = (gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] & (31 << 9)) >> 9;

      /* Actualizamos la OAM */
      gba_sprite_oam_shadow.rotation[rot_index].PA = dx;
      gba_sprite_oam_shadow.rotation[rot_index].PC = dy;
      gba_sprite_oam_shadow.rotation[rot_index].PB = dmx;
      gba_sprite_oam_shadow.rotation[rot_index].PD = dmy;
    }
  }
}

/*****************************************************************************/

/*
 * Muestra un sprite.
 * @param sp  El sprite
 */
inline void gba_sprite_show(sprite_struct *sp)
{
  sp->is_shown = 1;
}

/*****************************************************************************/

/*
 * Oculta un sprite.
 * @param sp  El sprite
 */
inline void gba_sprite_hide(sprite_struct *sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] &= 0xfe00;
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] |= SCREEN_WIDTH;

  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] &= 0xff00;
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] |= SCREEN_HEIGHT;

  sp->is_shown = 0;
}

/*****************************************************************************/

/*
 * Fija la posición inicial de un sprite.
 * @param sp  El sprite
 * @param x   Posición en x
 * @param y   Posición en y
 */
inline void gba_sprite_set_pos(sprite_struct *sp, short x, short y)
{
  sp->pos_x = x;
  sp->pos_y = y;
}

/*****************************************************************************/

/*
 * Mueve un sprite en la dirección indicada por la máscara.
 * @param sp El sprite
 * @param dx Desplazamiento en x
 * @param dy Desplazamiento en y
 */
void gba_sprite_move(sprite_struct *sp, short dx, short dy)
{
  gba_sprite_set_pos(sp, sp->pos_x+dx, sp->pos_y+dy);
}

/*****************************************************************************/

/*
 * Habilita el alpha-blending para un sprite
 * @param sp Puntero al sprite
 */
inline void gba_sprite_enable_bld(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] |= OBJ_MODE_BLD;
}

/*****************************************************************************/

/*
 * Anula el alpha-blending para un sprite
 * @param sp Puntero al sprite
 */
inline void gba_sprite_disable_bld(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] &= ~OBJ_MODE_BLD;
}

/*****************************************************************************/

/*
 * Voltea el sprite horizontalmente
 * @param sp Puntero al sprite
 */
inline void gba_sprite_flip_h(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] ^= OBJ_HORIZONTAL_FLIP;
}

/*****************************************************************************/

/*
 * Voltea el sprite verticalmente
 * @param sp Puntero al sprite
 */
inline void gba_sprite_flip_v(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] ^= OBJ_VERTICAL_FLIP;
}

/*****************************************************************************/

/*
 * Habilita la rotación y escalado de un sprite
 * @param sp        Puntero al sprite
 * @param rot_index Indice en la tabla de rotaciones para los parámetros
 */
inline void gba_sprite_enable_rotation(sprite_struct * sp, short rot_index)
{
  /* Activamos la rotación para el sprite */
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] |= OBJ_ROTATION;
  
  /* Fijamos su entrada en la tabla de rotaciones */
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] &= ~OBJ_ROTDATA(31);
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[1] |= OBJ_ROTDATA(rot_index);
}

/*****************************************************************************/

/*
 * Fija el ańgulo inicial de rotación hardware para un sprite.
 * @param sp     Puntero al sprite
 * @param angle  Angulo de rotación en grados enteros
 */
inline void gba_sprite_set_angle(sprite_struct * sp, int angle)
{
  sp->angle = angle;
  sp->rotated = TRUE;
}

/*****************************************************************************/

/*
 * Modifica el ángulo de rotación actual del sprite.
 * @param sp     Puntero al sprite
 * @param dangle Incremento/decremento al angulo actual de rotación
 */
inline void gba_sprite_rotate(sprite_struct * sp, int dangle)
{
  sp->angle += dangle;
  sp->rotated = TRUE;
}

/*****************************************************************************/

/*
 * Fija el escalado hardware inicial para un sprite.
 * @param sp      Puntero al sprite
 * @param scale_h Escalado horizontal
 * @param scale_v Escalado vertical
 */
inline void gba_sprite_set_scale(sprite_struct * sp, fixed_p scale_h, fixed_p scale_v)
{
  sp->scale_h = scale_h;
  sp->scale_v = scale_v;
  sp->rotated = TRUE;
}

/*****************************************************************************/

/*
 * Si la rotación del sprite está activada, dobla el tamaño del sprite.
 * En caso contrario, el sprite se oculta
 * @param sp       Puntero al sprite
 */
void inline gba_sprite_enable_double_size(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] |= OBJ_SIZE_DOUBLE;
}

/*****************************************************************************/

/*
 * Si la rotación del sprite está activada, restaura el tamaño del sprite
 * En caso contrario, vuelve a mostrar el sprite
 * @param sp       Puntero al sprite
 */
void inline gba_sprite_disable_double_size(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] &= ~OBJ_SIZE_DOUBLE;
}

/*****************************************************************************/

/*
 * Define una secuencia de frames para crear la animación del sprite
 * @param sp  Puntero al sprite
 * @param seq Vector que define la secuencia
 * @param len Longitud de la secuencia
 */
void inline gba_sprite_set_frame_seq(sprite_struct * sp, const short* seq, short len)
{
  sp->frame_seq = seq;
  sp->frame_seq_len = len;
  sp->frame_index = 0;
}

/*****************************************************************************/

/*
 * Avanza al siguiente frame de la animación
 * @param sp  Puntero al sprite
 */
void gba_sprite_next_frame(sprite_struct * sp)
{
  const void *frame = sp->data;
  short name = gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[2] & 0x3ff;

  if (sp->frame_seq)
  {
    sp->frame_index = gba_mod(sp->frame_index+1, sp->frame_seq_len);
    frame = sp->data + (sp->frame_size * sp->frame_seq[sp->frame_index]);
  }

  /* Copiamos los caracteres del frame a la memoria de vídeo */
  gba_dma_memcpy((void*)gba_vram.obj_data[name], frame, sp->frame_size);
}

/*****************************************************************************/

/*
 * Fija el tamaño de los pixels de los sprites en modo mosaico
 * @param h_size Tamaño horizontal del mosaico de los fondos (1-16)
 * @param v_size Tamaño vertical del mosaico de los fondos (1-16)
 */
inline void gba_sprite_set_mosaic_size(short h_size, short v_size)
{
  gba_bg_mosaic_shadow &= 0x00ff;
  gba_bg_mosaic_shadow |= (((v_size-1)  & 0x000f) << 12 ) | (((h_size-1) & 0x000f) << 8);
  gba_video_regs.MOSAIC =  gba_bg_mosaic_shadow;
}

/*****************************************************************************/

/*
 * Habilita el modo mosaico en el sprite.
 * @param sp  Puntero al sprite
 */
void gba_sprite_enable_mosaic(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] |= OBJ_MOSAIC;
}

/*****************************************************************************/

/*
 * Deshabilita el modo mosaico en el sprite.
 * @param sp  Puntero al sprite
 */
void gba_sprite_disable_mosaic(sprite_struct * sp)
{
  gba_sprite_oam_shadow.obj[sp->oam_entry].ATTRIBUTE[0] &= ~OBJ_MOSAIC;
}

/*****************************************************************************/

/*
 * Comprueba si dos sprites se solapan.
 * @param sp1  Puntero al primer sprite
 * @param sp2  Puntero al segundo sprite
 * @return TRUE si hay solapamiento o FALSE en otro caso
 */
char gba_sprite_overlap(sprite_struct * sp1, sprite_struct * sp2)
{
  char overlap = FALSE;

  /* Coordenadas de sp1 */
  short min_x1 = sp1->pos_x;
  short min_y1 = sp1->pos_y;
  short max_x1 = sp1->pos_x + sp1->width - 1;
  short max_y1 = sp1->pos_y + sp1->height -1;

  /* Coordenadas de sp2 */
  short min_x2 = sp2->pos_x;
  short min_y2 = sp2->pos_y;
  short max_x2 = sp2->pos_x + sp2->width - 1;
  short max_y2 = sp2->pos_y + sp2->height -1;
  
  /* Compruebo si hay solapamiento */
  if (min_x2 >= min_x1 && min_x2 <= max_x1 &&
      min_y2 >= min_y1 && min_y2 <= max_y1)
    overlap = TRUE;
  else if (max_x2 >= min_x1 && max_x2 <= max_x1 &&
           min_y2 >= min_y1 && min_y2 <= max_y1)
    overlap = TRUE;
  else if (min_x2 >= min_x1 && min_x2 <= max_x1 &&
           max_y2 >= min_y1 && max_y2 <= max_y1)
    overlap = TRUE;
  else if (max_x2 >= min_x1 && max_x2 <= max_x1 &&
           max_y2 >= min_y1 && max_y2 <= max_y1)
    overlap = TRUE;
  else if (min_x1 >= min_x2 && min_x1 <= max_x2 &&
           min_y1 >= min_y2 && min_y1 <= max_y2)
    overlap = TRUE;
  else if (max_x1 >= min_x2 && max_x1 <= max_x2 &&
           min_y1 >= min_y2 && min_y1 <= max_y2)
    overlap = TRUE;
  else if (min_x1 >= min_x2 && min_x1 <= max_x2 &&
           max_y1 >= min_y2 && max_y1 <= max_y2)
    overlap = TRUE;
  else if (max_x1 >= min_x2 && max_x1 <= max_x2 &&
           max_y1 >= min_y2 && max_y1 <= max_y2)
    overlap = TRUE;

  return overlap;
}

/*****************************************************************************/

