#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* The program writes a string to standard output and exits immediately
 * afterwards */

/* QUESTION: run the program under strace. which syscall is used for writing the
 * string to standard output? */

void do_write(void)
{
    char str[] = "write me to stdout\n";

    /* write(2) is a simple wrapper around a syscall so it should be easy to
     * find in the syscall trace. */

    /* Notice the use of the STDOUT_FILENO macro which referers to one of the 2
     * descriptors open by default upon process start */
    if (sizeof(str) != write(STDOUT_FILENO, str, sizeof(str))){
        perror("write");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[])
{
    /* gcc -Wall -Wextra (and we should always go for both) doesn't like unused
     * parameters so we silence the compiler. */
    (void) argc; (void) argv;

    do_write();

    /* Notice the return values. Process return values are not very well defined
     * in Linux and across UNIX-likes in general. Generally it's 0 for success
     * and any other values. So it's easier to just stick with standard macros
     * provided by stdlib. */
    return EXIT_SUCCESS;
}
