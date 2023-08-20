#include <sys/time.h> 
#include <unistd.h>
#include "Interface.h"

// Asssistant function

// returns a random number from 1 to the number given using the process_id as well
int random_line(int num_of_lines)
{
    // generating a random number as the number of lines we will get  // let's call it b
    int random = rand() % num_of_lines + 1;

    // a factor to differentiate the demands between child processes  // let's call it a
    int pid_factor = getpid();
    pid_factor = pid_factor % num_of_lines + 1;

    // returns [(a + b) div 2] + [(a + b) mod 2]
    return ((pid_factor + random)/2 + (pid_factor + random)%2);
}

// takes over the whole program
int solution(struct SHM_Structure *shm, int num_of_lines, int numTransactions)
{

    // Integer variable for error handling the semaphores
    int result;

    // initializing the overall process time variable 
    suseconds_t processes_time = 0.0;

    for(int i=0; i<numTransactions; i++)
    {

        // the client has to wait
        result = sem_wait(&shm->client_sem);

        // Error handling
        if(result)
        {
            cout << strerror(errno) << endl;
            return -1;
        }

        // the moment the timer starts counting
        struct timeval start, stop;
        gettimeofday(&start, NULL);

        // gives a line number decided by the random function above
        int line_num = random_line(num_of_lines);
        set_line_num(shm, line_num);

        // starts the server process
        result = sem_post(&shm->server_sem);

        // Error handling
        if(result)
        {
            cout << strerror(errno) << endl;
            return -1;
        }

        // waiting for the text to appear
        result = sem_wait(&shm->text_sem);

        // Error handling
        if(result)
        {
            cout << strerror(errno) << endl;
            return -1;
        }

        // reading the text when done waiting
        string line(shm->line);
        cout << line << endl;

        // the moment the time stops counting
        gettimeofday(&stop ,NULL);
        // adding the time of each transaction to the overall time to calculate its average afterwards
        processes_time += (stop.tv_usec-start.tv_usec);

        // the client will not wait now
        result = sem_post(&shm->client_sem);

        // Error handling
        if(result)
        {
            cout << strerror(errno) << endl;
            return -1;
        }
    }

    // finding the average time per transaction in the process
    suseconds_t average_time = processes_time/((suseconds_t) numTransactions);
    cout << getpid() << " Average process time per transaction: " << average_time <<  " microseconds" << endl;

    return 0;
}