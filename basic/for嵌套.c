#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i;
  int j;
  int k;
  int n;
  int sum = 0;

  printf("Please input a number n:");
  scanf("%d",&n);

  for(i=1;i<=n;++i){
    for(j=1,k=1;j<=i;++j){
        k *= j;
  }
  sum += k;
  }

  printf("Result:%d",sum);

    return 0;
}
