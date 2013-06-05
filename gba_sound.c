/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas de sonido                                 */
/*                                                                           */
/*****************************************************************************/

#include "gba_sound.h"
#include "gba_irq.h"
#include "gba_timer.h"
#include "gba_dma.h"
#include "gba_bios.h"

/*****************************************************************************/

/*
 * Variables estáticas de la biblioteca
 */

sound_ds_struct gba_sound_dss[2]=
{
  /* SOUND_DSA */
  {
    2,         /* SOUNDCNT_H: desplazamiento para el volumen */
    8,         /* SOUNDCNT_H: desplazamiento para las lineas L y R */
    10,        /* SOUNDCNT_H: desplazamiento para el temporizador */
    11,        /* SOUNDCNT_H: desplazamiento para el reset */
    (gba_word32) &(gba_sound_regs.FIFO_A)  /* Puntero a la cola FIFO */
  },

  /* SOUND_DSB */
  {
    3,         /* SOUNDCNT_H: desplazamiento para el volumen */
    12,        /* SOUNDCNT_H: desplazamiento para las lineas L y R */
    14,        /* SOUNDCNT_H: desplazamiento para el temporizador */
    15,        /* SOUNDCNT_H: desplazamiento para el reset */
    (gba_word32) &(gba_sound_regs.FIFO_B) /* Puntero a la cola FIFO */
  }
};

/*****************************************************************************/

/*
 * Habilita el controlador de sonido
 */
inline void gba_sound_enable()
{
  gba_sound_regs.SOUNDCNT_X |= SOUND_ENABLE;
}

/*****************************************************************************/

/*
 * Deshabilita el controlador de sonido
 */
inline void gba_sound_disable()
{
  gba_sound_regs.SOUNDCNT_X &= ~SOUND_ENABLE;
}

/*****************************************************************************/

/*
 * Inicializa el temporizador que se usará en un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 * @param timer   Temporizador (sólo TIMER0 o TIMER1)
 */
inline void gba_sound_ds_set_timer(u_char channel, u_char timer)
{
  gba_sound_regs.SOUNDCNT_H |= (timer & 0x01) << gba_sound_dss[channel].timer_offset;
}

/*****************************************************************************/

/*
 * Inicializa el volumen de un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 * @param volume  Volumen (SOUND_DS_OUTPUT_RATIO_50 o SOUND_DS_OUTPUT_RATIO_100)
 */
inline void gba_sound_ds_set_volume(u_char channel, u_char volume)
{
  gba_sound_regs.SOUNDCNT_H |= (volume & 0x01) << gba_sound_dss[channel].volume_offset;
}

/*****************************************************************************/

/*
 * Inicializa la salida de un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 * @param output  Tipo de salida  (SOUND_DS_OUTPUT_TO_RIGHT,
 *                SOUND_DS_OUTPUT_TO_LEFT o SOUND_DS_OUTPUT_TO_BOTH)
 */
inline void gba_sound_ds_set_output(u_char channel, u_char output)
{
  gba_sound_regs.SOUNDCNT_H |= (output & 0x03) << gba_sound_dss[channel].lr_offset;
}

/*****************************************************************************/

/*
 * Resetea la cola de un canal de sonido directo.
 * @param channel Número de canal (SOUND_DSA o SOUND_DSB)
 */
inline void gba_sound_ds_fifo_reset(u_char channel)
{
  gba_sound_regs.SOUNDCNT_H |= 1 << gba_sound_dss[channel].reset_offset;
}

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
void gba_sound_ds_play(u_char channel, const void* samples, u_short size, u_short rate)
{
  u_short clocks_per_sample;

  gba_dma_sound_init(DMA1, (void *)gba_sound_dss[channel].FIFO, samples);

  /* Reseteamos la cola FIFO */
  gba_sound_ds_fifo_reset(channel);

  /* Fijamos el temporizador que se usará para gestionar la frecuencia */
  gba_sound_ds_set_timer(channel, TIMER0);

  /* Calculamos el número de ciclos que deben pasar entre cada muestra */
  clocks_per_sample = gba_div(MCK, rate);

  /* Calculamos el valor inicial para el temporizador */
  gba_timer_init(TIMER0, TIMER_FREQ_1, TIMER_OVERFLOW - clocks_per_sample);

  /*
   * Programamos el temporizador que contará el número de muestras reproducidas
   * para que genere una interrupción cuando se reproduzca la últime muestra
   */
  gba_timer_init(TIMER1, TIMER_CASCADE | TIMER_INT, TIMER_OVERFLOW - size);
  
  /* Habilitamos la atención de la interrupción */
  gba_irq_enable(IRQ_TIMER1, gba_sound_ds_stop);
  
  /* Habilitamos el controlador de sonido */
  gba_sound_enable();

  /* Habilitamos el canal de DMA1 */
  gba_dma_enable(DMA1);

  /* Habilitamos los temporizadores */
  gba_timer_start(TIMER0);
  gba_timer_start(TIMER1);
}

/*****************************************************************************/

/*
 * Finaliza la reproducción de sonido
 */
inline void gba_sound_ds_stop()
{
  gba_timer_stop(TIMER0);
  gba_dma_disable(DMA1);
  gba_sound_disable();
}

/*****************************************************************************/

