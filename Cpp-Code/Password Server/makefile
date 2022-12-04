proj5.x: proj5.cpp passserver.o
	g++ -std=c++11 -lcrypt proj5.cpp passserver.o -o proj5.x

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -std=c++11 -c passserver.cpp -lcrypt

clean:
	rm -f *.o*
