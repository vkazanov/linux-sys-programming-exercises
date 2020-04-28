#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* Waiting for children results in retrieving some information about terminated
 * child processes (e.g.return code, pid, etc). So if a child process terminates
 * but the parent doesn't wait for it then the information will have to be kept
 * in system tables until parent requests it.
 *
 * Those dead but unwaited-for child processes are called zombies. */

/* QUESTION: follow the program execution using the ps(1) shell utility */

/* QUESTION: what happens if the parent process just keeps creating zombies?  */

/* QUESTION: is there a way to kill a zombie process manually? */

/* QUESTION: let's say the parent process is busy with it's parenting business,
 * and has no time for waiting. Apart from explicit waiting in the parent
 * process find an alternative (an quite popular in practise) way of handling
 * child termination. Use it to avoid creating zombies in the program.  */

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    setbuf(stdout, NULL);

    int zombies_to_create = 10;

    while (zombies_to_create > 0) {
        switch(fork()) {
        case -1:
            break;
        case 0:
            /* Child processed die immediately */
            printf("[child_pid=%d] child dying\n", getpid());
            exit(EXIT_SUCCESS);
        default:
            /* Parent goes on to create more children... */
            printf("[parent_pid=%d] child %d added\n", getpid(), zombies_to_create);
            zombies_to_create--;
            break;
        }
    }

    /* And then the parent sleeps without waiting for children */
    printf("[parent_pid=%d] sleeping\n", getpid());

    sleep(10);                  /* very important parent process work happens
                                 * here */
    printf("[parent_pid=%d] done\n", getpid());

    return 0;
}
