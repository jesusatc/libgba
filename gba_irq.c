/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para manejar interrupciones en la GBA     */
/*                                                                           */
/*****************************************************************************/

#include "gba_irq.h"

/*****************************************************************************/

#define IRQ_MAX    14

/*****************************************************************************/

/*
 * Manejador principal de las interrupciones.
 * Identifica el origen de la interrupción, llama al manejador adecuado y
 * reconoce su atención.
 * Esta versión es muy lenta porque se ejecuta desde la ROM. En startup.s hay
 * otra escrita en ensamblador mucho mejor. También está la versión cutre sin
 * tabla de interrupciones ...
 */
void gba_irq_master_handler(void)
{
  int i = 0;

  gba_irq_disable_all();        /* Deshabilitamos las interrupciones */

  for (i = 0 ; i < IRQ_MAX ; i++)
  {
    if(gba_irq_regs.IF & (1 << i)) /* Comprobamos qué interrupción se ha generado */
    {
      gba_irq_handler_table[i](); /* Llamamos a su manejador */
      gba_irq_regs.IF |= (1 << i); /* Reconocemos su atención */
    }
  }

  gba_irq_enable_all();         /* Habilitamos las interrupciones */
}

/*****************************************************************************/

/*
 * Habilita la gestión de interrupciones
 */
inline void gba_irq_enable_all()
{
  gba_irq_regs.IME = IRQ_ENABLE;
}

/*****************************************************************************/

/*
 * Deshabilita la gestión de interrupciones
 */
inline void gba_irq_disable_all()
{
  gba_irq_regs.IME = IRQ_DISABLE;
}

/*****************************************************************************/

/*
 * Función para habilitar la atención de interrupciones concretas
 * @param masc    Máscara para seleccionar interrupciones 
 * @param handler Función para gestionar las interrupciones
 */
void gba_irq_enable(short masc, gba_irq_handler handler)
{
  int i;

  /* Copiamos el manejador en la tabla de manejadores */
  for (i = 0 ; i < IRQ_MAX ; i++)
  {
    if (masc & (1 << i))
      gba_irq_handler_table[i] = handler;
  }

  gba_irq_disable_all();
  gba_irq_regs.IE |= masc;
  gba_irq_enable_all();
}

/*****************************************************************************/

/*
 * Deshabilita interrupciones concretas
 * @param masc Máscara para seleccionar interrupciones 
 */
inline void gba_irq_disable(short masc)
{
  gba_irq_disable_all();
  gba_irq_regs.IE &= ~masc;
  gba_irq_enable_all();
}

/*****************************************************************************/

