#ifndef SHM_STRUCTURE
#define SHM_STRUCTURE
#include <iostream>
#include <string>
#include <cstring>
#include <errno.h>
#include <semaphore.h>

#define MAX_LENGTH 100

using namespace std;

struct SHM_Structure{
    sem_t client_sem; // semaphore for the client to wait
    sem_t server_sem; // semaphore for the server to wait
    sem_t text_sem;   
    // semaphore for the client to wait for the text to be prepared before being read
    unsigned int line_num;  // number of line that will be sent to the server
    char line[MAX_LENGTH];  // line that will be sent to the client
};

// initializes the shared memory structure, returns it
// returns 0 if successful and -1 if not
int shm_struct_init(struct SHM_Structure *shm);

// changes the line that the structure will include
void set_line(struct SHM_Structure *shm, string line);

// destroys the structure
// returns 0 if successful and -1 if not
int shm_struct_destroy(struct SHM_Structure *shm);

#endif