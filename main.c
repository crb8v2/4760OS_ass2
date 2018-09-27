#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define SHMKEY 123123

// performs forking and work to be done
int forkerMaster (int nn, int ss) {
    int counter1;
    int status;
    int bufferArray[2];

    //shared memory (key, size, permissions)
    int shmid = shmget ( SHMKEY, sizeof(bufferArray[2]), 0775 | IPC_CREAT );

    if ( shmid == -1 )
    {
        printf("Error in shared memory");
        return 1;
    }

    //get pointer to memory block
    char * paddr = ( char * )( shmat ( shmid, NULL, 0 ) );
    int * pint = ( int * )( paddr );

    pint[0] = nn;
    pint[1] = 0;
    pint[2] = 0;

    // if n is bigger than s
    if(nn >= ss) {
        for (counter1 = 0; counter1 < ss; counter1++) {
            if ((fork()) == 0)
                execl("./Worker",
                      "Worker", NULL);
        }
        while (counter1 < nn) {
            //waits for a child to report finished
            wait(&status);
            if ((fork()) == 0)
                execl("./Worker",
                      "Worker", NULL);
            counter1++;
        }
    // if n is smaller than s
    } else {
        for (counter1 = 0; counter1 < nn; counter1++) {
            if ((fork()) == 0)
            execl ("./Worker",
                   "Worker", NULL);
        }
    }

    //*** children never come back to here.
    // waits for all children to finish
    wait(NULL);

    printf("Seconds: %d Millis: %d\n", pint[1], pint[2]);

    shmdt(pint);

//    fprintf(stderr, "i:%d, process ID:%ld, parent ID: %ld, child ID:%ld\n",
//            counter1, (long)getpid(), (long)getppid(), (long)childpid);
    return 0;
}

// help menu
void helpMenu() {
    printf("\n -- HELP MENU --\n");
    printf("-n (int) -s (int)     runs n number of forks, with max of s at any given time\n");
    printf("-h                    open help menu\n");

}

// alarm magic
static void ALARMhandler()
{
    printf("Time ran out!\n");
    exit(EXIT_SUCCESS);
}

int main (int argc, char **argv) {

    int c, nn = 0, ss = 0;
    int isForkCalled = 0;

    // for options
    while ((c = getopt (argc, argv, "hs:n:")) != -1)
        switch (c)
        {
            case 'h':
                helpMenu();
                break;

            case 's':
                ss = atoi(optarg);           // forks allowed at once
                break;

            case 'n':
                nn = atoi(optarg);           // total forks
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


        //alarm times out if forks all do not return in 2 seconds
        signal(SIGALRM, ALARMhandler);
        alarm(2);
        // fork should be called outside of option switch
        // so that if the forks do not begin before all options are read
        if(isForkCalled == 1){
            forkerMaster(nn,ss);
        }
        return 0;
}


