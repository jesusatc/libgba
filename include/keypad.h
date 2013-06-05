/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para gestionar los botones de la GBA          */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef keypad_h
#define keypad_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz del controlador los botones de la GBA                            */
/*****************************************************************************/

typedef struct
{
  short KEYINPUT;      /* estado de los botones */
  short KEYCNT;        /* generación de interrupciones */
} gba_keypad_regs_struct;

extern volatile gba_keypad_regs_struct gba_keypad_regs;


/*****************************************************************************/
/* KEYINPUT: Flags para comprobar el estado de los botones                   */
/*****************************************************************************/

#define KEYPAD_A                   ((short) (1 << 0))  /* 0=pulsado, 1=liberado */
#define KEYPAD_B                   ((short) (1 << 1))
#define KEYPAD_SELECT              ((short) (1 << 2))
#define KEYPAD_START               ((short) (1 << 3))
#define KEYPAD_RIGHT               ((short) (1 << 4))
#define KEYPAD_LEFT                ((short) (1 << 5))
#define KEYPAD_UP                  ((short) (1 << 6))
#define KEYPAD_DOWN                ((short) (1 << 7))
#define KEYPAD_R                   ((short) (1 << 8))
#define KEYPAD_L                   ((short) (1 << 9))


/*****************************************************************************/
/* KEYCNT: Generación de interrupciones                                      */
/*****************************************************************************/

/*
 * Generación de una interrupción
 */
#define KEYPAD_INT                 ((short) (1 << 14))

/*
 * Generación de una interrupción cuando se pulse varios botones
 */
#define KEYPAD_OR                  ((short) (0 << 15))
#define KEYPAD_AND                 ((short) (1 << 15))

/*****************************************************************************/

#endif /* keypad_h */
