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
    pid_t pid;
    int counter1;

    // create forks
    for (counter1 = 1; counter1 < n; counter1++) {
        if ((childpid = fork()))
//            execl ("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2/Worker",
//                    "Worker", NULL);

//            if (childpid == 0)
//                perror("fork error");
//            else if (childpid == 0) {
//                execl("Worker","Worker");
//            }
            break;
    }

//    execl ("/home/crbaniak/Documents/umslClasses/fall18/4760_OS/code/ass2",
//           "Worker", NULL);

    fprintf(stderr, "i:%d, process ID:%ld, parent ID: %ld, child ID:%ld\n",
            counter1, (long)getpid(), (long)getppid(), (long)childpid);
}


void helpMenu() {
    printf("\n -- HELP MENU --\n");
    printf("-n int    runs int number of forks\n");
    printf("-h    open help menu\n");

}


int main (int argc, char **argv) {

    int n = 0;
    int c;
    char errorString[256];

    // for options
    while ((c = getopt (argc, argv, "hn:")) != -1)
        switch (c)
        {
            case 'h':
                helpMenu();
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



















//
//
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <unistd.h>
//
//
//int main(void)
//{
//    char *my_args[5];
//    pid_t pid;
//
//    my_args[0] = "child.exe";
//    my_args[1] = "arg1";
//    my_args[2] = "arg2";
//    my_args[3] = NULL;
//
//    puts ("fork()ing");
//
//    switch ((pid = fork()))
//    {
//        case -1:
//            /* Fork() has failed */
//            perror ("fork");
//            break;
//        case 0:
//            /* This is processed by the child */
//            execv ("Worker", my_args);
//            puts("Uh oh! If this prints, execv() must have failed");
//            exit(EXIT_FAILURE);
//            break;
//        default:
//            /* This is processed by the parent */
//            puts ("This is a message from the parent");
//            break;
//    }
//
//    puts ("End of parent program");
//    return 0;
//}
//
///*
// * Program output:
// fork()ing
// This is a message from the parent
// End of parent program
// I am the child
// Arg 1 arg1
// Arg 2 arg2
// *
// */