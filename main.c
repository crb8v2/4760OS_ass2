#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 123123

// performs forking and work to be done
int forkerMaster (int n, int s) {
    pid_t childpid = 0;
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

    pint[0] = n;
    pint[1] = 0;
    pint[2] = 0;

    // if n is bigger than s
    if(n >= s) {
        for (counter1 = 0; counter1 < s; counter1++) {
            if ((childpid = fork()) == 0)
                execl("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2/Worker",
                      "Worker", NULL);
        }
        while (counter1 < n) {
            //waits for a child to report finished
            wait(&status);
            if ((childpid = fork()) == 0)
                execl("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2/Worker",
                      "Worker", NULL);
            counter1++;
        }
    // if n is smaller than s
    } else {
        for (counter1 = 0; counter1 < n; counter1++) {
            if ((childpid = fork()) == 0)
            execl ("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2/Worker",
                   "Worker", NULL);
        }
    }

    //*** children never come back to here.
    // waits for all children to finish
    wait(NULL);

    shmdt(pint);

    fprintf(stderr, "i:%d, process ID:%ld, parent ID: %ld, child ID:%ld\n",
            counter1, (long)getpid(), (long)getppid(), (long)childpid);
    return 0;
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


        // fork should be called outside of option switch
        // so that if the forks do not begin before all options are read
        if(isForkCalled == 1){
            forkerMaster(n,s);
        }

        sleep(1);

        return 0;
}


