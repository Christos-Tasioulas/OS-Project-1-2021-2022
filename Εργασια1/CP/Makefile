# sample Makefile that you can quickly adapt to your needs
# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11 -pthread -lpthread -lrt

# set the name of the executable file to compile here
program=child

# list object files needed to compile the program
objects=main.o SHM_Structure.o Solution.o

# arguments to run the program
args = 

# this makes the program. It's the first rule so it will be executed if you give just 'make'
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program)

# list .h dependencies for each .o (dependency on .c is automatically set by make!)
main.o : Interface.h
SHM_Structure.o : SHM_Structure.h
Solution.o : Interface.h

# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects)

# run the program with 'make run'. Sometimes useful to avoid rewriting long commands.
run: $(program)
	./$(program) $(args)	

valgrind: $(program)
	valgrind --track-origins=yes --trace-children=yes ./$(program) $(args)