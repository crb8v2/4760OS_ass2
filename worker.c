#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 123123

int main() {

    int bufferArray[2];
    int passedNValue;
    int seconds, millis;

    //shared memory
    int shmid = shmget ( SHMKEY, sizeof(bufferArray[2]), 0775 | IPC_CREAT );
    if ( shmid == -1 )
    {
        printf("Error in shared memory1");
        return 1;
    }
    // pointer to shared memory that prints n
    int *cint = ( shmat ( shmid, NULL, 0 ) );

    //set nice variable names
    passedNValue = cint[0];
    seconds = cint[1];
    millis = cint[2];

    printf("n is %d, seconds %d, millis %d\n", passedNValue, seconds, millis);








    sleep(2);

    shmdt(cint);

    return 0;
}
