#include <stdio.h>
#include <time.h>

int main()
{
    clock_t ck1, ck2;
    ck1 = clock();
    int i;
    for (i = 0; i < 1000000; i = i + 1)
    {
    }
    for (i = 0; i < 1000000; i = i + 1)
    {
    }
    for (i = 0; i < 1000000; i = i + 1)
    {
    }
    ck2 = clock();
    double difference = ((double)(ck1 - ck2));
    printf("Diferencia %f", difference);
    return (0);
}