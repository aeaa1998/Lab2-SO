#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int i = 0;
    for (i; i < 4; i = i + 1)
    {
        fork();
    }
    printf("Forked\n");
    return (0);
}
