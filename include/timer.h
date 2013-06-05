/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para los temporizadores de la GBA             */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef timer_h
#define timer_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz para los temporizadores de la consola                            */
/*****************************************************************************/

typedef struct
{
  short TM0CNT_L;      /* timer 0 counter/reload */
  short TM0CNT_H;      /* timer 0 control */
  short TM1CNT_L;      /* timer 1 counter/reload */
  short TM1CNT_H;      /* timer 1 control */
  short TM2CNT_L;      /* timer 2 counter/reload */
  short TM2CNT_H;      /* timer 2 control */
  short TM3CNT_L;      /* timer 3 counter/reload */
  short TM3CNT_H;      /* timer 3 control */
} gba_timer_regs_struct;

extern volatile gba_timer_regs_struct gba_timer_regs;


/*****************************************************************************/
/* TMxCNT_H: Control de los temporizadores                                   */
/*****************************************************************************/

/*
 * Pre-escalado del la frecuencia del temporizador
 */
#define TIMER_FREQ_1               ((short) 0)         /* Cada ciclo del reloj del sistema */
#define TIMER_FREQ_64              ((short) 1)         /* Cada 64 ciclos */
#define TIMER_FREQ_256             ((short) 2)         /* Cada 256 ciclos */
#define TIMER_FREQ_1024            ((short) 3)         /* Cada 1024 ciclos */

/*
 * Para encadenar los temporizadores. En este caso se ignora el factor de pre-escalado.
 */
#define TIMER_CASCADE              ((short) (1 << 2))
  
/*
 * Generación de una interrupción cuando el temporizador sobrepase el valor limite
 */
#define TIMER_INT                  ((short) (1 << 6))

/*
 * Habilitación del temporizador
 */
#define TIMER_ENABLE               ((short) (1 << 7))

/*****************************************************************************/

#endif /* timer_h */

