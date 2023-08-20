#include "Interface.h"
#include <fstream>

// Returns the number of lines in the file
int get_file_size(char* filename)
{
    ifstream fileX(filename);
    int file_size = 0;
    if(fileX.is_open())
    {
        string temp;
        while(getline(fileX, temp))
        {
            file_size++;
        }
    }
    fileX.close();
    return file_size;
}

// Returns the line with the number given from the file given
// Notice that the number of the line should be smaller than the size of the file
string get_specific_file_line(char* filename, int line_num, int file_size)
{
    string line = "";
    // checking if the line number is greater than the number of lines in the file
    if(line_num > file_size) 
    {
        cout << "Error line does not exist" << endl;
    }
    else
    {
        int counter = 0;
        ifstream fileX(filename);
        if(fileX.is_open())
        {
            string temp;
            while(getline(fileX, temp))
            {
                counter++;
                // we found the line
                if(counter == line_num)
                {
                    line = temp;
                    fileX.close();
                    return line;
                }
            }
        }
        fileX.close();
    }
    return line;
}
