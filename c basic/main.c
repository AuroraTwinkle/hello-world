#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a,b,c;
    int d=109;

    scanf("%d\n",&a);
    scanf("%x\n",&b);
    scanf("%o\n",&c);

    printf("a=%d\n",a);
    printf("b=%d\n",b);
    printf("c=%d\n",c);

    printf("d(109)=%o\n",d);
    printf("d(109)=%x\n",d);
    printf("d(109)=%d\n",d);
    printf("d(109)=%X\n",d);

    return 0;
}
