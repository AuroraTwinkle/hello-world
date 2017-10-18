#include <stdio.h>                                                                                                    +e <stdio.h>
#include <stdlib.h>

int main(void)
{
    double pi = 3.1415926;
    printf("please input a double number:");
    scanf("%lf",&pi);
    int i = pi;
    printf("%d",i);
    return 0;
}
