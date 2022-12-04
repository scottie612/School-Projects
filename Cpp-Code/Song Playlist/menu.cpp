#include <iostream>
#include <cctype>
#include <cstring>
#include "Playlist.cpp"




using namespace std;


void ShowMenu()
{
cout<<"\n\nA:\tAdd a song to the playlist";
cout<<"\nF:\tFind a song in the playlist";
cout<<"\nR:\tRename playlist";
cout<<"\nS:\tRemove a song";
cout<<"\nD:\tDisplay the playlist";
cout<<"\nG:\tGenre summary";
cout<<"\nM:\tShow this Menu";
cout<<"\nQ:\tQuit/exit the program";


}

char GetaChar(const char* promptstring)
{
    char response;
    cout<<promptstring;
    cin>>response;
    response = toupper(response);
    cin.get();
    return response;
}
bool Legal(char c)
{
    return((c=='A')||(c=='F')||(c=='R')||(c=='S')||(c=='D')||(c=='G')||(c=='M')||(c=='Q'));

}
char GetCommand()
{
    char cmd= GetaChar("\n");
    while(!Legal(cmd))
    {
        cout<<"\nIllegal Command, please try again..";
        ShowMenu();
        cmd=GetaChar("\n");
    }
    return cmd;
}

void Soption()
{


}



int main()
{   char command;
    char temptitle[40],tempartist[20];
    char tempgenre;
    int tempduration;
    Playlist one;

cout<<"*** Welcome to Spotify-ish ***"<<endl;
cout<<"Please input the name for your playlist: ";
cin.getline(one.nameofplaylist,20);
one.ShowName();
ShowMenu();

do{
    command=GetCommand();
    switch(command)
    {
        case'A':
        {   cout<<"\nEnter Title"<<endl;
            cin.getline(temptitle,40);
            cout<<"<"<<temptitle<<">"<<endl;
            cout<<"\nEnter Author"<<endl;
            cin.getline(tempartist,20);
            cout<<"<"<<tempartist<<">"<<endl;
            cout<<"\nEnter Genre- (C)ountry, (E)DM, (P)op, (R)ock, or (B)R&B: "<<endl;
            cin>>tempgenre;
            tempgenre=toupper(tempgenre);
            cout<<"<"<<tempgenre<<">"<<endl;
            cout<<"\nEnter the duration of the song (in seconds):"<<endl;
            cin>>tempduration;
            cout<<"<"<<tempduration<<">"<<endl;
            one.Add(temptitle,tempartist,tempgenre,tempduration);
            break;
        }
        case'F':
        {
            char search[40];
            cout<<"Please enter the title/artist to search: ";
            cin.getline(search,40);
            one.Find(search);
            break;
        };
        case'R':
        {
            cout<<"Please input the name for your playlist: ";
            cin.getline(one.nameofplaylist,20);
            one.ShowName();
            cout<<"\n";
            break;
        };
        case'S':
        {
            int index;
            cout<<"Please enter the index you want to remove: ";
            cin>>index;
            one.Remove(index);
        };
        case'D':one.DisplayPlaylist();break;
        case'G':
        {
            cout<<"\nEnter Genre- (C)ountry, (E)DM, (P)op, (R)ock, or (B)R&B: "<<endl;
            cin>>tempgenre;
            tempgenre=toupper(tempgenre);
            one.gDisplay(tempgenre);
            break;

        };
        case'M': ShowMenu();break;
        case'Q':  break;
    }
}while(command!='Q');

    return 0;
}
