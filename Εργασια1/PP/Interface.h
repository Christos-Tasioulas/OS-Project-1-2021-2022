// This is the file that connects every module with each other
#ifndef INTERFACE
#define INTERFACE
#include "SHM_Structure.h"

// Child.cpp

// Creates as many child processes as given 
// Returns an array of the child processes' id
pid_t* child_creation(int numChildren, int numOfLines, int numOfTransactions, int shmid);

// // Makes the parent wait for the given child processes
// // Returns true if everything works properly and false if not
bool child_waiting(pid_t* processes_ids, int numMonitors);

// File.cpp

// Returns the number of lines in the file
int get_file_size(char* filename);

// Returns the line with the number given from the file given
// Notice that the number of the line should be smaller than the size of the file
string get_specific_file_line(char* filename, int line_num, int file_size);

// Solution.cpp
// takes over the whole program
int solution(struct SHM_Structure *shm, int num_of_lines, int numChildren, int numTransactions, int shmid, pid_t* child_processes, char* filename);

#endif