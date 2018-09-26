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

    // *** cant pass variables out of shared memory
    passedNValue = cint[0];
    cint[2] += (passedNValue * 1000000);

    cint[1] = cint[1] + (cint[2] / 1000);
    cint[2] = cint[2] % (cint[1] * 1000);

    printf("n is %d, seconds %d, millis %d\n", passedNValue, cint[1], cint[2]);

    sleep(2);

    shmdt(cint);

    return 0;
}
