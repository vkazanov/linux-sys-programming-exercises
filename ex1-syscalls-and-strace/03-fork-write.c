#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* The program launches a simple process hierarchy consisting of 2 processes.
 * Both output their PIDs and terminate while following the usual unix-style
 * procedure. */

/* QUESTION: what syscall is used for forking the process */

/* QUESTION: what happens to the child when the parent doesn't wait for its
 * children to terminate and just exists immediately? */

/* QUESTION: what is the syscall used in wait? */

/* QUESTION: what is the syscall used in exit? */

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    pid_t parent_pid = getpid();

    /* Just fork and ignore possible error conditions here. */
    pid_t child_pid = fork();
    if (child_pid == 0) {
        /* A child is born! */
        child_pid = getpid();

        /* In the end of the day printf is just a call to write(2). */
        printf("child (self=%d)\n", child_pid);
        exit(EXIT_SUCCESS);
    }

    /* Business as usual for the parent. */
    printf("parent (self=%d, child=%d)\n", parent_pid, child_pid);

    /* Wait for child termination. */
    wait(NULL);

    exit(EXIT_SUCCESS);
}
