/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas de vídeo                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdlib.h>
#include "gba_draw.h"
#include "gba_bg.h"

/*****************************************************************************/

/*
 * Variables estáticas de la biblioteca
 */

u_short gba_draw_def_buffer = FRONT_BUFFER; /* Buffer por defecto para dibujar pixels */
u_short gba_draw_def_color = 0;         /* Color por defecto para dibujar pixels */
u_char gba_draw_def_cursor_x = 0;       /* Posición x por defecto para el cursor */
u_char gba_draw_def_cursor_y = 0;       /* Posición y por defecto para el cursor */
font_struct gba_draw_def_font;          /* Fuente por defecto */

/*****************************************************************************/

/*
 * Función para fijar el buffer que se usará para dibujar en los modos bitmap
 * con doble buffer (modos 4 y 5).
 * @param buffer Identificador del buffer (FRONT_BUFFER o BACK_BUFFER)
 */
inline void gba_draw_set_buffer(u_short buffer)
{
  gba_draw_def_buffer = buffer;
}

/*****************************************************************************/

/*
 * Función para fijar el color que se usará para dibujar en los modos bitmap.
 * Para los modos 3 y 5 se usará como una tripleta RGB de 15 bits.
 * Para el modo 4 sólo se usarán los 8 bits inferiores como índice de la paleta.
 * @param color El color
 */
inline void gba_draw_set_color(u_short color)
{
  gba_draw_def_color = color;
}

/*****************************************************************************/

/*
 * Función para fijar las coordenadas del cursor.
 * @param x coordenada x
 * @param y coordenada y
 */
inline void gba_draw_set_cursor(u_char x, u_char y)
{
  gba_draw_def_cursor_x = MIN(x, gba_bg_width(BG2));
  gba_draw_def_cursor_y = MIN(y, gba_bg_height(BG2));
}

/*****************************************************************************/

/*
 * Función para fijar la fuente por defecto.
 * @param font La fuente
 */
inline void gba_draw_set_font(font_struct font)
{
  gba_draw_def_font = font;
}

/*****************************************************************************/

/*
 * Función para dibujar un pixel en los modos 3, 4 y 5
 * @param x   Coordenada x de la pantalla
 * @param y   Coordenada y de la pantalla
 */
void gba_draw_pixel(u_short x, u_short y)
{
  // TODO
  // This function should check that the arguments are correct
  // x should be lesser than SCREEN_WIDTH
  // x should be lesser than SCREEN_HEIGHT
  u_short pixel;
  gba_word16 video_buffer = gba_vram.video_buffer;
  short bg_mode = gba_bg_get_mode();
  u_short bg_width = gba_bg_width(BG2);
  u_short bg_height = gba_bg_height(BG2);
  u_short offset = x + bg_width*y;

  
  if (gba_draw_def_buffer==BACK_BUFFER)
    video_buffer = gba_vram.back_buffer;

  if (x<bg_width && y<bg_height)
  {
    if (bg_mode == BG_MODE3)
    {
      gba_vram.video_buffer[offset] = gba_draw_def_color;
    }
    else if (bg_mode == BG_MODE4)
    {
      offset = offset >> 1;
      pixel = video_buffer[offset];
      if (x & 1)
        video_buffer[offset] = ((gba_draw_def_color & 0x00ff) << 8) + (pixel & 0x00ff);
      else
        video_buffer[offset] = (pixel & 0xff00) + (gba_draw_def_color & 0x00ff);
    }
    else if (bg_mode == BG_MODE5)
    {
      video_buffer[offset] = gba_draw_def_color;
    }
  }
}

/*****************************************************************************/

/*
 * Función para dibujar una línea mediante el algoritmo de Bresenham
 * @param x1  Coordenada x del primer extremo
 * @param y1  Coordenada y del primer extremo
 * @param x2  Coordenada x del segundo extremo
 * @param y2  Coordenada y del segundo extremo
 */
void gba_draw_line(u_short x1, u_short y1, u_short x2, u_short y2)
{
  // TODO
  // This function should correctly handle both negative values and
  // greater than SCREEN_WIDTH and SCREEN_HEIGHT values
  short i, deltax, deltay, numpixels;
  short d, dinc1, dinc2;
  short x, xinc1, xinc2;
  short y, yinc1, yinc2;
  
  // calculate deltaX and deltaY
  deltax = abs(x2 - x1);
  deltay = abs(y2 - y1);
  
  //initialize
  if(deltax >= deltay)
  {
    //If x is independent variable
    numpixels = deltax + 1;
    d = (2 * deltay) - deltax;
    dinc1 = deltay << 1;
    dinc2 = (deltay - deltax) << 1;
    xinc1 = 1;
    xinc2 = 1;
    yinc1 = 0;
    yinc2 = 1;
  }
  else
  {
    //if y is independent variable
    numpixels = deltay + 1;
    d = (2 * deltax) - deltay;
    dinc1 = deltax << 1;
    dinc2 = (deltax - deltay) << 1;
    xinc1 = 0;
    xinc2 = 1;
    yinc1 = 1;
    yinc2 = 1;
  }

  //move the right direction
  if(x1 > x2)
  {
    xinc1 = -xinc1;
    xinc2 = -xinc2;
  }
  if(y1 > y2)
  {
    yinc1 = -yinc1;
    yinc2 = -yinc2;
  }
  x = x1;
  y = y1;

  //draw the pixels
  for(i = 1; i < numpixels; i++)
  {
    gba_draw_pixel(x, y);
    if(d < 0)
    {
      d = d + dinc1;
      x = x + xinc1;
      y = y + yinc1;
    }
    else
    {
      d = d + dinc2;
      x = x + xinc2;
      y = y + yinc2;
    }
  }
}

/*****************************************************************************/

/*
 * Función para dibujar un círculo
 * @param xCenter  Coordenada x del centro
 * @param yCenter  Coordenada y del centro
 * @param radius   Radio
 */
void gba_draw_circle(u_short xCenter, u_short yCenter, u_short radius)
{
  // TODO
  // This function should correctly handle both negative values and
  // greater than SCREEN_WIDTH and SCREEN_HEIGHT values

  // TODO
  // A function that drew a filled circle would be interesting.
  short i, deltax, deltay, numpixels;
  short x = 0;
  short y = radius;
  short p = 3 - 2 * radius;
  while (x <= y)
  {
    gba_draw_pixel(xCenter + x, yCenter + y);
    gba_draw_pixel(xCenter - x, yCenter + y);
    gba_draw_pixel(xCenter + x, yCenter - y);
    gba_draw_pixel(xCenter - x, yCenter - y);
    gba_draw_pixel(xCenter + y, yCenter + x);
    gba_draw_pixel(xCenter - y, yCenter + x);
    gba_draw_pixel(xCenter + y, yCenter - x);
    gba_draw_pixel(xCenter - y, yCenter - x);
    if (p < 0)
      p += 4 * x++ + 6;
    else
      p += 4 * (x++ - y--) + 10;
  }
}

/*****************************************************************************/

/*
 * Función para dibujar una caja coloreada
 * @param left   Coordenada x de la esquina superior-izquierda
 * @param top    Coordenada y de la esquina superior-izquierda
 * @param right  Coordenada x de la esquina inferior-derecha
 * @param bottom Coordenada y de la esquina inferior-derecha
 */
void gba_draw_box(u_short left, u_short top, u_short right, u_short bottom)
{
  // TODO
  // This function should correctly handle both negative values and
  // greater than SCREEN_WIDTH and SCREEN_HEIGHT values

  // TODO
  // A function that drew an empty box would be interesting.
  short i, deltax, deltay, numpixels;
  u_short x, y;

  for(y = top; y < bottom; y++)
    for(x = left; x < right; x++)
      gba_draw_pixel(x, y);
}

/*****************************************************************************/

/*
 * Función para dibujar un carácter en pantalla.
 * Previamente se debe fijar el cursor a la posición donde se empezará a
 * escribir, que por defecto es la (0,0).
 * De momento no se han implementado ni scroll de pantalla ni caracteres de
 * control.
 * @param the_char El carácter
 */
void gba_draw_char(u_char the_char)
{
  // TODO
  // This function should correctly handle both negative values and
  // greater than SCREEN_WIDTH and SCREEN_HEIGHT values
  short i, deltax, deltay, numpixels;
  u_short i, j;          /* Para recorrer el bitmap del carácter */
  u_char pintar;         /* Si es TRUE hay que pintar el píxel del carácter */
  u_short bitmaps_width; /* Ancho total de los bitmaps en píxeles */
  u_short offset;        /* Primer pixel del caracter */
  
  /* Sólo puedo dibujar los caracteres que están en la fuente */
  if (the_char < gba_draw_def_font.first_ascii || the_char > gba_draw_def_font.last_ascii)
    return;
  
  bitmaps_width = (gba_draw_def_font.last_ascii - gba_draw_def_font.first_ascii + 1) * gba_draw_def_font.width;
  offset = the_char * gba_draw_def_font.width;

  for(j = 0; j < gba_draw_def_font.height ; j++)
  {
    for (i = 0; i < gba_draw_def_font.width; i++)
    {
        // Selecciono un pixel de la fuente
        pintar = ((u_char*)gba_draw_def_font.bitmaps)[offset+i];
        
        // Si el pintar = 1, se colorea el píxel en la pantalla
        if (pintar)
          gba_draw_pixel(gba_draw_def_cursor_x+i, gba_draw_def_cursor_y+j);
    }
    offset += bitmaps_width;
  }

  /* Incremento la posición x del cursor para el siguiente caracter */
  gba_draw_def_cursor_x += gba_draw_def_font.width;
  gba_draw_def_cursor_x = MIN(gba_draw_def_cursor_x, gba_bg_width(BG2));

}

/*****************************************************************************/

