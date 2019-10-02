#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   int m = 0;
   int n = 0;
   int i = 0;
   int sum = 0;

   printf("Please input m and n ,(m<=n):");
   scanf("%d %d",&m,&n);

   for( ;m>n; ){
    printf("Error:m must be no more than n.\n");
    printf("Please input new m and n:");
    scanf("%d %d",&m,&n);
   }

   for(i=m,sum=0; i<=n;++i){
    sum += i;
   }

   printf("Sum = %d",sum);

    return 0;
}
