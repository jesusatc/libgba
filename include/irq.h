/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para el controlador de interrupciones         */
/* de la GBA                                                                 */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef irq_h
#define irq_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz del controlador de interrupciones de la consola                  */
/*****************************************************************************/

typedef struct
{
  short IE;            /* interrupt enable register */
  short IF;            /* interrupt request flags / irq acknowledge */
  short filler[2];     /* not used & waitcnt */
  short IME;           /* interrput master enable register */
} gba_irq_regs_struct;

extern volatile gba_irq_regs_struct gba_irq_regs;

/*
 * Tipo para definir los manejadores de interripciones.
 */
typedef void (*gba_irq_handler)(void);

/*
 * Tabla de punteros a manejadores de interrupciones
 */
extern volatile gba_irq_handler *gba_irq_handler_table;


/*****************************************************************************/
/* IE, IF: Máscaras para las interrupciones                                  */
/*****************************************************************************/

/*
 * Máscaras para cada una de las interrupciones
 */
#define IRQ_VBLANK                 ((short) (1 << 0))
#define IRQ_HBLANK                 ((short) (1 << 1))
#define IRQ_VCOUNT                 ((short) (1 << 2))
#define IRQ_TIMER0                 ((short) (1 << 3))
#define IRQ_TIMER1                 ((short) (1 << 4))
#define IRQ_TIMER2                 ((short) (1 << 5))
#define IRQ_TIMER3                 ((short) (1 << 6))
#define IRQ_SERIAL                 ((short) (1 << 7))
#define IRQ_DMA0                   ((short) (1 << 8))
#define IRQ_DMA1                   ((short) (1 << 9))
#define IRQ_DMA2                   ((short) (1 << 10))
#define IRQ_DMA3                   ((short) (1 << 11))
#define IRQ_KEYPAD                 ((short) (1 << 12))
#define IRQ_CART                   ((short) (1 << 13))


/*****************************************************************************/
/* IME: Habilitación de todas las interrupciones                             */
/*****************************************************************************/

#define IRQ_DISABLE                 ((short) 0)
#define IRQ_ENABLE                  ((short) 1)

/*****************************************************************************/

#endif /* irq_h */
