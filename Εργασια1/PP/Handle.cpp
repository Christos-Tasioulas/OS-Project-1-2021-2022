#include "Handle.h"
#include "Interface.h"
#include <sys/ipc.h>
#include <sys/shm.h>

// Takes control of the program after working with the run command arguments in the main function
// Returns the line an error occured or 0 if it worked properly
int handle(int numChildren, int numTransactions, string input_file)
{
    char* filename = new char[input_file.length()+1];
    strcpy(filename, input_file.c_str());
    int num_of_lines = get_file_size(filename);

    // Creating a shared memory space for parents and children to share
    int shmid = shmget(IPC_PRIVATE, sizeof(struct SHM_Structure), 0666);

    // Error Handling
    if(shmid == -1)
    {
        cout << strerror(errno) << endl;
        return 15;
    }

    struct SHM_Structure *shm = (struct SHM_Structure*) shmat(shmid, NULL, 0);

    // Error Handling
    if(shm == (void *) -1)
    {
        cout << strerror(errno) << endl;
        return 24;
    }

    // Creating the children
    pid_t* child_processes;
    child_processes = child_creation(numChildren, num_of_lines, numTransactions, shmid);

    // Error checking for the children
    if(child_processes == NULL)
    {
        cout << "Error creating children!" << endl;
        return 35;
    } 

    // Moving to the solution
    int solved = solution(shm, num_of_lines, numChildren, numTransactions, shmid, child_processes, filename);
    if(solved == -1) return 45;

    // Waiting for the child proccesses to finish
    bool wait = child_waiting(child_processes, numChildren);

    // Error checking the waiting function
    if(wait == false)
    {
        cout << "Error waiting the child processes" << endl;
        return 49;
    }

    // delete functions
    delete[] filename;
    delete[] child_processes;

    int result = shmdt(shm);

    // Error Handling
    if(result)
    {
        cout << strerror(errno) << endl;
        return 62;   
    }

    result = shmctl(shmid, IPC_RMID, NULL);

    // Error Handling
    if(result)
    {
        cout << strerror(errno) << endl;
        return 69;   
    }

    return 0;
}