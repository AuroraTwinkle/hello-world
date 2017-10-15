#include <stdio.h>                                                                                                    +e <stdio.h>
#include <stdlib.h>

int main(void)
{
    int salary = 0;
    float ratio = 0.0;

    printf("Please input your salary:");
    scanf("%d",&salary);

    if (salary > 50000)
        ratio = 0.5;
    else if (salary > 10000)
        ratio = 0.3;
    else if (salary > 7000)
        ratio = 0.2;
    else if (salary > 5000)
        ratio = 0.1;
    else
        ratio = 0;

    printf("The tax is %.3f\n",salary*ratio);

    return 0;
}
