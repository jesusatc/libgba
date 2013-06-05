/*****************************************************************************/
/*                                                                           */
/* Sistemas operativos empotrados                                            */
/*                                                                           */
/* Biblioteca de funciones básicas para generar números aleatorios           */
/*                                                                           */
/*****************************************************************************/

/*
 * Como la GBA no implementa ni la división ni el resto en hardware, y las
 * implementaciónes software de estas operaciones son lentas, los generadores
 * de números aleatorios habituales, que se basan en la utilización de estas
 * dos operaciones, son muy lentos para genetar números aleatorios en tiempo
 * real.
 *
 * Sin embargo, el algoritmo de generación de números aleatorios de "Mersenne
 * Twister", desarrollado por Makoto Matsumoto y Takuji Nishimura en 1997, no
 * necesita usar estas dos operaciones. Sólo se usan 4 XORs, 2 ANDs y 4
 * desplazamientos de registro, lo que lo hace muy adecuado para su uso en la
 * GBA. 
 *
 * El algoritmo original, tal y como se describe el trabajo Matsumoto y
 * Nishimura, necesita un búfer de 2496 bytes para almacenar el estado actual
 * del generador y tiene un periodo de 2^19937. Sin embargo, se puede reducir
 * el tamaño del búfer, reduciendo el periodo del algoritmo, para ahorrar algún
 * K de memoria. Concretamente, este código implementa la versión MT19937, que
 * genera números aleatorios equidistribuidos en el intervalo 0..(2^32 - 1).
 * 
 * Esta versión está basada en un código de Rafael Baptista, basado en otro de
 * Shawn Cokus que partía de la versión original del algoritmo. 
 */

/*****************************************************************************/

#include "gba_rand.h"
#include "gba_bios.h"

/*****************************************************************************/

/*
 * Variables estáticas del generador
 */
u_int  gba_rand_state[RAND_N+1]; /* Buffer de estado (mas 1 extra para no hacer chequeo de límites) */
u_int* gba_rand_next;            /* El siguiente valor aleatorio se calcula a partir de aquí */
int    gba_rand_left=-1;         /* Elementos que quedan en el búfer antes de hacer una recarga */
/*****************************************************************************/

/*
 * Fija la semilla del generador.
 * @param seed Semilla
 */
void gba_srand(u_int seed)
{
  u_int x = (seed | 0x1) & 0xFFFFFFFF;
  u_int* s = gba_rand_state;
  u_int j = RAND_N;
  gba_rand_left = 0;
  *s++ = x;
   
  while (--j)
  {
    x *= 69069;
    *s = ( x & 0xFFFFFFFF );
    s++;
  }
}

/*****************************************************************************/

/*
 * Recarga del búfer
 */
u_int gba_rand_reload_buffer()
{
  u_int* p0 = gba_rand_state;
  u_int* p2 = gba_rand_state + 2;
  u_int* pM = gba_rand_state + RAND_M;
  u_int s0;
  u_int s1;
  int j;
   
  /* Si no se ha fijado una semilla, se fija ahora */
  if (gba_rand_left < -1)
    gba_srand(4357U);
   
  gba_rand_left = RAND_N-1;
  gba_rand_next = &(gba_rand_state[1]);
   
  for(s0 = gba_rand_state[0], s1 = gba_rand_state[1], j = (RAND_N-RAND_M+1) ; --j ; s0 = s1, s1 = *p2++)
    *p0++ = ( *pM++ ^ (mixBits(s0, s1) >> 1) ^ (LSBit(s1) ? RAND_K : 0));
   
  for(pM = gba_rand_state, j = RAND_M ; --j ; s0 = s1, s1 = *p2++)
    *p0++ = ( *pM++ ^ ( mixBits(s0, s1) >> 1 ) ^ ( LSBit(s1) ? RAND_K : 0 ));
   
  s1 = gba_rand_state[0];
  *p0 = ( *pM ^ ( mixBits( s0, s1 ) >> 1 ) ^ ( LSBit( s1 ) ? RAND_K : 0 ));
  s1 ^= ( s1 >> 11 );
  s1 ^= ( s1 <<  7 ) & 0x9D2C5680U;
  s1 ^= ( s1 << 15 ) & 0xEFC60000U;
  
  return ( s1 ^ ( s1 >> 18 ));
}

/*****************************************************************************/

/*
 * Devuelve el siguiente número aleatorio
 */
u_int gba_rand()
{
  u_int y;
   
  gba_rand_left--;
  if ( gba_rand_left < 0 ) 
    return gba_rand_reload_buffer();
   
  y  = *gba_rand_next;
  gba_rand_next++;
  y ^= ( y >> 11 );
  y ^= ( y <<  7 ) & 0x9D2C5680;
  y ^= ( y << 15 ) & 0xEFC60000;
  y ^= ( y >> 18 );
  
  return y;
}

/*****************************************************************************/

/*
 * Devuelve un número aleatorio en el intervalo [0, max_val).
 * @param max_val Máximo valor para el número aleatorio
 */
u_int gba_rand_mod(u_int max)
{
  // If max is 0, do not hang the console
  if (max==0)
    return max;

  signed int n = gba_rand();

  if (n<=0 || n>= max)
    n = gba_mod(n, max);

  return (n<0?-n:n);
}

/*****************************************************************************/

