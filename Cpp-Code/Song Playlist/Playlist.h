//
// Created by Scottie on 3/13/2019.
//

#ifndef UNTITLED16_PLAYLIST_H
#define UNTITLED16_PLAYLIST_H

#include "Song.h"



class Playlist{

public:
    Playlist();
    ~Playlist();
    void Add(const char* t, const char* a, char g, int d);
    void Remove(int x);
    void ShowName();
    void DisplayPlaylist();
    char nameofplaylist[20];
    void gDisplay(char x);
    void Find(char* search);
private:
    int currentsize;
    Song* songlist;
    void Grow();

    int totalduration=0;
    int numofsongs=0;
    int maxsize;


};








#endif //UNTITLED16_PLAYLIST_H
