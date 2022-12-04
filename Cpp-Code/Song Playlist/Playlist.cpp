//
// Created by Scottie on 3/13/2019.
//

#include<iostream>
#include<iomanip>
#include <cstring>
#include "Playlist.h"
#include "Song.cpp"


using namespace std;
Playlist::Playlist()
{
currentsize=0;
maxsize=1;
songlist = new Song[maxsize];
}
Playlist::~Playlist()
{
delete []songlist;
}
//---------------------------------------------------------------------- Constructor/Deconstructor


void Playlist::Grow()
{
maxsize=currentsize+1;
Song* newplaylist = new Song[maxsize];
for(int i=0;i<currentsize;i++)
{
    newplaylist[i]=songlist[i];
}
delete [] songlist;
songlist=newplaylist;

cout<<"\n** Array being resized to "<<maxsize<<" allocated slots**\n";
}

void Playlist::Add(const char* t, const char* a, char genre, int d)
{
if(currentsize==maxsize)
    Grow();
Song newsong;
Genre g;
switch(genre)
{
    case'C': g=COUNTRY;break;
    case'E': g=EDM;break;
    case'P': g=POP;break;
    case'R': g=ROCK;break;
    case'B': g=RB;break;
}


newsong.set(t,a,g,d);

songlist[currentsize++]=newsong;
    numofsongs++;

}
void Playlist::Remove(int x)
{
int song=x;
    totalduration=totalduration-songlist[song].getDuration();
for(int j=song +1;j<currentsize;j++)
{
    songlist[j-1]=songlist[j];
}
currentsize--;
numofsongs--;

}

void Playlist::ShowName()
{
    cout<<nameofplaylist;
}

void Playlist::DisplayPlaylist()
{
    cout<<left<<setw(40)<<"Song"<<setw(25)<<"Artist"<<"\tGenre\t"<<"Duration"<<endl;
    cout<<"---------------------------------------------------------------------------------------";
    for(int i=0;i<=(currentsize-1);i++)
    {
        songlist[i].display();
        totalduration=totalduration + songlist[i].getDuration();
    }
    cout<<"\n\nNumber of Songs: "<< numofsongs;

    cout<<"\nTotal duration "<<totalduration;

}
void Playlist::gDisplay(char x)
{
    int gnumofsongs=0;
    int gduration=0;
    int g;
    switch(x)
    {
        case'C': g=COUNTRY;break;
        case'E': g=EDM;break;
        case'P': g=POP;break;
        case'R': g=ROCK;break;
        case'B': g=RB;break;
    }

    cout<<left<<setw(40)<<"Song"<<setw(25)<<"Artist"<<"\tGenre\t"<<"Duration"<<endl;
    cout<<"-------------------------------------------------------------------------------------------";
    for(int i=0;i<=(currentsize-1);i++)
    {
        if(songlist[i].getGenre()==g) {
            songlist[i].display();
            gduration = gduration + songlist[i].getDuration();
            gnumofsongs++;
        }
    }
    cout<<"\n\nNumber of Songs: "<< gnumofsongs;

    cout<<"\nTotal duration "<<gduration;

}
void Playlist::Find(char *x)
{int fnumofsongs=0;
    for(int i=0;i<=(currentsize-1);i++)
    {
        if(songlist[i].getArtist()==x||songlist[i].getTitle()==x)
        {
            fnumofsongs++;
        }
    }
    if(fnumofsongs==0)
        cout<<"No song found"<<endl;
    else{
        for(int i=0;i<=(currentsize-1);i++)
        {
            if(songlist[i].getArtist()==x||songlist[i].getTitle()==x)
            {
                songlist[i].display();
            }
        }

    }


 }
