#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// performs forking and work to be done
void forkerMaster (int n) {
    pid_t childpid = 0;
    int counter1;

    // create forks
    for (counter1 = 1; counter1 < n; counter1++) {
        if ((childpid = fork()))
            break;
    }

    fprintf(stderr, "i:%d, process ID:%ld, parent ID: %ld, child ID:%ld\n",
            counter1, (long)getpid(), (long)getppid(), (long)childpid);
}


void helpMenu() {
    printf("\n -- HELP MENU --\n");
    printf("-n int int int    runs a forking function\n");
    printf("-h    open help menu\n");
    printf("-p    generates a test error with perror\n\n");
}


int main (int argc, char **argv) {

    int n = 0;
    int c;
    char errorString[256];

    // for options
    while ((c = getopt (argc, argv, "hpn:")) != -1)
        switch (c)
        {
            case 'h':
                helpMenu();
                break;

            case 'p':
                snprintf( errorString, sizeof errorString,
                          "This, my friend, is an error");
                perror(errorString);
                break;

            case 'n':
//                // checks for proper number of args
//                if (argc != 4) {
//                    fprintf(stderr, "Invalid number of command line args.");
//                    return 1;
//                }

                //get command line values
                n = atoi(argv[2]);

                forkerMaster(n);

                break;

            case '?':
                if (optopt == 'n')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;
            default:
                abort ();
        }
        sleep(1);
    return 0;
}