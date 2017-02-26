#include <stdio.h>                                                                                                    +e <stdio.h>
#include <stdlib.h>

int main(void)
{
    float a = 0;
    printf("Please input a number:");
    scanf("%f",&a);

    if (a>0)
        printf("%.2f is a positive number\n",a);
    else if (a<0)
        printf("%.2f is a negative number\n",a);
    else if (a==0)
        printf("%.2f is a zero\n",a);

    int b = 0;
    printf("Please input a int number:");
    scanf("%d",&b);

    if (0 == b % 2)
        printf("%d is even\n",b);
    else
        printf("%d is obb\n",b);


    return 0;
}
