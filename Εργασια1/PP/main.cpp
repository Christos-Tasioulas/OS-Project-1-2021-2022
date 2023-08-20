#include <cstdlib>
#include "Handle.h"

int main(int argc, char* argv[])
{
    // Checking if we have the right number of arguments
    if(argc != 4)
    {
        cout << "Usage: ./parent input_file numChildren numTransactions" << endl;
        return -1;
    }

    // this are the variables we will use instead of the argv array
    string input_file = argv[1];
    int numChildren = atoi(argv[2]);
    int numTransactions = atoi(argv[3]);

    // adding the fact that the file is one directory above
    string above = "../";
    input_file = above.append(input_file);

    // this is where the program starts creating processes
    int line = handle(numChildren, numTransactions, input_file);
    if(line)
    {
        cout << "Error at line " << line << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}