#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* Signals delivered to a process can be initiated on behalf of the process
 * itself, some other process or the kernel itself. Signal delivery is
 * asynchronous, i.e it interrupts the execution of the currently running code.
 * All signals have default actions to be executed upon signal delivery, and
 * it's possible to replace the default action with some user code to be
 * executed whenever a signal arrives. */

/* QUESTION: What happens when a user types Ctrl-C or Ctrl-\ in a terminal?  */

/* QUESTION: What is the default action for the SIGTERM signal? SIGKILL? What's
 * the difference between the signals? */

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    /* disable stdout buffering */
    setbuf(stdout, NULL);

    /* QUESTION: Alarm delivers a SIGALRM signal to the current signal. What is
     * the default action of the signal? */
    alarm(10);

    printf("taking a pause...\n");

    /* Pause causes the process to sleep until a signal-handling function
     * returns. */
    pause();

    /* QUESTION: Why doesn't this get printed? Is there a way to output the
     * string? */
    printf("pause() interrupted\n");

    return 0;
}
