#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// performs forking and work to be done
void forkerMaster (int n, int s) {
    pid_t childpid = 0, wpid;
    int counter1;
    int status;


    for(counter1 = 0; counter1 < s; counter1++){
        if (childpid = fork() == 0)
            execl ("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2/Worker",
                   "Worker", NULL);
    }

    while (counter1 < n) {
        wait(&status);
        if (childpid = fork() == 0)
            execl ("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2/Worker",
                   "Worker", NULL);
        counter1++;
    }

//    // create forks
//    for (counter1 = 0; counter1 < n; counter1++) {
//        if (childpid = fork())
//            execl ("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2/Worker",
//                   "Worker", NULL);
//    }

    //*** children never come back to here.


    wait(NULL);

    fprintf(stderr, "i:%d, process ID:%ld, parent ID: %ld, child ID:%ld\n",
            counter1, (long)getpid(), (long)getppid(), (long)childpid);
}


void helpMenu() {
    printf("\n -- HELP MENU --\n");
    printf("-n int    runs int number of forks\n");
    printf("-h    open help menu\n");

}


int main (int argc, char **argv) {

    int c, n = 0, s = 0;
    int isForkCalled = 0;

    // for options
    while ((c = getopt (argc, argv, "hs:n:")) != -1)
        switch (c)
        {
            case 'h':
                helpMenu();
                break;

            case 's':
                s = atoi(optarg);

                printf("\ninput for s was : %d\n", s);
                break;

            case 'n':
                //get command line values
                n = atoi(optarg);
                isForkCalled = 1;
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
                abort();
        }

        if(isForkCalled == 1){
            forkerMaster(n,s);
        }

        sleep(1);
    return 0;
}


