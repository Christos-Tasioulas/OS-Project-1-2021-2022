#include "SHM_Structure.h"

// initializes the shared memory structure 
// returns 0 if successful and -1 if not
int shm_struct_init(struct SHM_Structure *shm)
{
    char space[2] = " ";
    strcpy(shm->line, space);

    shm->line_num = 0;
    
    /* Initializing the semaphores */
    /*
        Client is the only semaphore that starts with value 1 because the client process is the first one that must happen
        even after the first sem_wait for client will be called
        (The client will send first the line that it wants and afterwars the server will send the line itself) 
    */

    int client = sem_init(&shm->client_sem, 1, 1);
    // Error Handling
    if(client)
    {
        cout << strerror(errno) << endl;
        return -1;
    } 

    int server = sem_init(&shm->server_sem, 1, 0);
    // Error Handling
    if(server) 
    {
        cout << strerror(errno) << endl;
        return -1;
    } 

    int text = sem_init(&shm->text_sem, 1, 0);
    // Error Handling
    if(text) 
    {
        cout << strerror(errno) << endl;
        return -1;
    }
    
    return 0;
}

// changes the line that the structure will include
void set_line(struct SHM_Structure *shm, string line)
{
    strcpy(shm->line, line.c_str());
}

// destroys the structure
// returns 0 if successful and -1 if not
int shm_struct_destroy(struct SHM_Structure *shm)
{

    /* Destroying the semaphores */

    int client = sem_destroy(&shm->client_sem);
    // Error Handling
    if(client)
    {
        cout << strerror(errno) << endl;
        return -1;
    } 

    int server = sem_destroy(&shm->server_sem);
    // Error Handling
    if(server) 
    {
        cout << strerror(errno) << endl;
        return -1;
    } 

    int text = sem_destroy(&shm->text_sem);
    // Error Handling
    if(text) 
    {
        cout << strerror(errno) << endl;
        return -1;
    }

    return 0;
}