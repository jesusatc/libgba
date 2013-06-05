/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Constantes útiles para el manejo del procesador de la GBA                 */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef arm_h
#define arm_h

/*****************************************************************************/
/* Modos de ejecución y bits de estado                                       */
/*****************************************************************************/

#define     ARM_MODE_USER       0x10
#define     ARM_MODE_FIQ        0x11
#define     ARM_MODE_IRQ        0x12
#define     ARM_MODE_SVC        0x13
#define     ARM_MODE_ABORT      0x17
#define     ARM_MODE_UNDEF      0x1b
#define     ARM_MODE_SYS        0x1f

#define     ARM_I_BIT           0x80
#define     ARM_F_BIT           0x40
#define     ARM_T_BIT           0x20

/*****************************************************************************/

#endif /* arm_h */
