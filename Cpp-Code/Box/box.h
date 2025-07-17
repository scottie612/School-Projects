
using namespace std;
#include <ostream>
#include "const.h"  
// ************************************************************
// ************************************************************
// *  Box Class:                                              *
// *                                                          *
// *  Description:  A class that provides the capability to   *
// *    draw a box of varying size to standard output.  The   *
// *    box will have a border and fill character and be      *
// *    restricted to certain sizes as specified by the       *
// *    constants MINIMUMSIZE and MAXIMUMSIZE.   Boxes        *
// *    of sizes 1 and 2 have no fill characters.             *
// *                                                          *
// ************************************************************
// ************************************************************
//
// ************************************************************
// * Constant Definitions.                                    *
// ************************************************************


class Box
{

public:

    
  Box (const int boxsize=1, const char borderchar=DEFAULTBORDER,
       const char fillchar=DEFAULTFILL);
  ~Box(); 
  friend ostream & operator << ( ostream & cout, const Box & MyBox);
  friend const Box operator + ( const Box & B1,
				const Box & B2);
  friend bool operator == ( Box & B1,
			    Box & B2);
  Box operator++();
  Box operator++(int); 
  
  void Draw();
  void Shrink();
  void Grow();
  int GetSize();
  char GetBorder();
  char GetFill(); 
  int Perimeter();
  int Area();
  void SetBorder(const char borderchar);
  void SetFill(const char fillchar);
  void SetSize(const int boxsize);
  void Summary();

private:
 
  char fill;
  char border;
  int size;
}; 
  
