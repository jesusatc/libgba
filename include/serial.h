/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para manejar el puerto serie de la GBA        */
/*                                                                           */
/*****************************************************************************/

/*
 * SÃ³lo incluimos este archivo una vez
 */
#ifndef serial_h
#define serial_h

#include    "std_c.h"

/*****************************************************************************/
/* Interfaz para el puerto serie de la consola                               */
/* Realmente los registros para controlar el puerto serie están separados    */
/* por los registros de gestión del teclado.                                 */
/* En este caso, para evitar el manejo de dos estructuras independientes,    */
/* una para cada parte de los registros, se ha optado por una única          */
/* estructura en la que se han marcado las posiciones en las que se          */
/* encuentran los registros del teclado como no usados                       */
/*****************************************************************************/

typedef struct
{
  union  /* estos registros comparten la misma posición */
  {
    int SIODATA32;     /* SIO data (normal-32bit mode) */
    struct
    {
      short SIOMULTI0; /* SIO data 0 (parent)    (multi-player mode) */
      short SIOMULTI1; /* SIO data 1 (1st child) (multi-player mode) */
    } __attribute__ ((packed));
  } __attribute__ ((packed));

  short SIOMULTI2;     /* SIO data 2 (2nd child) (multi-player mode) */
  short SIOMULTI3;     /* SIO data 3 (3rd child) (multi-player mode) */
  short SIOCNT;        /* SIO control register */

  union /* estos dos registros comparten la misma posición */
  {
    short SIOMLT_SEND; /* SIO data (local of multi-player) */
    short SIODATA8;    /* SIO data (normal-8bit and uart mode) */
  } __attribute__ ((packed));  /* para evitar que fije el tamaño de la union a
                                  un múltiplo de 4 bytes (por defecto) */
  short filler1[4];
  short RCNT;          /* SIO mode select/general purpose data */
  short IR;            /* infrared register (prototypes only) */
  short filler2[4];
  short JOYCNT;        /* SIO JOY bus control */
  short filler3[7];
  int   JOY_RECV;      /* SIO JOY bus receive data */
  int   JOY_TRANS;     /* SIO JOY bus transmit data */
  short JOYSTAT;       /* SIO JOY bus receive status */
} gba_serial_regs_struct;

extern volatile gba_serial_regs_struct gba_serial_regs;

/*****************************************************************************/

#endif /* serial_h */

