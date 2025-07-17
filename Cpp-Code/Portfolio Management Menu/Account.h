//
// Created by Scottie on 4/14/2019.
//

#ifndef UNTITLED1_ACCOUNT_H
#define UNTITLED1_ACCOUNT_H

#include <cstring>
#include <cctype>
#include <fstream>                                                                                           //library importations
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;
class ETF
{
public:
    ETF();
    ETF(double x, double y, double z, double h);
    double getA();
    double getIVS();
    double getCVS();
    double getI();
    double getDIV();
    double getCV();


private:
    double CV,DIV;
    double A, IVS, CVS, I;

protected:
};

class Account
{
public:
    Account();
    virtual ~Account();
    void setfirst(char*x);
    void setlast(char*y);
    void setaccounttype(char*z);
    const char* getfirst() const;
    const char* getlast() const;
    const char* getaccounttype() const;
    virtual double GetProjected()=0;
    virtual double GetInitial()=0;

protected:
    char first[20];
    char last [20];
    char account_type[20];
};





class Savings: public Account
{
public:
    Savings(double current_balance, double interest_rate);
    double GetProjected();
    double GetInitial();
private:
    double currentbalance;
    double interestrate;
protected:
};

class Checking: public Account
{
public:
    Checking(double current_balance);
    double GetProjected();
    double GetInitial();
private:
    double currentbalance;
protected:
};


class Investment: public Account
{
public:
    Investment(ETF one,ETF two, ETF three,ETF four, ETF five);
    ~Investment();
    double GetProjected();
    double GetInitial();
private:
    ETF efts[5];
protected:
};



class Portfolio
{
public:
    Portfolio();
    ~Portfolio();
    bool importFile(const char*filename);
    bool createReportFile(const char* filename);
    void showAccounts()const;
    //void Sort(Account * a[], int size);

    Account** GetList();
    int GetSize();
private:
    int size=0;
    Account ** accts;
};



#endif //UNTITLED1_ACCOUNT_H
