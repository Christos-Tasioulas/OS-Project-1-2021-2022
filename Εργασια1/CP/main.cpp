#include <sys/shm.h>
#include "Interface.h"

// main function for child process
int main(int argc, char* argv[])
{
    int numOfLines = atoi(argv[1]);
    int numOfTransactions = atoi(argv[2]);
    int shmid = atoi(argv[3]);

    // reading the shared memory structure
    struct SHM_Structure *shm = (struct SHM_Structure*) shmat(shmid, NULL, 0);

    int solved = solution(shm, numOfLines, numOfTransactions);
    if(solved == -1) 
    {
        cout << "Error!" << endl;
        return solved;
    }

    shmdt(shm);

    return 0;
}