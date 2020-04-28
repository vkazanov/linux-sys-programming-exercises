#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* The program demostrates what happens to "orphaned" processes, i.e. processes
 * parent exited without waiting for a child process to exit*/

/* QUESTION: what program is the root of the process tree on your system? */

/* QUESTION: find a name of a shell command that shows the complete process tree */

/* QUESTION: compare how stdout buffering mixes output from the processes.
 * Uncomment fflush lines. Find a way to disable buffering for stdout using a
 * single call (try checking the fflush(3) man page for alternatives)*/

/* QUESTION: unlike original Unix-likes Linux now supports using non-init (i.e.
 * pid != 1) processes for receiving orphaned processes. This program doesn't
 * work for this case. Implement a (trivial) fix for the case. */

/* QUESTION: what happens if we replace exit(3) with _exit(2)? */

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    pid_t child_pid;
    switch (child_pid = fork()) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        /* Child process */

        for (;;) {
            pid_t parent_pid = getppid();
            if (parent_pid == 1){
                printf("[pid=%d, ppid=%d] child terminating!\n", child_pid, getppid());
                /* fflush(stdout); */
                break;
            }
            printf("[pid=%d, ppid=%d] child still sleeping...\n", child_pid, getppid());
            /* fflush(stdout); */
            sleep(1);
        }
        exit(EXIT_SUCCESS);

    default:
        /* Parent process */

        printf("[pid=%d] parent sleeping...\n", getpid());
        /* fflush(stdout); */
        sleep(2);
        printf("[pid=%d] parent terminating\n", getpid());
        /* fflush(stdout); */
        exit(EXIT_SUCCESS);
    }
}
