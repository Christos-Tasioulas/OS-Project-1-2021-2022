// This is the file that connects every module with each other
#ifndef INTERFACE
#define INTERFACE
#include <cstdlib> 
#include "SHM_Structure.h"

using namespace std;

// Solution.cpp
// takes over the whole program
int solution(struct SHM_Structure *shm, int num_of_lines, int numTransactions);

#endif