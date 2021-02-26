#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (fork() == 0)
    {
        execlp("./ipc", "ipc", "30", "A", (char *)NULL);
    }
    else
    {
        execlp("./ipc", "ipc", "30", "b", (char *)NULL);
    }
    exit(0);
}