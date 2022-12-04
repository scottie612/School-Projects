//
// Created by Scottie on 3/1/2019.
////

#include <iostream>
#include <iomanip>
#include <string>
#include "bigint.h"

using namespace std;


ostream& operator << (ostream &output, bigint number)
    {

        output<<number.array[4];//outputs the largest place value
        for(int i=3;i>=0;i--)//outputs the lesser place values with padding zeros
        {
            if(number.array[i]!= 0)
                output << setfill('0') << setw(9) << number.array[i];
        }
return output;
}
istream& operator >> (istream &input, bigint number)
{
char temp[45];

    cin.getline(temp,45,'\n');

   number.array[0]=100000000*temp[0]+10000000*temp[1]+1000000*temp[2]+100000*temp[3]+10000*temp[4]+1000*temp[5]+100*temp[6]+10*temp[7]+temp[8];
   number.array[1]=100000000*temp[9]+10000000*temp[10]+1000000*temp[11]+100000*temp[12]+10000*temp[13]+1000*temp[14]+100*temp[15]+10*temp[16]+temp[17];
   number.array[2]=100000000*temp[18]+10000000*temp[19]+1000000*temp[20]+100000*temp[21]+10000*temp[22]+1000*temp[23]+100*temp[24]+10*temp[25]+temp[26];
   number.array[3]=100000000*temp[27]+10000000*temp[28]+1000000*temp[29]+100000*temp[30]+10000*temp[31]+1000*temp[32]+100*temp[33]+10*temp[34]+temp[35];
   number.array[4]=100000000*temp[36]+10000000*temp[37]+1000000*temp[38]+100000*temp[39]+10000*temp[40]+1000*temp[41]+100*temp[42]+10*temp[43]+temp[44];
input >> number.array[0]>>number.array[1]>>number.array[2]>>number.array[3]>>number.array[4];
    return input;
}



bool operator==(const bigint & num1, const bigint & num2)//checks to see if equal by checking each segment of the big int starting with the largest index
{
    if(num1.array[4]==num2.array[4])
    {
        if(num1.array[3]==num2.array[3])
        {
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[1]==num2.array[1])
                {
                    if(num1.array[0]==num2.array[0])
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false; 
};

bool operator!=(const bigint & num1, const bigint & num2)//same thing as equal to but changed true to false and false to true
{
    if(num1.array[4]==num2.array[4])
    {
        if(num1.array[3]==num2.array[3])
        {
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[1]==num2.array[1])
                {
                    if(num1.array[0]==num2.array[0])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
  
};

bool operator>(const bigint & num1, const bigint & num2)//checks each segment starting with the largest place value to check if greater than
{
    if(num1.array[0]>num2.array[0])
    {
        return true;
    }
    if(num1.array[0]==num2.array[0])
    {
        if(num1.array[1]>num2.array[1])
        {
            return true;
        }
        if(num1.array[1]==num2.array[1])
        {
            if(num1.array[2]>num2.array[2])
            {
                return true;
            }
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[3]>num2.array[3])
                {
                    return true;
                }
                if(num1.array[3]==num2.array[3])
                {
                    if(num1.array[4]>num2.array[4])
                    {
                        return true;
                    }
                }
            }
        }
    }

return false;
}
bool operator<(const bigint & num1, const bigint & num2)//same thing as greater than but signs are flipped
{
    if(num1.array[0]<num2.array[0])
    {
        return true;
    }
    if(num1.array[0]==num2.array[0])
    {
        if(num1.array[1]<num2.array[1])
        {
            return true;
        }
        if(num1.array[1]==num2.array[1])
        {
            if(num1.array[2]<num2.array[2])
            {
                return true;
            }
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[3]<num2.array[3])
                {
                    return true;
                }
                if(num1.array[3]==num2.array[3])
                {
                    if(num1.array[4]<num2.array[4])
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
bool operator<=(const bigint & num1, const bigint & num2)//combination of less than and equal to
{
    if(num1.array[0]<num2.array[0])
    {
        return true;
    }
    if(num1.array[0]==num2.array[0])
    {
        if(num1.array[1]<num2.array[1])
        {
            return true;
        }
        if(num1.array[1]==num2.array[1])
        {
            if(num1.array[2]<num2.array[2])
            {
                return true;
            }
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[3]<num2.array[3])
                {
                    return true;
                }
                if(num1.array[3]==num2.array[3])
                {
                    if(num1.array[4]<num2.array[4])
                    {
                        return true;
                    }
                }
            }
        }
    }
    if(num1.array[4]==num2.array[4])
    {
        if(num1.array[3]==num2.array[3])
        {
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[1]==num2.array[1])
                {
                    if(num1.array[0]==num2.array[0])
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
bool operator>=(const bigint & num1, const bigint & num2)//combination of greater than and equal to
{
    if(num1.array[0]>num2.array[0])
    {
        return true;
    }
    if(num1.array[0]==num2.array[0])
    {
        if(num1.array[1]>num2.array[1])
        {
            return true;
        }
        if(num1.array[1]==num2.array[1])
        {
            if(num1.array[2]>num2.array[2])
            {
                return true;
            }
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[3]>num2.array[3])
                {
                    return true;
                }
                if(num1.array[3]==num2.array[3])
                {
                    if(num1.array[4]>num2.array[4])
                    {
                        return true;
                    }
                }
            }
        }
    }
    if(num1.array[4]==num2.array[4])
    {
        if(num1.array[3]==num2.array[3])
        {
            if(num1.array[2]==num2.array[2])
            {
                if(num1.array[1]==num2.array[1])
                {
                    if(num1.array[0]==num2.array[0])
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}



bigint operator+(const bigint &number,const bigint &number1)//if the addition of the indexs is over the max value, increase the value after by 1 and, subtract the difference
{
    int spot0=number.array[0]+number1.array[0];
    int spot1=number.array[1]+number1.array[1];
    int spot2=number.array[2]+number1.array[2];
    int spot3=number.array[3]+number1.array[3];
    int spot4=number.array[4]+number1.array[4];
if((spot4>999999999))
    {
        spot4=999999999-spot4-1;
        spot3=spot3+1;
    }
if((spot3>999999999))
{
        spot3=999999999-spot3-1;
        spot2=spot2+1;
    }
if((spot2>999999999))
    {
        spot2=999999999-spot2-1;
        spot1=spot1+1;
    }
if((spot1>999999999))
    {
        spot1=999999999-spot1-1;
        spot0=spot0+1;
    }
if((spot0>999999999))
    {
        spot0=999999999-spot0-1;
    }

    return bigint(spot4,spot3,spot2,spot1,spot0);
}

bigint operator-(const bigint &number,const bigint &number1)
{
    if( number < number1)//if it is less then it is equal to zero
    {
        return bigint();
    }
    int spot0,spot1,spot2,spot3,spot4;
    spot4=number.array[4]-number1.array[4];
    if(number.array[3]<number1.array[3])
    {
        spot4=spot4-1;
        spot3=(number.array[3]+100000000)-number1.array[3];
    }
    if(number.array[2]<number1.array[2])
    {
        spot3=spot3-1;
        spot2=(number.array[2]+100000000)-number1.array[2];
    }
    if(number.array[1]<number1.array[1])
    {
        spot2=spot2-1;
        spot1=(number.array[1]+100000000)-number1.array[1];
    }
    if(number.array[0]<number1.array[0])
    {
        spot1=spot1-1;
        spot0=(number.array[0]+100000000)-number1.array[0];
    }
    return bigint(spot4,spot3,spot2,spot1,spot0);

}




bigint::bigint(int x0, int x1, int x2, int x3, int x4)
{
    array[4]=x0;
    array[3]=x1;
    array[2]=x2;
    array[1]=x3;
    array[0]=x4;
}

bigint::bigint(int x0, int x1, int x2, int x3)
{
    array[4]=x0;
    array[3]=x1;
    array[2]=x2;
    array[1]=x3;
    array[0]=0;
}
bigint::bigint(int x0, int x1, int x2)
{
    array[4]=x0;
    array[3]=x1;
    array[2]=x2;
    array[1]=0;
    array[0]=0;
}
bigint::bigint(int x0, int x1)
{
    array[4]=x0;
    array[3]=x1;
    array[2]=0;
    array[1]=0;
    array[0]=0;
}
bigint::bigint(int x0)
{
    array[4]=x0;
    array[3]=0;
    array[2]=0;
    array[1]=0;
    array[0]=0;

}
bigint::bigint()
{
    array[4]=000000000;
    array[3]=000000000;
    array[2]=000000000;
    array[1]=000000000;
    array[0]=000000000;

}
