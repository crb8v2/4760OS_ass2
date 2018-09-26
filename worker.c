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

    //shared memory
    int shmid = shmget ( SHMKEY, sizeof(bufferArray[2]), 0775 | IPC_CREAT );
    if ( shmid == -1 )
    {
        printf("Error in shared memory1");
        return 1;
    }
    // pointer to shared memory that prints n
    int *cint = ( shmat ( shmid, NULL, 0 ) );

    // array pos:
    //          0 = value of n
    //          1 = seconds
    //          2 = milliseconds
    // can't convert to variables w/ shared memory
    passedNValue = cint[0];
    cint[0] += 1;
    cint[2] += (passedNValue * 1000000);

    printf("n is %d, seconds %d, millis %d\n", passedNValue, cint[1], cint[2]);

    sleep(2);

    shmdt(cint);

    return 0;
}
