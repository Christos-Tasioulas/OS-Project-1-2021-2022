#include "Interface.h"

// takes over the whole program
int solution(struct SHM_Structure *shm, int num_of_lines, int numChildren, int numTransactions, int shmid, pid_t* child_processes, char* filename)
{
    // Creating a structure with the objects we will share with the child proccesses
    int shm_result = shm_struct_init(shm); 

    // Error Handling
    if(shm_result)
    {
        cout << "Error creating shared memory" << endl;
        return -1;
    }

    int total_transactions = numChildren * numTransactions;
    // Integer variable for error handling the semaphores
    int result;

    for(int i=0; i<total_transactions; i++)
    {
        // wait for the client to finish
        result = sem_wait(&shm->server_sem);

        // Error handling
        if(result)
        {
            cout << strerror(errno) << endl;
            return -1;
        }

        // reading the number the child sent
        int line_num = shm->line_num;
        cout << line_num << endl;
        
        // getting the line from the file
        string line = get_specific_file_line(filename, line_num, get_file_size(filename));
        
        // write the line at the shared memory
        set_line(shm, line);

        // the wait for the text is over 
        result = sem_post(&shm->text_sem);

        // Error handling
        if(result)
        {
            cout << strerror(errno) << endl;
            return -1;
        }
    }

    // Destroying the shared structure 
    shm_result = shm_struct_destroy(shm);

    // Error Handling
    if(shm_result)
    {
        cout << "Error destroying shared memory" << endl;
        return -1;
    }

    return 0;
}