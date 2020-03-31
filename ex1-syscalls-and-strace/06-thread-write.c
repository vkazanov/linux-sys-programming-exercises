#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* The program runs 2 threads (an initial and a secondary one), both printing
 * strings to stdout */

/* QUESTION: find a way to make strace differentiate syscalls on a per-thread basis */

/* QUESTION: what syscall is used on linux for creating threads? compare with
 * fork-related syscalls */

/* NOTE: you will need to use the -pthread flag to compile this program*/

void *thread(void *arg)
{
    (void) arg;

    printf("Secondary thread: working\n");
    sleep(1);
    printf("Secondary thread: done\n");

    return NULL;
}

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    printf("Initial thread: launching a thread\n");

    pthread_t thr;
    if (0 != pthread_create(&thr, NULL, thread, NULL)) {
        fprintf(stderr, "Initial thread: failed to create a thread");
        exit(EXIT_FAILURE);
    }

    printf("Initial thread: joining a thread\n");
    if (0 != pthread_join(thr, NULL)) {
        fprintf(stderr, "Initial thread: failed to join a thread");
        exit(EXIT_FAILURE);
    };

    printf("Initial thread: done");

    exit(EXIT_SUCCESS);
}
