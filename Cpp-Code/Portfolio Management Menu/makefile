Account: Account.o main.o
	g++ -o Account Account.o main.o

Account.o: Account.cpp Account.h
	g++ -c -std=c++11 Account.cpp

main.o: main.cpp Account.h
	g++ -c -std=c++11 main.cpp

clean:
	rm -f *.o Account
