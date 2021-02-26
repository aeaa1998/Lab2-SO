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
#define MEMORY_SIZE 38
#define NAME "NAME1"
struct shmbuf
{
    // sem_t sem1;            /* POSIX unnamed semaphore */
    // sem_t sem2;            /* POSIX unnamed semaphore */
    size_t cnt;
    size_t cnt2;
    char buf[MEMORY_SIZE];
    char buf2[MEMORY_SIZE]; /* All shared things */
};
char *x;
struct shmbuf *shmp;

void cb(int sig)
{
    printf("%s Tiene %s\n", x, &shmp->buf2);
    //write(STDOUT_FILENO, &shmp->buf2, size);
}

int main(int argc, char *argv[])
{
    x = argv[2];
    char *n_p = argv[1];
    int finished = 0;
    int n = atoi(n_p);
    int created = 0;
    int file_descriptor;

    file_descriptor = shm_open(NAME, O_RDWR, 0);
    if (file_descriptor < 0)
    {
        //Must open the shared memory
        file_descriptor = shm_open(NAME, O_RDWR | O_CREAT | O_EXCL, S_IWUSR | S_IRUSR);
        shmp = mmap(NULL, sizeof(*shmp),
                    PROT_READ | PROT_WRITE | PROT_EXEC,
                    MAP_SHARED, file_descriptor, 0);
        if (shmp == MAP_FAILED)
            printf("fail");
        printf("\n%s Creo instancia de memoria compartida %d\n", x, file_descriptor);
        char file_descriptor_char[1024];
        sprintf(file_descriptor_char, "%d", file_descriptor);
        ftruncate(file_descriptor, sizeof file_descriptor_char);

        char *string = file_descriptor_char;
        size_t len = strlen(string);
        shmp->cnt = len;
        memcpy(&shmp->buf, string, len);
        created = 1;
    }
    else
    {
        //He has the opens the memory and watches the file descriptor
        shmp = mmap(NULL, sizeof(*shmp),
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, file_descriptor, 0);
        ftruncate(file_descriptor, sizeof(struct shmbuf));
        int size = (int)shmp->cnt;
        printf("\n%s Recibio instancia de memoria compartida %s\n", x, &shmp->buf);
    }
    int child_id = fork();

    //Parent
    if (child_id != 0)
    {
        sleep(1);
        int n_it = MEMORY_SIZE;
        int j;
        char messageToChild[MEMORY_SIZE] = "";
        strcat(messageToChild, shmp->buf2);
        for (j = 0; j < n_it; j = j + 1)
        {
            if (j % n == 0)
            {

                //memcpy(&shmp->buf, x, strlen(x));
                strcat(messageToChild, x);
            }
        }
        char *messageToChildp = messageToChild;
        memcpy(&shmp->buf2, messageToChildp, strlen(messageToChildp));
        shmp->cnt = strlen(messageToChildp);

        kill(child_id, SIGUSR1);
        wait(NULL);
    }
    else
    {
        //while(finished == 0){
        //	printf("listening");
        //}
        signal(SIGUSR1, cb);
        sleep(2);
        exit(0);
    }
    //Solo el que lo creo puede unlinkear
    if (created != 1)
    {
        shm_unlink(NAME);
    }
    exit(0);
}