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
#ifndef gba_draw_h
#define gba_draw_h

#include "gba.h"

/*****************************************************************************/

/*
 * Identificadores para los búferes de vídeo en los modos con doble búfer
 */
#define FRONT_BUFFER           0
#define BACK_BUFFER            1

/*****************************************************************************/

/*
 * Estructura para manejar una fuente de pantalla.
 */
typedef struct
{
  u_char        width;         /* Ancho de los caracteres */
  u_char        height;        /* Alto de los caracteres */
  u_char        first_ascii;   /* Código ASCII del primer carácter de la fuente */
  u_char        last_ascii;    /* Código ASCII del último carácter de la fuente */
  const u_char* bitmaps;       /* Puntero a los bitmaps de los caracteres */
} font_struct;

/*****************************************************************************/

/*
 * Función para fijar el buffer que se usará para dibujar en los modos bitmap
 * con doble buffer (modos 4 y 5).
 * @param buffer Identificador del buffer (FRONT_BUFFER o BACK_BUFFER)
 */
inline void gba_draw_set_buffer(u_short buffer);

/*****************************************************************************/

/*
 * Función para fijar el color que se usará para dibujar en los modos bitmap.
 * Para los modos 3 y 5 se usará como una tripleta RGB de 15 bits.
 * Para el modo 4 sólo se usarán los 8 bits inferiores como índice de la paleta.
 * @param color El color
 */
inline void gba_draw_set_color(u_short color);

/*****************************************************************************/

/*
 * Función para fijar las coordenadas del cursor.
 * @param x coordenada x
 * @param y coordenada y
 */
inline void gba_draw_set_cursor(u_char x, u_char y);

/*****************************************************************************/

/*
 * Función para fijar la fuente por defecto.
 * @param font La fuente
 */
inline void gba_draw_set_font(font_struct font);

/*****************************************************************************/

/*
 * Función para dibujar un pixel en los modos 3, 4 y 5
 * @param x   Coordenada x de la pantalla
 * @param y   Coordenada y de la pantalla
 */
void gba_draw_pixel(u_short x, u_short y);

/*****************************************************************************/

/*
 * Función para dibujar una línea mediante el algoritmo de Bresenham
 * @param x1  Coordenada x del primer extremo
 * @param y1  Coordenada y del primer extremo
 * @param x2  Coordenada x del segundo extremo
 * @param y2  Coordenada y del segundo extremo
 */
void gba_draw_line(u_short x1, u_short y1, u_short x2, u_short y2);

/*****************************************************************************/

/*
 * Función para dibujar un círculo
 * @param xCenter  Coordenada x del centro
 * @param yCenter  Coordenada y del centro
 * @param radius   Radio
 */
void gba_draw_circle(u_short xCenter, u_short yCenter, u_short radius);

/*****************************************************************************/

/*
 * Función para dibujar una caja coloreada
 * @param left   Coordenada x de la esquina superior-izquierda
 * @param top    Coordenada y de la esquina superior-izquierda
 * @param right  Coordenada x de la esquina inferior-derecha
 * @param bottom Coordenada y de la esquina inferior-derecha
 */
void gba_draw_box(u_short left, u_short top, u_short right, u_short bottom);

/*****************************************************************************/

/*
 * Función para dibujar un carácter en pantalla.
 * Previamente se debe fijar el cursor a la posición donde se empezará a
 * escribir, que por defecto es la (0,0).
 * De momento no se han implementado ni scroll de pantalla ni caracteres de
 * control.
 * @param the_char El carácter
 */
void gba_draw_char(u_char the_char);

/*****************************************************************************/

#endif /* gba_draw_h */
