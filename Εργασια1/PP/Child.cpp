#include <unistd.h>
#include <sys/wait.h>
#include "Interface.h"

// Creates as many child processes as given
// Returns an array of the child processes' id
pid_t* child_creation(int numOfChildren, int numOfLines, int numOfTransactions, int shmid)
{
    pid_t* process_ids;
    process_ids = new pid_t[numOfChildren];

    for(int child=0; child<numOfChildren; child++)
    {
        // forking to create child processes
        process_ids[child] = fork();

        // error checking the process
        if(process_ids[child] == -1)
        {
            perror("fork");
            return NULL;
        }
        else if(process_ids[child] == 0)
        {
            string lines = to_string(numOfLines);
            string transactions = to_string(numOfTransactions);
            string key = to_string(shmid); 
            // ./child <numOfLines> <numOfTransactions> <shmid>
            execl("../CP/child", "./child", lines.c_str(), transactions.c_str(), key.c_str(), (char*) NULL);
            perror("execl");
            return NULL;
        }
    }

    return process_ids;
}

// Makes the parent wait for the given child processes
// Returns true if everything works properly and false if not
bool child_waiting(pid_t* processes_ids, int numOfChildren)
{
    for(int child = 0; child < numOfChildren; child++)
    {
        pid_t wait_id = waitpid(processes_ids[child], NULL, 0);

        // Error checking the wait function
        if(wait_id == -1)
        {
            perror("waitpid");
            return false;
        }
    }
    return true;
}