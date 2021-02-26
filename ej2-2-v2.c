#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    clock_t ck1, ck2;
    pid_t p1, p2;
    ck1 = clock();
    p1 = fork();
    int i;
    // Is children checl
    if (p1 == 0)
    {
        pid_t pchild = fork();
        //Is grandchild check
        if (pchild == 0)
        {
            //Into grandchild
            pid_t pGrandChild = fork();
            //Grandchild makes 10000 iterations
            if (pGrandChild == 0)
            {
                //Grand grand child
                for (i = 0; i < 1000000; i = i + 1)
                {
                    printf("%d", i);
                }
                return (0);
            }
            else
            {
                //Is grandchild
                for (i = 0; i < 1000000; i = i + 1)
                {
                    printf("%d", i);
                }
                //Grandchild waits for his child
                wait(NULL);
                return (0);
            }
        }
        else
        {
            //Is child
            for (i = 0; i < 1000000; i = i + 1)
            {
                printf("%d", i);
            }
            //child waits for his child
            wait(NULL);
            return (0);
        }
    }
    else
    {
        //Is parent
        for (i = 0; i < 1000000; i = i + 1)
        {
            printf("%d", i);
        }
        //parent waits for his child
        wait(NULL);
        ck2 = clock();
    }
    double difference = ((double)(ck2 - ck1));
    printf("Diferencia %f\n", difference / 1000.0);
    return (0);
}