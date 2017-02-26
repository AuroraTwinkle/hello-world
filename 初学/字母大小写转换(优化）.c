#include <stdio.h>                                                                                                    +e <stdio.h>
#include <stdlib.h>

int main(void)
{
   char c,d;
   scanf("%c",&c);

   (c >= 'a' && c <= 'z') ? (d = c - 32) : (d = c + 32);

   printf("result:%c to %c",c,d);

    return 0;
}
