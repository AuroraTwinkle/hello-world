#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   char c,d;
   scanf("%c",&c);

   if (c >= 'a'&& c <= 'z')
    d = c - 32;
   else if (c >= 'A'&& c <= 'Z')
    d = c + 32;

   printf("Result:%c to %c",c,d);

    return 0;
}
