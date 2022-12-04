//
// Created by Scottie on 3/27/2019.

#include<iostream>
#include "matrix.h"
using namespace std;

ostream& operator<<(ostream& o, const Matrix& m)
{

    int matrixindex=0;

            if(m.rowmajored_==1) {//output based if rowmajored

                for (int j = 0; j < m.row; j++) {
                    for (int i = 0; i < m.column; i++) {
                        o << m.numsofmatrix[matrixindex] << "\t";
                    matrixindex++;
                }
                o << endl;
                }
            }
            else {

                for (int j = 0; j < m.row; j++) {
                    for (int i = 0; i < m.column; i++) {

                        if(matrixindex==m.sizeofarray-1)//if the index is the last spot of the array, output the last spot in the array
                        {
                            o << m.numsofmatrix[matrixindex] << "\t";
                        } else{//output based if column majored
                            o << m.numsofmatrix[(matrixindex*m.row)%(m.sizeofarray-1)] << "\t";
                        }
                        matrixindex++;
                        }
                    o<<endl;
                }
            }
    return o;
}
 Matrix::Matrix(unsigned int r, unsigned int c, unsigned int v)
{
    value=v;
    row=r;
    column=c;
    rowmajored_=1;
    sizeofarray=(row*column);
    numsofmatrix = new int[sizeofarray];
    for(int fill=0;fill<=(sizeofarray-1);fill++)//set each value of the array to v
    {
        numsofmatrix[fill]=value;
    }
}
Matrix::Matrix(const Matrix &other)//copy constructor
{
        rowmajored_=other.rowmajored_;
        column = other.column;
        row = other.row;
        sizeofarray = (other.row * other.column);
        numsofmatrix=new int[sizeofarray-1];
        for (int i = 0; i <= (other.sizeofarray - 1); i++) {
            numsofmatrix[i] = other.numsofmatrix[i];
        }
}

Matrix::~Matrix()
{
 delete [] numsofmatrix;
}
unsigned int Matrix:: numofrows()const
{
    return row;
}
unsigned int Matrix:: numofcolums()const
{
    return column;
}
int Matrix::get(unsigned int r, unsigned int c)
{

    if(r<=row&&c<=column) {
        if(rowmajored_==1) {
            return (numsofmatrix[(column * (r - 1) + (c - 1))]);
        }
        if(rowmajored_==0) {
            return (numsofmatrix[(row * (c - 1) + (r - 1))]);
        }
    } else return -1;
}
bool Matrix::set(unsigned int r, unsigned int c, unsigned int value)
{
    if(r<=row&&c<=column)//checks to see if its in bounds
    {
        if(rowmajored_==1) {//if its rowmajored
            for (int j = 0; j < r; j++) {
                for (int i = 0; i < c; i++) {
                    numsofmatrix[(column * (r - 1) + (c - 1))] = value;
                }
            }
        }
        else{//if column majored
                for (int j = 0; j < c; j++) {
                    for (int i = 0; i < r; i++) {
                        numsofmatrix[(row * (c - 1) + (r - 1))] = value;
                    }
                }
        }
        return true;
    }
    else
        return false;
}
Matrix Matrix::operator+ (const Matrix& other)
{
    Matrix copy=other;
    copy.torowmajor();
    Matrix return1(row,column);
    if(row == copy.row && column == copy.column)
    {
        for(int i=0;i<sizeofarray;i++)
        {
            return1.numsofmatrix[i]=copy.numsofmatrix[i]+numsofmatrix[i];
        }
        return return1;
    } else
        {
            return return1;
        }

}
Matrix Matrix::operator* (const Matrix& other)
{       Matrix copy=other;
        copy.torowmajor();
        Matrix return2(row,copy.column);

        for (int i = 0; i <= row; i++) {
            for (int j = 0; j <= copy.column; j++) {
                int sum = 0;
                for (int k = 0; k <= copy.row; k++)
                    sum = sum + numsofmatrix[i * column + k] * copy.numsofmatrix[k * copy.column + j];
                return2.numsofmatrix[i * return2.column + j] = sum;
            }
        }
        return return2;
}
void Matrix::torowmajor()
{
    if(rowmajored_==0)
    {
        int* temp=new int[sizeofarray];
        for(int i=0; i<numofrows(); i++)
        {
            temp[0]=numsofmatrix[0];
            for(int j=1;j<sizeofarray;j++)
            {
                temp[j]=numsofmatrix[j*numofrows()%(sizeofarray-1)];
            }
            temp[sizeofarray-1]=numsofmatrix[sizeofarray-1];
        }

        delete []numsofmatrix;
        numsofmatrix=temp;
        rowmajored_=1;
    }

}
void Matrix::tocolumnmajor()
{
    if(rowmajored_==1)
    {
        int* temp=new int[sizeofarray];
        for(int i=0; i<numofcolums(); i++)
        {
            temp[0]=numsofmatrix[0];
            for(int j=1;j<sizeofarray;j++)
            {
                temp[j]=numsofmatrix[j*numofcolums()%(sizeofarray-1)];
            }
        }
        temp[sizeofarray-1]=numsofmatrix[sizeofarray-1];
        delete []numsofmatrix;
        numsofmatrix=temp;
        rowmajored_=0;
    }

}
void Matrix::printinternal()
{
    for(int i=0; i<sizeofarray;i++)
    {
        cout<<numsofmatrix[i]<<"\t";
    }
    cout<< endl;
}
Matrix Matrix::transpose()
{
    torowmajor();
    Matrix transposed(column,row);
    for(int i=0;i<sizeofarray;i++)
    {
        transposed.numsofmatrix[i]=numsofmatrix[i*numofcolums()%(sizeofarray-1)];
    }
    transposed.numsofmatrix[sizeofarray-1]=numsofmatrix[(sizeofarray-1)*numofcolums()%(sizeofarray)];
    return transposed;
}
Matrix Matrix::submatrix(unsigned int startrow, unsigned int endrow, unsigned int startcol, unsigned int endcol)
{
if(startrow>=1 && startcol>=1 && endcol<=column && endrow<=row && endrow>=startrow && endcol>=startcol)
{
    torowmajor();
  Matrix returnsub((endrow-startrow)+1,(endcol-startcol)+1);
    for(unsigned int i=0;i<returnsub.column;i++)
    {
        for(unsigned int j=0;j<returnsub.row;j++)
        {
            returnsub.set(j+1,i+1,unsigned(get(startrow+j,startcol+i)));
        }
    }

    return returnsub;
} else{
    Matrix returnbasic(row,column);
    return returnbasic;
}



}