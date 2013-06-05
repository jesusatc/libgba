/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para manejar los temporizadores en la GBA */
/*                                                                           */
/*****************************************************************************/

#include "gba_timer.h"

/*****************************************************************************/

/*
 * Variables estáticas de la biblioteca
 */

timer_struct gba_timers[4]=
{
  /* Timer 0 */
  {
    (gba_word16) &(gba_timer_regs.TM0CNT_L),  /* timer counter/reload */
    (gba_word16) &(gba_timer_regs.TM0CNT_H)   /* timer control */
  },

  /* Timer 1 */
  {
    (gba_word16) &(gba_timer_regs.TM1CNT_L),  /* timer counter/reload */
    (gba_word16) &(gba_timer_regs.TM1CNT_H)   /* timer control */
  },

  /* Timer 2 */
  {
    (gba_word16) &(gba_timer_regs.TM2CNT_L),  /* timer counter/reload */
    (gba_word16) &(gba_timer_regs.TM2CNT_H)   /* timer control */
  },

  /* Timer 3 */
  {
    (gba_word16) &(gba_timer_regs.TM3CNT_L),  /* timer counter/reload */
    (gba_word16) &(gba_timer_regs.TM3CNT_H)   /* timer control */
  }
};

/*****************************************************************************/

/*
 * Inicializa un temporizador.
 * @param timer Número de temporizador
 * @param conf  Flags de configuración
 * @param val   Valor inicial
 */
inline void gba_timer_init(u_char timer, u_short conf, u_short val)
{
  *(gba_timers[timer].TMCNT_L) = val;
  *(gba_timers[timer].TMCNT_H) = conf;
}

/*****************************************************************************/

/*
 * Indica al temporizador que empiece a contar.
 * @param timer Número de temporizador
 */
inline void gba_timer_start(u_char timer)
{
  *(gba_timers[timer].TMCNT_H) |= TIMER_ENABLE;
}

/*****************************************************************************/

/*
 * Indica al temporizador que deje de contar.
 * @param timer Número de temporizador
 */
inline void gba_timer_stop(u_char timer)
{
  *(gba_timers[timer].TMCNT_H) &= ~TIMER_ENABLE;
}

/*****************************************************************************/

/*
 * Función que devuelve el valor de cuenta de un temporizador.
 * @param timer Número de temporizador
 */
inline u_short gba_timer_get_counter(u_char timer)
{
  return *(gba_timers[timer].TMCNT_L);
}

/*****************************************************************************/

/*
 * Carga un nuevo valor para un temporizador. El valor se copiará al
 * temporizador cuando se reinicie, bien manualmente o bien porque haya llegado
 * a una condición de overflow.
 * @param timer Número de temporizador
 * @param val   Valor a cargar
 */
inline void gba_timer_reload(u_char timer, u_short val)
{
  *(gba_timers[timer].TMCNT_L) = val;
}

/*****************************************************************************/

