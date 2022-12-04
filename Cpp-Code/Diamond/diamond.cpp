//Scottie Jacobs, saj17, COP 3330 section 6

#include <iostream>
#include <iomanip>
#include "diamond.h"
#include <cmath>


using namespace std;


Diamond::Diamond(int s ,char d ,char f)
{
    if(s<1)
    {
        size=1;
    }
    else if(s > 39)
    {
        size=39;
    }
    else
        size = s;
    border = d;
    fill =f;


}


int Diamond::GetSize()
{
 return size;
}


int Diamond::Perimeter()
{

return 4*size;
}


double Diamond::Area()
{

 return (2* (sqrt(3)/4)*(size*size));
}

bool Diamond::Grow()
{
    int temp1 = size;
    temp1 = temp1 +1;
    if(temp1<1)
    {
        return false;
    }
    if (temp1 > 39)
    {
        return false;
    }
    size = temp1;
    return true;
}


bool Diamond::Shrink()
{
    int temp2 = size;
    temp2 = temp2 -1;
    if(temp2<1)
    {
        return false;
    }
    if (temp2 > 39)
    {
        return false;
    }
    size = temp2;
    return true;
}


bool Diamond::SetBorder(char border1)
{
    if(border1<33)
    {
        return false;
    }
    if(border1>126)
    {
        return false;
    }
    border= border1;
    return true;
}


bool Diamond::SetFill(char fill1) {
    if (fill1 < 33) {
        return false;
    }
    if (fill1 > 126) {
        return false;
    }
    fill = fill1;
    return true;
}

void Diamond::Draw()
{
    int i, j, k;
    //Drawing upper half of the diamond
    for(i = 1; i <= size; i++)
    {
        for(j = i; j <= size; j++)
            cout<<" ";
        cout<<border<<" ";
        for(k = i - 2; k > 0; k--)
            cout<<fill<<" ";
        if(i != 1)
            cout<<border;
        cout<<"\n";
    }

    //Drawing lower half of the diamond
    for(i = size - 1; i >= 1; i--)
    {
        for(j = i; j <= size; j++)
            cout<<" ";
        cout<<border<<" ";
        for(k = 3; k <= i; k++)
            cout<<fill<<" ";
        if(i != 1)
            cout<<border;
        cout<<"\n";
    }
}


void Diamond::Summary()
{
cout << "Size of diamond's side = " << GetSize() <<" units."<<endl;
cout << "Perimeter of diamond's side = " << Perimeter()<<" units."<< endl;
cout << "Area of diamond = "<< Area() <<" units."<< endl;
cout << "Diamond looks like: "<< endl;
Draw();
}





