#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* For most signals user handlers can installed, i.e. custom logic executed on
 * signal delivery. User code can also temporarily block signals, which is very
 * helpful for designing signal handlers. */

void do_write(const char *str)
{

    /* QUESTION: why using a raw write instead of a more convenient printf()
     * function? */
    size_t ss = strlen(str) + 1;
    if ((ssize_t)ss != write(STDOUT_FILENO, str, ss)){
        exit(EXIT_FAILURE);
    }

}

void handle_sig(int sig)
{
    (void) sig;
    switch (sig) {
    case SIGINT:
        do_write("SIGINT arrived\n");
        break;
    case SIGTERM:
        do_write("SIGTERM arrived\n");
        break;
    default:
        /* QUESTION: why using _exit and not the usual exit? */
        _exit(EXIT_FAILURE);

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

void block(int sig)
{
    sigset_t to_block;
    sigaddset(&to_block, sig);
    sigprocmask(SIG_BLOCK, &to_block, NULL);
}

void unblock(int sig)
{
    sigset_t to_unblock;
    sigaddset(&to_unblock, sig);
    sigprocmask(SIG_UNBLOCK, &to_unblock, NULL);
}

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    setbuf(stdout, NULL);

    /* Install a simple handler for Ctrl-C (aka the SIGINT signal) */
    set_handler(SIGINT, handle_sig);
    printf("Press Ctrl-C to unpause...\n");
    pause();

    /* QUESTION: what happens if a second SIGINT arrives while the first handler
     * is still in flight? */

    /* Use an additional signal (Ctrl-\, or SIGQUIT) for unpausing. */
    set_handler(SIGQUIT, handle_sig);

    /* Block Ctrl-C */
    block(SIGINT);
    printf("Press Ctrl-C at least 2 times, followed by Ctrl-\\ to unpause\n");
    pause();
    /* Unblock Ctrl-C */
    unblock(SIGINT);

    /* QUESTION: how many times was SIGINT handled after unblocking? */

    /* QUESTION: what exit status did the process return?  */

    return 0;
}
