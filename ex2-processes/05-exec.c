#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/* The fork call creates a mostly identical copy of the calling process (the
 * parent), and fork famously is the only way to create processes on Unix-likes
 * systems.
 *
 * To launch non-copies we use an additional call family - the exec* call
 * family, which replaces the calling process's memory with a program from the
 * specified path. */

/* QUESTION: what do exec-like functions return? */

/*  */

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    setbuf(stdout, NULL);

    switch (fork()) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        /* Child */

        printf("[pid=%d] child \n", getpid());

        /* QUESTION: finding out why casting NULLs to char* is necessary in
         * variadic functions will help to appreciate the Zen of C */

        execl("/bin/echo", "echo", "Hello", "Child", (char *)NULL);

        /* QUESTION: comment the execl call above and uncomment the line below.
         * Sleep will make the child sleep for 10 seconds. Try to think of a way
         * to utilise the alarm(2) call to limit the life of a child process.*/

        /* execl("/bin/sleep", "sleep", "10s", (char *)NULL); */

        /* QUESTION: why is there no conditional checking that an error really
         * happened? */
        perror("execl");
        exit(EXIT_FAILURE);

    default:
        /* Parent */

        printf("[pid=%d] parent \n", getpid());
        break;
    }

    exit(EXIT_SUCCESS);
}
