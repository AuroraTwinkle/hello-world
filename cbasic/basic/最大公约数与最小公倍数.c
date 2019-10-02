#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int m = 0;
  int r = 0;
  int n = 0;
  int tmp = 0;
  int product =0;

  printf("Please input m and n(m is more than n):");
  scanf("%d %d",&m,&n);
  if (m<n){
    printf("Error:m is must more than n\n");
    printf("Please input m and n again:");
    scanf("%d %d",&m,&n);

  }

  product = m * n;

  if (m < n){
    tmp = n;
    n = m;
    m = tmp;
  }

  r = m % n;

  while (r != 0){
    m = n;
    n = r;
    r = m % n;
  }

  printf("The maximal common divisor: %d\n",n);
  printf("The minimal common multiple: %d\n",product / n);

    return 0;
}
