#include <stdio.h>
#include <time.h>

int main()
{
    clock_t ck1, ck2;
    ck1 = clock();
    time_t start, end;
    int i;
    time(&start);
    for (i = 0; i < 1000000; i = i + 1)
    {
        printf("%d\n", i);
    }
    time(&end);
    printf("Diferencia 1: %f\n", difftime(end, start));
    time(&start);
    for (i = 0; i < 1000000; i = i + 1)
    {
        printf("%d\n", i);
    }
    time(&end);
    printf("Diferencia 2: %f\n", difftime(end, start));
    time(&start);
    for (i = 0; i < 1000000; i = i + 1)
    {
        printf("%d\n", i);
    }
    time(&end);
    printf("Diferencia 3: %f\n", difftime(end, start));

    ck2 = clock();
    double difference = ((double)(ck2 - ck1));
    printf("Diferencia %f\n", difference);
    return (0);
}