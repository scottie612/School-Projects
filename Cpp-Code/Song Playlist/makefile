menu: menu.o Playlist.o Song.o
	g++ -o menu  menu.o Playlist.o Song.o

menu.o: menu.cpp Playlist.h
	g++ -c -03 -Wall -std=c++11 menu.cpp

Playlist.o: Playlist.cpp Playlist.h
	g++ -c -03 -Wall -std=c++11 Playlist.cpp

Song.o: Song.cpp Song.h
	g++ -c -03 -Wall -std=c++11 Song.cpp

clean:
	rm *.o main
