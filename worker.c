#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 123123
#define BUFF_SZ sizeof(int)

int main() {

    //shared memory
    int shmid = shmget ( SHMKEY, BUFF_SZ, 0777 | IPC_CREAT );
    if ( shmid == -1 )
    {
        printf("Error in shared memory");
        return 1;
    }
    // pointer to shared memory
    int *cint = ( int * )( shmat ( shmid, 0, 0 ) );

    printf("n is %d\n", *cint);

    sleep(2);

    return 0;
}
