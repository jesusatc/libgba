/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas de vídeo                                  */
/*                                                                           */
/*****************************************************************************/

#include "gba_bg.h"
#include "gba_video.h"
#include "gba_dma.h"
#include "gba_fp.h"

/*****************************************************************************/

/*
 * Variables estáticas de la biblioteca
 */

bg_struct gba_bgs[4]=
{
  /* Fondo 0 */
  {
    VIDEO_BG0,                            /* Máscara en DISPCNT */
    (gba_word16) &(gba_video_regs.BG0CNT),   /* Puntero al registro de control */
    (gba_word16) &(gba_video_regs.BG0HOFS),  /* Puntero al registro de desplazamiento horizontal */
    (gba_word16) &(gba_video_regs.BG0VOFS),  /* Puntero al registro de desplazamiento vertical */
    NULL,                                 /* Puntero al registro PA (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero al registro PB (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero al registro PC (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero al registro PD (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero a la coordenada x del punto de referencia (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero a la coordenada y del punto de referencia (sólo para los fondos de rotación) */
    0,                                    /* Bloque para almacenar los caracteres */
    0,                                    /* Bloque para almacenar el mapa que define el fondo */
    0,                                    /* Desplazamiento horizontal */
    0,                                    /* Desplazamiento vertical */
    0,                                    /* Ancho en pixels */
    0,                                    /* Alto en pixels */
    I2FP(1),                              /* Factor de escalado horizontal*/
    I2FP(1),                              /* Factor de escalado vertical */
    0,                                    /* Angulo de rotación en grados */
    0,                                    /* Punto de referencia para la rotación - x */
    0                                     /* Punto de referencia para la rotación - y */
  },
  
  /* Fondo 1 */
  {
    VIDEO_BG1,                            /* Máscara en DISPCNT */
    (gba_word16) &(gba_video_regs.BG1CNT),   /* Puntero al registro de control */
    (gba_word16) &(gba_video_regs.BG1HOFS),  /* Puntero al registro de desplazamiento horizontal */
    (gba_word16) &(gba_video_regs.BG1VOFS),  /* Puntero al registro de desplazamiento vertical */
    NULL,                                 /* Puntero al registro PA (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero al registro PB (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero al registro PC (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero al registro PD (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero a la coordenada x del punto de referencia (sólo para los fondos de rotación) */
    NULL,                                 /* Puntero a la coordenada y del punto de referencia (sólo para los fondos de rotación) */
    0,                                    /* Bloque para almacenar los caracteres */
    0,                                    /* Bloque para almacenar el mapa que define el fondo */
    0,                                    /* Desplazamiento horizontal */
    0,                                    /* Desplazamiento vertical */
    0,                                    /* Ancho en pixels */
    0,                                    /* Alto en pixels */
    I2FP(1),                              /* Factor de escalado horizontal*/
    I2FP(1),                              /* Factor de escalado vertical */
    0,                                    /* Angulo de rotación en grados */
    0,                                    /* Punto de referencia para la rotación - x */
    0                                     /* Punto de referencia para la rotación - y */
  },

  /* Fondo 2 */
  {
    VIDEO_BG2,                            /* Máscara en DISPCNT */
    (gba_word16) &(gba_video_regs.BG2CNT),   /* Puntero al registro de control */
    (gba_word16) &(gba_video_regs.BG2HOFS),  /* Puntero al registro de desplazamiento horizontal */
    (gba_word16) &(gba_video_regs.BG2VOFS),  /* Puntero al registro de desplazamiento vertical */
    (gba_word16) &(gba_video_regs.BG2PA),    /* Puntero al registro PA (sólo para los fondos de rotación) */
    (gba_word16) &(gba_video_regs.BG2PB),    /* Puntero al registro PB (sólo para los fondos de rotación) */
    (gba_word16) &(gba_video_regs.BG2PC),    /* Puntero al registro PC (sólo para los fondos de rotación) */
    (gba_word16) &(gba_video_regs.BG2PD),    /* Puntero al registro PD (sólo para los fondos de rotación) */
    (gba_word32) &(gba_video_regs.BG2X),     /* Puntero a la coordenada x del punto de referencia (sólo para los fondos de rotación) */
    (gba_word32) &(gba_video_regs.BG2Y),     /* Puntero a la coordenada y del punto de referencia (sólo para los fondos de rotación) */
    0,                                    /* Bloque para almacenar los caracteres */
    0,                                    /* Bloque para almacenar el mapa que define el fondo */
    0,                                    /* Desplazamiento horizontal */
    0,                                    /* Desplazamiento vertical */
    0,                                    /* Ancho en pixels */
    0,                                    /* Alto en pixels */
    I2FP(1),                              /* Factor de escalado horizontal*/
    I2FP(1),                              /* Factor de escalado vertical */
    0,                                    /* Angulo de rotación en grados */
    0,                                    /* Punto de referencia para la rotación - x */
    0                                     /* Punto de referencia para la rotación - y */
  },

  /* Fondo 3 */
  {
    VIDEO_BG3,                            /* Máscara en DISPCNT */
    (gba_word16) &(gba_video_regs.BG3CNT),   /* Puntero al registro de control */
    (gba_word16) &(gba_video_regs.BG3HOFS),  /* Puntero al registro de desplazamiento horizontal */
    (gba_word16) &(gba_video_regs.BG3VOFS),  /* Puntero al registro de desplazamiento vertical */
    (gba_word16) &(gba_video_regs.BG2PA),    /* Puntero al registro PA (sólo para los fondos de rotación) */
    (gba_word16) &(gba_video_regs.BG2PB),    /* Puntero al registro PB (sólo para los fondos de rotación) */
    (gba_word16) &(gba_video_regs.BG2PC),    /* Puntero al registro PC (sólo para los fondos de rotación) */
    (gba_word16) &(gba_video_regs.BG2PD),    /* Puntero al registro PD (sólo para los fondos de rotación) */
    (gba_word32) &(gba_video_regs.BG2X),     /* Puntero a la coordenada x del punto de referencia (sólo para los fondos de rotación) */
    (gba_word32) &(gba_video_regs.BG2Y),     /* Puntero a la coordenada y del punto de referencia (sólo para los fondos de rotación) */
    0,                                    /* Bloque para almacenar los caracteres */
    0,                                    /* Bloque para almacenar el mapa que define el fondo */
    0,                                    /* Desplazamiento horizontal */
    0,                                    /* Desplazamiento vertical */
    0,                                    /* Ancho en pixels */
    0,                                    /* Alto en pixels */
    I2FP(1),                              /* Factor de escalado horizontal*/
    I2FP(1),                              /* Factor de escalado vertical */
    0,                                    /* Angulo de rotación en grados */
    0,                                    /* Punto de referencia para la rotación - x */
    0                                     /* Punto de referencia para la rotación - y */
  }
};

/*
 * Copia del registro MOSAIC. Es necesaria porque el registro MOSAIC no se
 * puede leer. Es de sólo escritura.
 */
short gba_bg_mosaic_shadow = 0x0000;

/*****************************************************************************/

/*
 * Función que retorna el modo de los fondos.
 */
inline short gba_bg_get_mode(void)
{
  return gba_video_regs.DISPCNT & (BG_MODE1|BG_MODE2|BG_MODE3|BG_MODE4|BG_MODE5);
}

/*****************************************************************************/

/*
 * Función para fijar el modo de los fondos.
 * @param mode Modo (BG_MODE0, BG_MODE1, BG_MODE2, BG_MODE3, BG_MODE4, BG_MODE5)
 */
void gba_bg_set_mode(u_char mode)
{
  gba_video_regs.DISPCNT = mode;
  if (mode < BG_MODE3)
  {
    gba_bgs[0].width  = 0;
    gba_bgs[0].height = 0;
    gba_bgs[1].width  = 0;
    gba_bgs[1].height = 0;
    gba_bgs[2].width  = 0;
    gba_bgs[2].height = 0;
    gba_bgs[3].width  = 0;
    gba_bgs[3].height = 0;
  }
  else if (mode < BG_MODE5)
  {
    gba_bgs[2].width = BG_MODE_WIDTH3;
    gba_bgs[2].height = BG_MODE_HEIGHT3;
  }
  else /* BG_MODE5 */
  {
    gba_bgs[2].width = BG_MODE_WIDTH5;
    gba_bgs[2].height = BG_MODE_HEIGHT5;
  }

}

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
                      short sizeof_chars, const void* chars, const void* map)
{
  short bg_mode = gba_bg_get_mode();

  short sizeof_map_entry;
  short sizeof_map;

  gba_bgs[id].char_block = char_block;      /* Bloque de caracteres */
  gba_bgs[id].screen_block = screen_block;  /* Bloque del mapa */

  /* Configuramos el fondo */
  *(gba_bgs[id].BGCNT) = color | size | VIDEO_CHAR_BLOCK(char_block) |
                                        VIDEO_SCREEN_BLOCK(screen_block);

  /*
   * Comprobamos si es un fondo de texto sin rotación
   *  - en el modo 0 los cuatro fondos son de texto
   *  - en el modo 1 sólo los fondos 0 y 1 son de texto
   */
  if (bg_mode==0 || (bg_mode==1 && id<BG2))
  {
    /* Si es un fondo sin rotación, cada entrada del mapa ocupa 2 bytes */
    sizeof_map_entry = 2;

    if (size & VIDEO_BG_WIDTH_TEXT_512)
      gba_bgs[id].width = 512;
    else
      gba_bgs[id].width = 256;
      
    if (size & VIDEO_BG_HEIGHT_TEXT_512)
      gba_bgs[id].height = 512;
    else
      gba_bgs[id].height = 256;
  }
  /*
   * Comprobamos si es un fondo de texto con rotación
   *  - en el modo 1 sólo el fondo 2 es de rotación
   *  - en el modo 2 sólo los fondos 2 y 3 son de rotación
   */
  else if ((bg_mode==1 && id==BG2) || (bg_mode==2 && (id==BG2 || id==BG3)))
  {
    /* Si es un fondo con rotación, cada entrada del mapa ocupa 1 byte */
    sizeof_map_entry = 1;

    switch (size)
    {
      case VIDEO_BG_SIZE_ROT_128x128:
        gba_bgs[id].width = 128;
        gba_bgs[id].height = 128;
        break;
      case VIDEO_BG_SIZE_ROT_256x256:
        gba_bgs[id].width = 256;
        gba_bgs[id].height = 256;
        break;
      case VIDEO_BG_SIZE_ROT_512x512:
        gba_bgs[id].width = 512;
        gba_bgs[id].height = 512;
        break;
      case VIDEO_BG_SIZE_ROT_1024x1024:
        gba_bgs[id].width = 1024;
        gba_bgs[id].height = 1024;
        break;
    }
  }
  else /* Si no está definido, retornamos sin hacer nada */
    return;

  /* Tamaño del mapa en bytes (cada caracter tiene 64 pixels) */
  sizeof_map = (gba_bgs[id].width*gba_bgs[id].height*sizeof_map_entry) / 64;
    
  /* Copiamos los caracteres en la memoria de video */
  gba_dma_memcpy((void*) gba_vram.char_block[gba_bgs[id].char_block],
                 chars, sizeof_chars);

  /* Copiamos el mapa en la memoria del fondo 0 */
  gba_dma_memcpy((void*) gba_vram.screen_block[gba_bgs[id].screen_block],
                 map, sizeof_map);
}

/*****************************************************************************/

/*
 * Función para inicializar el frontbuffer en modo bitmap (BG2, modos 3-5).
 * @param bitmap Puntero al buffer de pixels
 */
void gba_bg_init_front_buffer(const void* bitmap)
{
  char pix_size = 1;
  if(gba_bg_get_mode()==BG_MODE3)
    pix_size = 2;
  gba_dma_memcpy((void*)gba_vram.front_buffer, (void*)bitmap,
                 gba_bgs[BG2].width*gba_bgs[BG2].height*pix_size);
}

/*****************************************************************************/

/*
 * Función para inicializar el backbuffer en modo bitmap (BG2, modos 4-5).
 * @param bitmap Puntero al buffer de pixels
 */
void gba_bg_init_back_buffer(const void* bitmap)
{
  gba_dma_memcpy((void*)gba_vram.back_buffer, (void*)bitmap,
                 gba_bgs[BG2].width*gba_bgs[BG2].height);
}

/*****************************************************************************/

/*
 * Iniciliza una paleta de 256 colores para el fondo.
 * @param palette La paleta
 */
inline void gba_bg_init_palette256(const void * palette)
{
  gba_dma_memcpy((void*) gba_palette.bg256, palette, sizeof(gba_palette256));
}

/*****************************************************************************/

/*
 * Iniciliza una de las 16 paletas de 16 colores para el fondo.
 * @param index   Indice de la paleta (0..15)
 * @param palette La paleta
 */
inline void gba_bg_init_palette16(short index, const void * palette)
{
  gba_dma_memcpy((void*) gba_palette.bg16[index], palette, sizeof(gba_palette16));
}

/*****************************************************************************/

/*
 * Muestra un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_show(short id)
{
  gba_video_regs.DISPCNT |= gba_bgs[id].mask;
}

/*****************************************************************************/

/*
 * Oculta un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_hide(short id)
{
  gba_video_regs.DISPCNT &= ~gba_bgs[id].mask;
}

/*****************************************************************************/

/*
 * Retorna el ancho en pixels de un fondo
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline short gba_bg_width(short id)
{
  return gba_bgs[id].width;
}

/*****************************************************************************/

/*
 * Retorna el alto en pixels de un fondo
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline short gba_bg_height(short id)
{
  return gba_bgs[id].height;
}

/*****************************************************************************/

/*
 * Fija el tamaño de los pixels de los fondos en modo mosaico.
 * @param h_size Tamaño horizontal del mosaico de los fondos (1-16)
 * @param v_size Tamaño vertical del mosaico de los fondos (1-16)
 */
inline void gba_bg_set_mosaic_size(short h_size, short v_size)
{
  gba_bg_mosaic_shadow &= 0xff00;
  gba_bg_mosaic_shadow |= (((v_size-1) & 0x000f) << 4 ) | ((h_size-1) & 0x000f);
  gba_video_regs.MOSAIC =  gba_bg_mosaic_shadow;
}

/*****************************************************************************/

/*
 * Habilita el modo mosaico en un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_enable_mosaic(short id)
{
  *(gba_bgs[id].BGCNT) |= VIDEO_BG_MOSAIC;
}

/*****************************************************************************/

/*
 * Deshabilita el modo mosaico en un fondo.
 * @param id Identificador (BG0, BG1, BG2, BG3)
 */
inline void gba_bg_disable_mosaic(short id)
{
  *(gba_bgs[id].BGCNT) &= ~VIDEO_BG_MOSAIC;
}

/*****************************************************************************/

/*
 * Función para aplicar desplazamiento hardware a los fondos.
 * @param bg Puntero al fondo
 * @param dx Desplazamiento horizontal
 * @param dy Desplazamiento vertical
 */
inline void gba_bg_scroll(short id, short dx, short dy)
{
  gba_bgs[id].ofs_h += dx;
  gba_bgs[id].ofs_v += dy;

  *(gba_bgs[id].BGHOFS) = gba_bgs[id].ofs_h;
  *(gba_bgs[id].BGVOFS) = gba_bgs[id].ofs_v;
}

/*****************************************************************************/


/*
 * Función para actualizar los atributos de rotación/escalado.
 * @param id Identificador (BG2, BG3)
 */
void gba_bg_update_rotation(short id)
{
  fixed_p dx, dy, dmx, dmy;
 
  /* Desplazamiento en el eje x de la misma línea */
  dx = gba_fp_mult(gba_bgs[id].scale_h, gba_fp_cos(gba_bgs[id].rot_angle));

  /* Desplazamiento en el eje y de la misma línea */
  dy = gba_fp_mult(gba_bgs[id].scale_h, -gba_fp_sin(gba_bgs[id].rot_angle));

  /* Desplazamiento en el eje x de la siguiente línea */
  dmx = gba_fp_mult(gba_bgs[id].scale_v, gba_fp_sin(gba_bgs[id].rot_angle));

  /* Desplazamiento en el eje y de la siguiente línea */
  dmy = gba_fp_mult(gba_bgs[id].scale_v, gba_fp_cos(gba_bgs[id].rot_angle));

  /* Actualizamos los registros */
  *(gba_bgs[id].BGX)  = I2FP(gba_bgs[id].rot_x);
  *(gba_bgs[id].BGY)  = I2FP(gba_bgs[id].rot_y);
  *(gba_bgs[id].BGPA) = dx;
  *(gba_bgs[id].BGPC) = dy;
  *(gba_bgs[id].BGPB) = dmx;
  *(gba_bgs[id].BGPD) = dmy;
}

/*****************************************************************************/

/*
 * Modifica el centro de rotación actual del fondo.
 * @param id Identificador (BG2, BG3)
 * @param dx Incremento/decremento horizontal
 * @param dy Incremento/decremento vertical
 */
inline void gba_bg_move_rotation_center(short id, int dx, int dy)
{
  gba_bgs[id].rot_x += dx;
  gba_bgs[id].rot_y += dy;
  gba_bg_update_rotation(id);
}

/*****************************************************************************/

/*
 * Modifica el ángulo de rotación actual del fondo.
 * @param id     Identificador (BG2, BG3)
 * @param dangle Incremento/decremento al angulo actual de rotación
 */
inline void gba_bg_rotate(short id, int dangle)
{
  gba_bgs[id].rot_angle += dangle;
  gba_bg_update_rotation(id);
}

/*****************************************************************************/

/*
 * Modifica el escalado actual del fondo.
 * @param id       Identificador (BG2, BG3)
 * @param dscale_h Incremento/decremento escalado horizontal
 * @param dscale_v Incremento/decremento escalado vertical
 */
inline void gba_bg_scale(short id, fixed_p dscale_h, fixed_p dscale_v)
{
  gba_bgs[id].scale_h += dscale_h;
  gba_bgs[id].scale_v += dscale_v;
  gba_bg_update_rotation(id);
}

/*****************************************************************************/

/*
 * Repite el fondo para llenar la pantalla.
 * @param id Identificador (BG2, BG3)
 */
inline void gba_bg_overflow_wraparound(short id)
{
  *(gba_bgs[id].BGCNT) |= VIDEO_BG_WRAPAROUND;
}

/*****************************************************************************/

/*
 * Deja transparente la parte de pantalla que no ocupe un fondo de rotación.
 * @param id Identificador (BG2, BG3)
 */
inline void gba_bg_overflow_transparent(short id)
{
  *(gba_bgs[id].BGCNT) &= ~VIDEO_BG_WRAPAROUND;
}

/*****************************************************************************/

