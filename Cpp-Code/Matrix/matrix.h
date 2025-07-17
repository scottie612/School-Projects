//
// Created by Scottie on 3/27/2019.
//

#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
friend ostream& operator<<(ostream& o, const Matrix& m);

public:
    Matrix(unsigned int row=5, unsigned int column=5, unsigned int value=0);
    Matrix(const Matrix &other);
    ~Matrix();
    unsigned int numofrows()const;
    unsigned int numofcolums()const;
    int get(unsigned int r, unsigned int c);
    bool set(unsigned int r, unsigned int c, unsigned int v);
    Matrix operator+ (const Matrix& other);
    Matrix operator* (const Matrix& other);
    void torowmajor();
    void tocolumnmajor();
    void printinternal();
    Matrix transpose();
    Matrix submatrix(unsigned int startrow, unsigned
    int endrow, unsigned int startcol, unsigned int endcol);

private:
    int *numsofmatrix;
    unsigned int row;
    unsigned int column;
    unsigned int value;
    unsigned int sizeofarray;
    int rowmajored_;
};


#endif //UNTITLED_MATRIX_H
