//
// Created by Scottie on 3/1/2019.
//


#ifndef UNTITLED14_BIGINT_H
#define UNTITLED14_BIGINT_H

#include <iostream>

using namespace std;


class bigint
{
    friend ostream& operator << (ostream &output, bigint number);
    friend istream& operator >> (istream &input, bigint number);
    friend bigint operator+(const bigint &number,const bigint &number1);
    friend bigint operator-(const bigint &number,const bigint &number1);
    friend bool operator ==(const bigint &num1, const bigint& num2);
    friend bool operator !=(const bigint &num1, const bigint& num2);
    friend bool operator <(const bigint &num1, const bigint& num2);
    friend bool operator >(const bigint &num1, const bigint& num2);
    friend bool operator <=(const bigint &num1, const bigint& num2);
    friend bool operator >=(const bigint &num1, const bigint& num2);
public:
    bigint(int x0, int x1, int x2, int x3, int x4);
    bigint(int x0, int x1, int x2, int x3);
    bigint(int x0, int x1, int x2);
    bigint(int x0, int x1);
    bigint(int x0);
    bigint();

private:
     int array[5];


};

#endif //UNTITLED15_BIGINT_H
