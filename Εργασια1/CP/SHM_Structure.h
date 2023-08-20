#ifndef SHM_STRUCTURE
#define SHM_STRUCTURE
#include <iostream>
#include <cstring>
#include <errno.h>
#include <semaphore.h>

#define MAX_LENGTH 100

struct SHM_Structure{
    sem_t client_sem; // semaphore for the client to wait
    sem_t server_sem; // semaphore for the server to wait
    sem_t text_sem;   
    // semaphore for the client to wait for the text to be prepared before being read
    unsigned int line_num;  // number of line that will be sent to the server
    char line[MAX_LENGTH];  // line that will be sent to the client
};

// sends the number of the line it wants
void set_line_num(struct SHM_Structure *shm, int line_num);

#endif