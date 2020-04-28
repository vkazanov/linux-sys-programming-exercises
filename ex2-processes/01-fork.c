#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The program writes a string to stdout twice, i.e. from both a child and a
 * parent processes. A canonical UNIX way of creating processes is used -
 * through the fork(2) call*/

/* QUESTION: what happens if a parent terminates first? child? use sleep(3) to
 * check both conditions */

/* QUESTION: for both processes additionally output it's process ID (PID) and
 * parent process ID (PPID) using printf and relevant standard UNIX APIs */

/* QUESTION: fork() as it's used here is no longer just a wrapper around the
 * fork system call . Find the system call and the corresponding glibc wrapper,
 * and replace fork() with it */

void do_write(const char *str)
{
    /* There numerous inconsistencies and problems in C standard library and
     * standards of UNIX application programming interfaces (SVr4, 4.3BSD,
     * POSIX). Notice how it's hard to conveniently avoid type casting here.
     *
     * QUESTION: by the way, what are those SVr4, 4.3BSD, POSIX mentioned in
     * Linux manual pages? */
    size_t ss = strlen(str);
    if ((ssize_t)ss != write(STDOUT_FILENO, str, ss)){
        perror("write");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    /* fork(2) function creates a child process or returns an error. It used to
     * be a system call but nowadays on Linux it's implemented as a wrapper
     * around another glibc function. */
    if (fork() == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /* As we have two processes running now we should write the function
     * argument twice. */
    do_write("0123456789");

    return EXIT_SUCCESS;
}
