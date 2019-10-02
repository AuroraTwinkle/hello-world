#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m;
    int h = 0, temp = 0;
    int arr[50];
    scanf("%d", &m);
    while (m != 0)
    {
        arr[h] = m % 10;
        m /= 10;
        h++;
    }
    for (int i = 1; i < h; i++)
    {
        int j = 0;
        temp = arr[i];
        for (j = i - 1; arr[j] < temp; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
    for (int i = 0; i < h; i++)
    {
        printf("%d", arr[i]);
    }
}
