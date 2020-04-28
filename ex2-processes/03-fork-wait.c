#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* If a process terminates without waiting for its children to properly
 * terminate then child processes will become orphaned, i.e. they will be
 * reparented to the init process.
 *
 * A special call family - wait, waitpid, waitid - help with waiting for
 * children to terminate. */

/* QUESTION: what happens if a parent doesn't wait for a child to terminate? */

/* QUESTION: who waits for unwaited-for children if a parent goes away? */

/* QUESTION: figure out a way for a parent process to retrieve exit codes of
 * terminating children */

void do_work(void)
{
    sleep(3);
}

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    /* Let's disable buffering for stdout */
    setbuf(stdout, NULL);

    int children_left_to_spawn = 10;

    while (children_left_to_spawn > 0) {
        switch (fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;

        case 0:
            /* Child process */
            do_work();
            goto done;

        default:
            /* Parent process*/
            children_left_to_spawn--;
            break;
        }
    }

    pid_t child_pid;
    while ((child_pid = wait(NULL)) > 0)
        printf("[child_pid=%d] child done\n", child_pid);

    printf("parent done\n");

done:

    return EXIT_SUCCESS;
}
