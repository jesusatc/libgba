/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para gestionar el acceso a los cartuchos      */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef gamepack_h
#define gamepack_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz del controlador de memoria                                       */
/*****************************************************************************/

typedef struct
{
  short WAITCNT;       /* game pack memory control */
} gba_gamepack_regs_struct;

extern volatile gba_gamepack_regs_struct gba_gamepack_regs;


/*****************************************************************************/
/* WAITCNT: Game Pack Memory Control                                         */
/*****************************************************************************/

/*
 * Game Pack RAM Wait Control
 */
#define GAMEPACK_RAM_WAIT_4        ((short) 0)         /* 4 ciclos de espera */
#define GAMEPACK_RAM_WAIT_3        ((short) 1)         /* 3 ciclos de espera */
#define GAMEPACK_RAM_WAIT_2        ((short) 2)         /* 2 ciclos de espera */
#define GAMEPACK_RAM_WAIT_8        ((short) 3)         /* 8 ciclos de espera */

/*
 * Wait Control para el primer acceso en modo Wait State 0
 */
#define GAMEPACK_WS0_WAIT_1_4      ((short) (0 << 2))  /* 4 ciclos de espera */
#define GAMEPACK_WS0_WAIT_1_3      ((short) (1 << 2))  /* 3 ciclos de espera */
#define GAMEPACK_WS0_WAIT_1_2      ((short) (2 << 2))  /* 2 ciclos de espera */
#define GAMEPACK_WS0_WAIT_1_8      ((short) (3 << 2))  /* 8 ciclos de espera */

/*
 * Wait Control para el segundo acceso en modo Wait State 0
 */
#define GAMEPACK_WS0_WAIT_2_2      ((short) (0 << 4))  /* 2 ciclos de espera */
#define GAMEPACK_WS0_WAIT_2_1      ((short) (1 << 4))  /* 1 ciclo de espera */

/*
 * Wait Control para el primer acceso en modo Wait State 1
 */
#define GAMEPACK_WS1_WAIT_1_4      ((short) (0 << 5))  /* 4 ciclos de espera */
#define GAMEPACK_WS1_WAIT_1_3      ((short) (1 << 5))  /* 3 ciclos de espera */
#define GAMEPACK_WS1_WAIT_1_2      ((short) (2 << 5))  /* 2 ciclos de espera */
#define GAMEPACK_WS1_WAIT_1_8      ((short) (3 << 5))  /* 8 ciclos de espera */

/*
 * Wait Control para el segundo acceso en modo Wait State 1
 */
#define GAMEPACK_WS1_WAIT_2_4      ((short) (0 << 7))  /* 4 ciclos de espera */
#define GAMEPACK_WS1_WAIT_2_1      ((short) (1 << 7))  /* 1 ciclo de espera */

/*
 * Wait Control para el primer acceso en modo Wait State 2
 */
#define GAMEPACK_WS2_WAIT_1_4      ((short) (0 << 8))  /* 4 ciclos de espera */
#define GAMEPACK_WS2_WAIT_1_3      ((short) (1 << 8))  /* 3 ciclos de espera */
#define GAMEPACK_WS2_WAIT_1_2      ((short) (2 << 8))  /* 2 ciclos de espera */
#define GAMEPACK_WS2_WAIT_1_8      ((short) (3 << 8))  /* 8 ciclos de espera */

/*
 * Wait Control para el segundo acceso en modo Wait State 2
 */
#define GAMEPACK_WS2_WAIT_2_8      ((short) (0 << 10)) /* 8 ciclos de espera */
#define GAMEPACK_WS2_WAIT_2_1      ((short) (1 << 10)) /* 1 ciclo de espera */

/*
 * PHI Terminal Output Control
 */
#define GAMEPACK_PHI_DISABLE       ((short) (0 << 11)) /* Sin salida (defecto) */
#define GAMEPACK_PHI_4_19          ((short) (1 << 11)) /*  4.19 MHz */
#define GAMEPACK_PHI_8_38          ((short) (2 << 11)) /*  8.38 MHz */
#define GAMEPACK_PHI_16_78         ((short) (3 << 11)) /* 16.78 MHz */

/*
 * Habilitaciónd de precaptación
 */
#define GAMEPACK_PREFETCH_ENABLE   ((short) (1 << 14))

/*
 * Tipo de cartucho
 */
#define GAMEPACK_GBA               ((short) (0 << 15)) /* Gameboy Advance */
#define GAMEPACK_CGB               ((short) (1 << 15)) /* Gameboy Color */

/*****************************************************************************/

#endif /* gamepack_h */

