/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas de sonido                                 */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_sound_h
#define gba_sound_h

#include "gba.h"
#include "gba_timer.h"

/*****************************************************************************/

/*
 * Identificadores de los los canales de sonido directo
 */
#define SOUND_DSA                      0
#define SOUND_DSB                      1

/*
 * Constantes para seleccionar el volumen de los canales de sonido directo
 */
#define SOUND_DS_OUTPUT_RATIO_50       0       /*  50% */
#define SOUND_DS_OUTPUT_RATIO_100      1       /* 100% */

/*
 * Constantes para seleccionar el tipo de salida.
 */
#define SOUND_DS_OUTPUT_TO_RIGHT  (1 << 0)
#define SOUND_DS_OUTPUT_TO_LEFT   (1 << 1)
#define SOUND_DS_OUTPUT_TO_BOTH   (SOUND_DS_OUTPUT_TO_LEFT | SOUND_DS_OUTPUT_TO_RIGHT)


/*****************************************************************************/

/*
 * Estructura de datos para manejar los canales de sonido directo (DSA y DSB)
 */
typedef struct
{                              /* desplazamientos en SOUNDCNT_H */
  u_char     volume_offset;    /* volumen */
  u_char     lr_offset;        /* lineas izquierda y derecha */
  u_char     timer_offset;     /* temporizador */
  u_char     reset_offset;     /* reset */
  gba_word32 FIFO;             /* Puntero a la cola FIFO */
} sound_ds_struct;

/*****************************************************************************/

/*
 * Habilita el controlador de sonido
 */
inline void gba_sound_enable();

/*****************************************************************************/

/*
 * Deshabilita el controlador de sonido
 */
inline void gba_sound_disable();

/*****************************************************************************/

/*
 * Inicializa el temporizador que se usará en un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 * @param timer   Temporizador (sólo TIMER0 o TIMER1)
 */
inline void gba_sound_ds_set_timer(u_char channel, u_char timer);

/*****************************************************************************/

/*
 * Inicializa el volumen de un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 * @param volume  Volumen (SOUND_DS_OUTPUT_RATIO_50 o SOUND_DS_OUTPUT_RATIO_100)
 */
inline void gba_sound_ds_set_volume(u_char channel, u_char volume);

/*****************************************************************************/

/*
 * Inicializa la salida de un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 * @param output  Tipo de salida  (SOUND_DS_OUTPUT_TO_RIGHT,
 *                SOUND_DS_OUTPUT_TO_LEFT o SOUND_DS_OUTPUT_TO_BOTH)
 */
inline void gba_sound_ds_set_output(u_char channel, u_char output);

/*****************************************************************************/

/*
 * Resetea la cola de un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 */
inline void gba_sound_ds_fifo_reset(u_char channel);

/*****************************************************************************/

/*
 * Reproduce una muestra de sonido.
 *
 * Usa los temporizadores TIMER0 y TIMER1 para la reproducción. TIMER0 mide el
 * tiempo entre muestras y TIMER1 va contando el número de muestras que se van
 * reproduciendo.
 * También programa una interrupción en TIMER1 que se procucirá cuando se haya
 * terminado la reproducción y que se atenderá mediante la función gba_sound_ds_stop
 *
 * @param channel Canal de sonido directo (SOUND_DSA o SOUND_DSB)
 * @param samples Buffer con las muestras
 * @param size    Tamaño del buffer en bytes
 * @param rate    Frecuencia de muestreo
 */
void gba_sound_ds_play(u_char channel, const void* samples, u_short size, u_short rate);

/*****************************************************************************/

/*
 * Finaliza la reproducción de sonido
 */
inline void gba_sound_ds_stop();

/*****************************************************************************/

#endif /* gba_sound_h */
