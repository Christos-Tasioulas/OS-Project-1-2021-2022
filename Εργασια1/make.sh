#!/bin/bash

# this bash script compiles the two processes from the different directories simultaneously and with the same commands
count=$#

# checking the number of arguments it should be one or two 
if [[ ($count -gt 2 && $count -lt 1) ]];
then
    echo "Wrong number of arguments"
    exit -1
fi

# "make" command
if [[ ($count -eq 1 && $1 == "make") ]];
then
    cd PP/
    make
    cd ..
    cd CP/
    make
    cd ..
# "make run" command    
elif [[ ($count -eq 2 && $1 == "make" && $2 == "run") ]]
then    
    cd CP/
    make
    cd ..
    cd PP/
    make run
    cd ..
# "make clean" command    
elif [[ ($count -eq 2 && $1 == "make" && $2 == "clean") ]]
then
    cd PP/
    make clean 
    cd ..  
    cd CP/
    make clean
    cd ..  
	
# "make valgrind" command    
elif [[ ($count -eq 2 && $1 == "make" && $2 == "valgrind") ]]
then    
    cd CP/
    make
    cd ..
    cd PP/
    make valgrind 
    cd ..    
else
    echo "Invalid arguments"    
fi

