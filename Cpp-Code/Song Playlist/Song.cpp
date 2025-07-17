//
// Created by Scottie on 3/13/2019.
//
#include<iostream>
#include <cstring>
#include <iomanip>
#include "Song.h"

using namespace std;
Song::Song()
{

}
void Song::set(const char* t, const char* a, Genre g, int d)
{

type=g;
duration=d;

for(int i=0;i<41;i++)
    {
         title[i]=t[i];
    }

for(int i=0;i<26;i++)
    {
        artist[i]=a[i];
    }


}

// the set function should allow incoming data to be received through
// parameters and loaded into the member data of the object (i.e., this
// function "sets" the state of the object to the data passed in).
// The parameters t, a, g, and d represent the title, artist, genre,
// and duration of the song, respectively.

const char* Song::getTitle() const// returns the title stored in the object
{
    return title;
}
const char* Song::getArtist() const  	// returns the artist
{
    return artist;
}

int Song::getDuration() const		    // returns the duration
{
    return duration;
}
Genre Song::getGenre() const
{
return type;
}
void Song::display() const
{

    cout<<"\n"<<left<<setw(40)<<getTitle()<<setw(25)<<getArtist()<<"\t";
    switch(getGenre())
    {
        case 0: cout<<"Country"; break;
        case 1: cout<<"EDM"; break;
        case 2: cout<<"Pop"; break;
        case 3: cout<<"Rock"; break;
        case 4: cout<<"RB"; break;
    }
    cout<<"\t"<<getDuration();
}
