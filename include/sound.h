/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para el controlador de sonido de la GBA       */
/*                                                                           */
/*****************************************************************************/

/*
 * SÃ³lo incluimos este archivo una vez
 */
#ifndef sound_h
#define sound_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz para el controlador de sonido de la consola                      */
/*****************************************************************************/

typedef struct
{
  short SOUND1CNT_L;   /* FM synthesis channel 1 sweep */
  short SOUND1CNT_H;   /* FM synthesis channel 1 duty/length/envelope */
  short SOUND1CNT_X;   /* FM synthesis channel 1 frequency/control */
  short filler1;       /* not used */
  short SOUND2CNT_L;   /* FM synthesis channel 2 duty/length/envelope */
  short filler2;       /* not used */
  short SOUND2CNT_H;   /* FM synthesis channel 2 frequency/control */
  short filler3;       /* not used */
  short SOUND3CNT_L;   /* FM synthesis channel 3 stop/wave ram select */
  short SOUND3CNT_H;   /* FM synthesis channel 3 length/volume */
  short SOUND3CNT_X;   /* FM synthesis channel 3 frequency/control */
  short filler4;       /* not used */
  short SOUND4CNT_L;   /* FM synthesis channel 4 duty/length/envelope */
  short filler5;       /* not used */
  short SOUND4CNT_H;   /* FM synthesis channel 4 frequency/control */
  short filler6;       /* not used */
  short SOUNDCNT_L;    /* control stereo/volume/enable */
  short SOUNDCNT_H;    /* control mixing/dma control */
  short SOUNDCNT_X;    /* control sound on/off */
  short filler7;       /* not used */
  short SOUNDBIAS;     /* sound pwm control */ 
  short filler8[3];    /* not used */
  short WAVE_RAM[8];   /* FM synthesis channel 3 wave pattern ram */ 
  int   FIFO_A;        /* direct sound channel a fifo, data 0-3 */
  int   FIFO_B;        /* direct sound channel b fifo, data 0-3 */
} gba_sound_regs_struct;

extern volatile gba_sound_regs_struct gba_sound_regs;


/*****************************************************************************/
/* SOUNDCNT_H: Control Mixing/DMA Control                                    */
/*****************************************************************************/

/*
 * Porcentaje de volumen para los canales 1-4
 */
#define SOUND_FM_OUTPUT_RATIO_25   ((short) 0)         /*  25% */
#define SOUND_FM_OUTPUT_RATIO_50   ((short) 1)         /*  50% */
#define SOUND_FM_OUTPUT_RATIO_100  ((short) 2)         /* 100% */

/*
 * Porcentaje de volumen para los canales A-B
 */
#define SOUND_DSA_OUTPUT_RATIO_50  ((short) (0 << 2))  /*  50% para el canal A */
#define SOUND_DSA_OUTPUT_RATIO_100 ((short) (1 << 2))  /* 100% para el canal A */
#define SOUND_DSB_OUTPUT_RATIO_50  ((short) (0 << 3))  /*  50% para el canal B */
#define SOUND_DSB_OUTPUT_RATIO_100 ((short) (1 << 3))  /* 100% para el canal B */

/*
 * Selección de las líneas de salida para los canales A-B
 */
#define SOUND_DSA_OUTPUT_TO_RIGHT  ((short) (1 << 8))
#define SOUND_DSA_OUTPUT_TO_LEFT   ((short) (1 << 9))
#define SOUND_DSA_OUTPUT_TO_BOTH   (SOUND_DSA_OUTPUT_TO_RIGHT|SOUND_DSA_OUTPUT_TO_LEFT)
#define SOUND_DSB_OUTPUT_TO_RIGHT  ((short) (1 << 12))
#define SOUND_DSB_OUTPUT_TO_LEFT   ((short) (1 << 13))
#define SOUND_DSB_OUTPUT_TO_BOTH   (SOUND_DSB_OUTPUT_TO_RIGHT|SOUND_DSB_OUTPUT_TO_LEFT)

/*
 * Selección de los temporizadores para los canales A-B
 */
#define SOUND_DSA_TIMER0           ((short) (0 << 10))
#define SOUND_DSA_TIMER1           ((short) (1 << 10))
#define SOUND_DSB_TIMER0           ((short) (0 << 14))
#define SOUND_DSB_TIMER1           ((short) (1 << 14))

/*
 * Reset de las colas FIFO de los canales A-B
 */
#define SOUND_DSA_FIFO_RESET       ((short) (1 << 11))
#define SOUND_DSB_FIFO_RESET       ((short) (1 << 15))
 
/*****************************************************************************/
/* SOUNDCNT_X: Control Sound on/off                                          */
/*****************************************************************************/

/*
 * Flags para comprobar el estado de los canales de sonido 1-4
 */
#define SOUND_FM_1                 ((short) (1 << 0))
#define SOUND_FM_2                 ((short) (1 << 1))
#define SOUND_FM_3                 ((short) (1 << 2))
#define SOUND_FM_4                 ((short) (1 << 3))
 
/*
 * Habilitación/deshabilitación del controlador de sonido
 */
#define SOUND_ENABLE               ((short) (1 << 7))

/*****************************************************************************/

#endif /* sound_h */
