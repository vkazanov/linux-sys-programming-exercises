#include <unistd.h>
#include <stdlib.h>

/* This process hangs indefinitely so we need to debug the process by attaching
 * to a running process */

/* QUESTION: attach to a running process. which syscall is responsible for
 * hanging?
 *
 * QUESTION: is there a way to wake up the process?*/

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    char str[] = "write me\n";

    write(STDOUT_FILENO, str, sizeof(str));

    /* Sleep indefinitely or until a signal arrives. */
    pause();

    write(STDOUT_FILENO, str, sizeof(str));

    return EXIT_SUCCESS;
}
