program: program.o diamond.o
	g++ -0 program program.o diamond.o

program.o: program.o diamond.h
	g++ -c -03 -Wall -std=c++11 program.cpp

diamond.o: diamond.cpp diamond.h
	g++ -c -03 -Wall -std=c++11 diamond.cpp

clean:
	rm *.o program
