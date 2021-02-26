#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

int main()
{
    if (fork() == 0)
    {
        //IsChild
        int i;
        for (i = 0; i < 1000000; i = i + 1)
        {
            printf("Numero %d", i);
        }
    }
    else
    {
        while (true)
        {
        }
    }
}