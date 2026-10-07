/*

*/
int com(const void *a, const void *b)
{
  int ia = *(const int *)a;
  int ib = *(const int *)b;

  return (ia > ib) - (ia < ib);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      char c;
      scanf(" %c", &c);
      printf("%c ", (char)c + 32);
    }
    printf("\n");
  }
  return 0;
}