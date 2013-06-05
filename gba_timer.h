/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para manejar los temporizadores en la GBA */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gba_timer_h
#define gba_timer_h

#include "gba.h"

/*****************************************************************************/

/*
 * Identificadores de los temporizadores
 */
#define TIMER0             0
#define TIMER1             1
#define TIMER2             2
#define TIMER3             3

/*
 * Valor de overflow para los temporizadores
 */
#define TIMER_OVERFLOW     (1 << 16)    

/*****************************************************************************/

/*
 * Estructura de datos para manejar los temporizadores
 */
typedef struct
{
  gba_word16 TMCNT_L;      /* timer counter/reload */
  gba_word16 TMCNT_H;      /* timer control */
} timer_struct;

/*****************************************************************************/

/*
 * Inicializa un temporizador.
 * @param timer Número de temporizador
 * @param conf  Flags de configuración
 * @param val   Valor inicial
 */
inline void gba_timer_init(u_char timer, u_short conf, u_short val);

/*****************************************************************************/

/*
 * Indica al temporizador que empiece a contar.
 * @param timer Número de temporizador
 */
inline void gba_timer_start(u_char timer);

/*****************************************************************************/

/*
 * Indica al temporizador que deje de contar.
 * @param timer Número de temporizador
 */
inline void gba_timer_stop(u_char timer);

/*****************************************************************************/

/*
 * Función que devuelve el valor de cuenta de un temporizador.
 * @param timer Número de temporizador
 */
inline u_short gba_timer_get_counter(u_char timer);

/*****************************************************************************/

/*
 * Carga un nuevo valor para un temporizador. El valor se copiará al
 * temporizador cuando se reinicie, bien manualmente o bien porque haya llegado
 * a una condición de overflow.
 * @param timer Número de temporizador
 * @param val   Valor a cargar
 */
inline void gba_timer_reload(u_char timer, u_short val);

/*****************************************************************************/

#endif /* gba_timer_h */
