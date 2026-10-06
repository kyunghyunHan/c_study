/*
큐브돌리기

*/
#include <stdio.h>
#include <stdlib.h>
int arr[5];
int main(void)
{
  int cnt = 1;
  int index = 4;
  int n;
  int q = 16;
  freopen("data.txt", "r", stdin);
  scanf("%d %d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4], &n);

  while (1)
  {
    if (n <= 0)
    {
      printf("%d", cnt);
      return 0;
    }
    if (n >= q && arr[index] > 0)
    {
      arr[index]--;
      n %= q;
      cnt += n/q;
    }
    else
    {
      q >>= 1;
      index--;
    }
  }
  printf("%d", cnt);
  return 0;
}