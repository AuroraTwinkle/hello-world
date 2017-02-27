#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int f1 = 1;
  int f2 = 1;
  int tem = 0;
  int n =0;

  printf("Please input n:");
  scanf("%d",&n);

  while(f2<n){
    tem = f2;
    f2 = f2 + f1;
    f1 = tem;
  }
  printf("The maximal fibonacci number is less than %d is %d.\n",n,f1);

    return 0;
}
