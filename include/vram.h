/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Tipos de datos y constantes para manejar la memoria VRAM de la GBA        */
/*                                                                           */
/*****************************************************************************/

/*
 * Sólo incluimos este archivo una vez
 */
#ifndef vram_h
#define vram_h

#include    "std_c.h"

/*****************************************************************************/
/* Dimensiones de la pantalla                                                */
/*****************************************************************************/

#define BG_MODE_WIDTH3   240
#define BG_MODE_HEIGHT3  160
#define BG_MODE_WIDTH5   160
#define BG_MODE_HEIGHT5  128


/*****************************************************************************/
/* Formato de las tripletas RBG en la VRAM                                   */
/*****************************************************************************/

#define RGB(r,g,b)             ((unsigned short)(((r) & 0x001f) + \
                                                (((g) & 0x001f) << 5) + \
                                                (((b) & 0x001f) << 10)))


/*****************************************************************************/
/* Interfaz de la memoria VRAM                                               */
/*****************************************************************************/

/*
 * En los modos de texto, cada carácter está formado por matrices de 8x8
 * pixels, y cada pixel ocupa 4 bits (para paletas de 16 colores) o un byte
 * (para paletas de 256 colores).
 */
typedef char gba_video_char16[32];
typedef char gba_video_char256[64];

/*
 * En los modos de texto, la VRAM está dividida en 4 bloques de caracteres, de
 * 16 KB cada uno, en los que se almacenarán los caracteres para definir los
 * fondos.
 */
typedef gba_video_char256 gba_video_char_block[256];

/*
 * Para definir un fondo de pantalla se usa un mapa que indica qué carácter del
 * bloque de caracteres se usará para cada uno de los caracteres de la pantalla
 *
 *  * En los fondos de texto cada entrada del mapa es de 2 bytes:
 *     |Paleta 16 (4 bits) | FlipV (1 bit) | FlipH (1 bit) | Indice (10 bits) |
 *
 *  * En los fondos de rotación cada entrada ocupa un byte:
 *     |Indice del carácter (8 bits) |
 *
 * En modo texto, los mapas de 256x512, 512x256 y 512x512 no caben en un
 * screen-block, así que se parten en dos (256x512 y 512x256) o cuatro bloques
 * (512x512)
 */
typedef short gba_video_screen_block[1024];

/*
 * Estructura para acceder a las diferentes zonas de la VRAM
 */
typedef union
{
  struct // Modos de texto
  {
    union
    {
      gba_video_char_block char_block[4];
      gba_video_screen_block screen_block[32];
    } __attribute__ ((packed));
    
    /*
     * La memoria para almacenar los sprites está organizada en caracteres de
     * 16 colores. Si se usan sprites de 256 colores, cada carácter del sprite
     * ocupará dos caracteres de la memoria.
     */
    gba_video_char16 obj_data[1024];
  };
  
  short video_buffer[BG_MODE_WIDTH3*BG_MODE_HEIGHT3]; // Modo 3
    
  struct // Modos 4 y 5
  {
    short front_buffer[BG_MODE_WIDTH5*BG_MODE_HEIGHT5];
    short back_buffer[BG_MODE_WIDTH5*BG_MODE_HEIGHT5];
  };
}gba_vram_struct;

extern volatile gba_vram_struct gba_vram;

/*****************************************************************************/

#endif /* vram_h */
