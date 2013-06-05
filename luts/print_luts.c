#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * Para manejar los ángulos
 */
#define MAX_ANG                360
#define RADIAN(n)              (n * M_PI / 180)


void print_lut(char* name, double (*func)(double))
{
  short n, i;
  
  printf("const fixed_p %s[%d] = {\n", name, MAX_ANG);

  n = i = 0;
  while (n < MAX_ANG)
  {
    printf ("0x%04x", (unsigned short)(func(RADIAN(n))*256));

    if (++n<MAX_ANG)
      printf(",");

    if (++i==8)
    {
      i=0;
      printf("\n");
    }
  }
  printf("};\n\n");
}

int main()
{
  print_lut("fp_sin", sin);
  print_lut("fp_cos", cos);
  return 0;
}

