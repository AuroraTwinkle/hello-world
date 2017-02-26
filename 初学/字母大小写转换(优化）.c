#include <stdio.h>                                                                                                    +e <stdio.h>
#include <stdlib.h>

int main(void)
{
   char c,d;
   scanf("%c",&c);
   if (c >= 'a'&& c <= 'z')
    d = c - 32;
   else if (c >= 'A'&& c <= 'Z')
    d = c + 32;
   printf("%c",d);

    return 0;
}
