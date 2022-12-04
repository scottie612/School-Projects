//
//Scottie Jacobs, saj17, COP 3330 section 6
//

#ifndef UNTITLED10_DIAMOND_H
#define UNTITLED10_DIAMOND_H

class Diamond
{
private:
    int size;
    char border, fill;
public:

 Diamond( int , char = '#' , char = '*');




int GetSize();
int Perimeter();
double Area();
bool Grow();
bool Shrink();
bool SetBorder(char);
bool SetFill(char);
void Summary();
void Draw();




};

#endif //UNTITLED10_DIAMOND_H
