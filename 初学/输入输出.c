#include <stdio.h>                                                                                                    +e <stdio.h>
#include <stdlib.h>

int main(void)
{
    char c_v = 0;
    int i_v = 0;
    float f_v = 0;

    printf("please input a char number:");
    scanf("%c",&c_v);
    printf("please input a int number:");
    scanf("%d",&i_v);
    printf("please input a float number:");
    scanf("%f",&f_v);

    printf("c_v = %c\n",c_v);
    printf("i_v = %d\n",i_v);
    printf("f_v = %f\n",f_v);

    return 0;
}
