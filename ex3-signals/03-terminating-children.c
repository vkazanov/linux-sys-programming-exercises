#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <assert.h>

/* Signal handlers can be quite hard to write at times, with numerous gotchas.
 * Two major ones: signal queueing and functions that are safe to use in signal
 * handlers (signal-safe functions).
 *
 * One good example is trying to handle child termination in a SIGCHLD handler
 * while doing important work in the parent process.
 */

void do_write(const char *str)
{
    size_t ss = strlen(str) + 1;
    if ((ssize_t)ss != write(STDOUT_FILENO, str, ss)){
        exit(EXIT_FAILURE);
    }

}

typedef void (handler_function) (int);

void set_handler(int sid, handler_function *h)
{
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = h;
    sigemptyset(&sa.sa_mask);

    if (sigaction(sid, &sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int children_terminated = 0;

void handle_sigchld(int sid)
{
    (void) sid;

    /* QUESTION: how many signals were handled? */
    do_write("SIGCHLD received\n");

    /* QUESTION: fix the handler to make sure the initial process always
     * terminates */
    assert(wait(NULL) > 0);
    children_terminated++;
}

#define CHILD_NUM 16

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    set_handler(SIGCHLD, handle_sigchld);

    /* Let's overpopulate the planet! */
    int children_to_spawn = CHILD_NUM;
    while (children_to_spawn > 0) {
        switch (fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;

        case 0:
            /* Child */

            do_write("child spawned\n");
            sleep(1);           /* imitate work */
            do_write("child terminating\n");
            goto done;

        default:
            /* Parent*/

            children_to_spawn--;
            break;
        }
    }

    /* QUESTION: most of the time control flow never leaves the loop. Why? */
    while (children_terminated < CHILD_NUM)
        sleep(1);

done:

    return EXIT_SUCCESS;
}
