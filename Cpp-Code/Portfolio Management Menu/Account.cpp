//
// Created by Scottie on 4/14/2019.
//


#include <cstring>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cctype>
#include "Account.h"

using namespace std;

void Account::setfirst(char *x)
{
    strncpy(first,x,20);
}
void Account::setlast(char *y)
{
    strncpy(last,y,20);
}
void Account::setaccounttype(char *z)
{
    strncpy(account_type,z,20);
}
const char* Account::getfirst() const
{
    return first;
}
const char* Account::getlast() const
{
    return last;
}
const char* Account::getaccounttype() const
{
    return account_type;
}


Account::Account()
{
}

Account::~Account()
{
}






Savings::Savings(double current_balance, double interest_rate)
{
    currentbalance=current_balance;
    interestrate=interest_rate;
}
double Savings::GetProjected()
{
    return(currentbalance*(1+interestrate));
}
double Savings::GetInitial()
{
    return currentbalance;
}

Checking::Checking(double current_balance)
{
    currentbalance=current_balance;
}
double Checking::GetProjected()
{
    return(currentbalance+.1);
}
double Checking::GetInitial()
{
    return currentbalance;
}
ETF::ETF()
{

}

ETF::ETF(double x,double y,double z, double h)
{
    A=x;
    IVS=y;
    CVS=z;
    I=h;
    DIV=(I*A);
    CV=(A/IVS)*CVS;
}


double ETF::getA()
{
    return A;
}
double ETF::getIVS()
{
    return IVS;
}
double ETF ::getCVS()
{
    return this->CVS;
}
double ETF::getI()
{
    return this->I;

}
double ETF::getCV()
{
    CV=(A/IVS)*CVS;
    return CV;
}
double ETF::getDIV()
{
    DIV=I*A;
    return this->DIV;
}


Investment::Investment(ETF a,ETF b, ETF c,ETF d, ETF e)
{
    efts[0]=a;
    efts[1]=b;
    efts[2]=c;
    efts[3]=d;
    efts[4]=e;
}
Investment::~Investment()
{

}
double Investment::GetProjected()
{
    double totaldiv=0;
    double totalCV=0;
    for(int i=0;i<5;i++)
    {
        totaldiv=totaldiv+efts[i].getDIV();
        totalCV=totalCV+efts[i].getCV();
    }
    return (totaldiv + totalCV);
}
double Investment::GetInitial()
{
    double Initial=(efts[0].getA()+efts[1].getA()+efts[2].getA()+efts[3].getA()+efts[4].getA());

    return  Initial;
}


Portfolio::Portfolio()
{

}

Portfolio::~Portfolio()
{
   if(accts!=nullptr)
   {
       for(int i=0;i<size;i++)
       {
           delete accts[i];
           accts[i]=nullptr;
       }
       delete[]accts;
       accts=nullptr;
   }
}
bool Portfolio::importFile(const char *filename)
{
    int currentsize;
    double i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23;

    ifstream fin;
    fin.open(filename);
    if(!fin)
    {
        cout << "Invalid file. No data imported\n" <<endl;
        return false;
    }
    else
    {

        if(accts!=nullptr)
        {
            fin>>currentsize;
            fin.ignore();
            int old=size;
            int newsize=old+currentsize;
            Account** temp=new Account*[newsize];
            for(int i=0;i<old;i++)
                temp[i]=accts[i];
            accts=temp;
            size=newsize;
            for (int i = old; i < newsize; i++) {
                char x[20], y[20], z[20];
                fin.getline(x, 20, ',');
                fin.ignore();
                fin.getline(y, 20);
                fin.getline(z, 20, ' ');
                if (strcmp(z, "Savings") == 0) {
                    fin >> i1 >> i2;
                    accts[i] = new Savings(i1, i2);
                    accts[i]->setfirst(y);
                    accts[i]->setlast(x);
                    accts[i]->setaccounttype(z);
                }
                if (strcmp(z, "Checking") == 0) {
                    fin >> i3;
                    accts[i] = new Checking(i3);
                    accts[i]->setfirst(y);
                    accts[i]->setlast(x);
                    accts[i]->setaccounttype(z);
                }
                if (strcmp(z, "Investment") == 0) {
                    fin >> i4 >> i5 >> i6 >> i7;
                    ETF one(i4, i5, i6, i7);
                    fin >> i8 >> i9 >> i10 >> i11;
                    ETF two(i8, i9, i10, i11);
                    fin >> i12 >> i13 >> i14 >> i15;
                    ETF three(i12, i13, i14, i15);
                    fin >> i16 >> i17 >> i18 >> i19;
                    ETF four(i16, i17, i18, i19);
                    fin >> i20 >> i21 >> i22 >> i23;
                    ETF five(i20, i21, i22, i23);
                    accts[i] = new Investment(one, two, three, four, five);
                    accts[i]->setfirst(y);
                    accts[i]->setlast(x);
                    accts[i]->setaccounttype(z);
                }
                fin.ignore();
            }
            fin.close();
            return true;
        }
        else{
            fin >> size;
            fin.ignore();
            accts = new Account *[size];
            for (int i = 0; i < size; i++) {
                char x[20], y[20], z[20];
                fin.getline(x, 20, ',');
                fin.ignore();
                fin.getline(y, 20);
                fin.getline(z, 20, ' ');
                if (strcmp(z, "Savings") == 0) {
                    fin >> i1 >> i2;
                    accts[i] = new Savings(i1, i2);
                    accts[i]->setfirst(y);
                    accts[i]->setlast(x);
                    accts[i]->setaccounttype(z);
                }
                if (strcmp(z, "Checking") == 0) {
                    fin >> i3;
                    accts[i] = new Checking(i3);
                    accts[i]->setfirst(y);
                    accts[i]->setlast(x);
                    accts[i]->setaccounttype(z);
                }
                if (strcmp(z, "Investment") == 0) {
                    fin >> i16 >> i17 >> i18 >> i19;
                    ETF four(i16, i17, i18, i19);
                    fin >> i20 >> i21 >> i22 >> i23;
                    fin >> i4 >> i5 >> i6 >> i7;
                    ETF one(i4, i5, i6, i7);
                    fin >> i8 >> i9 >> i10 >> i11;
                    ETF two(i8, i9, i10, i11);
                    fin >> i12 >> i13 >> i14 >> i15;
                    ETF three(i12, i13, i14, i15);
                    ETF five(i20, i21, i22, i23);
                    accts[i] = new Investment(one, two, three, four, five);
                    accts[i]->setfirst(y);
                    accts[i]->setlast(x);
                    accts[i]->setaccounttype(z);
                }
                fin.ignore();
            }
            fin.close();
            return true;
        }

    }
}
bool Portfolio::createReportFile(const char* filename)
{
    ofstream fout;
    fout.clear();
    fout.open(filename);
    if(!fout)
    {
        cout << "Invalid file. No data Exported\n" <<endl;
        return false;
    }
    else {
        fout.setf(ios::right);
        fout << fixed;
        fout << setprecision(2);

        fout << "Banking Summary" << endl;
        fout << "---------------------\n\n" << endl;
        fout << "Savings Accounts\n\n";
        fout << setprecision(2) << showpoint << fixed;
        fout << setw(41) << left << "Holders Name" << setw(18) << right << "Initial Balance" << setw(20) << right<< "Projected Balance\n" << endl;
        fout << "-------------------------------------------------------------------------------\n";
        for (int i = 0; i < size; i++) {
            if (strcmp(accts[i]->getaccounttype(), "Savings") == 0) {
                fout << setw(strlen(accts[i]->getfirst())) << left << accts[i]->getfirst();
                fout<<" ";
                fout << setw(strlen(accts[i]->getlast()))  << left << accts[i]->getlast();
                fout<<setw(58-(strlen(accts[i]->getlast())+strlen(accts[i]->getfirst())))<< right << accts[i]->GetInitial() << setw(20)<<right << accts[i]->GetProjected()<< endl;
            }
        }
        fout << "\n\n";

        fout << "Checking Accounts\n\n";
        fout << setprecision(2) << showpoint << fixed;
        fout << setw(41) << left << "Holders Name" << setw(18) << right << "Initial Balance" << setw(20) << right<< "Projected Balance\n" << endl;
        fout << "-------------------------------------------------------------------------------\n";
        for (int i = 0; i < size; i++) {
            if (strcmp(accts[i]->getaccounttype(), "Checking") == 0) {
                fout << setw(strlen(accts[i]->getfirst())) << left << accts[i]->getfirst();
                fout<<" ";
                fout << setw(strlen(accts[i]->getlast()))  << left << accts[i]->getlast();
                fout<<setw(58-(strlen(accts[i]->getlast())+strlen(accts[i]->getfirst())))<< right << accts[i]->GetInitial() << setw(20)<<right << accts[i]->GetProjected()<< endl;
            }
        }
        fout << "\n\n";

        fout << "Investment Accounts\n\n";
        fout << setprecision(2) << showpoint << fixed;
        fout << setw(41) << left << "Holders Name" << setw(18) << right << "Initial Balance" << setw(20) << right<< "Projected Balance\n" << endl;
        fout << "-------------------------------------------------------------------------------\n";
        for (int i = 0; i < size; i++) {
            if (strcmp(accts[i]->getaccounttype(), "Investment") == 0) {
                fout << setw(strlen(accts[i]->getfirst())) << left << accts[i]->getfirst();
                fout<<" ";
                fout << setw(strlen(accts[i]->getlast()))  << left << accts[i]->getlast();
                fout<<setw(58-(strlen(accts[i]->getlast())+strlen(accts[i]->getfirst())))<< right << accts[i]->GetInitial() << setw(20)<<right << accts[i]->GetProjected()<< endl;
            }
        }
        fout << "\n\n";

        fout << "Overall Account distribution\n\n";
        int savingscount = 0, checkingcount = 0, investmentcount = 0;
        double savingssum = 0, checkingsum = 0, investmentsum = 0;
        for (int i = 0; i < size; i++) {
            if (strcmp(accts[i]->getaccounttype(), "Savings") == 0) {
                savingscount++;
                savingssum = savingssum + accts[i]->GetProjected();
            }
            if (strcmp(accts[i]->getaccounttype(), "Checking") == 0) {
                checkingcount++;
                checkingsum = checkingsum + accts[i]->GetProjected();
            }

            if (strcmp(accts[i]->getaccounttype(), "Investment") == 0) {
                investmentcount++;
                investmentsum = investmentsum + accts[i]->GetProjected();
            }
        }
        double savingsaverage = savingssum / savingscount;
        double checkingaverage = checkingsum / checkingcount;
        double investmentaverage = investmentsum / investmentcount;
        fout << setw(20) << left << "Savings:" << setw(10) << left << savingscount <<"-"<< setw(10) << right << fixed
             << showpoint << setprecision(2) << savingsaverage << endl;
        fout << setw(20) << left << "Checking:" << setw(10) << left << checkingcount <<"-"<< setw(10) << right << fixed
             << showpoint << setprecision(2) << checkingaverage << endl;
        fout << setw(20) << left << "Investment:" << setw(10) << left << investmentcount <<"-" <<setw(10) << right << fixed
             << showpoint << setprecision(2) << investmentaverage << endl;
        fout.close();
        return true;
    }
}

void Portfolio::showAccounts()const
{
    cout<<setprecision(2)<<showpoint<<fixed;
    cout<<setw(44)<<left<<"Holder"<<setw(12)<<left<<"Type"<<setw(12)<<left<<"Balance\n"<<endl;
    for(int i=0;i<size;i++)
    {
        cout<<setw(22)<<left<<accts[i]->getlast()<<setw(22)<<left<<accts[i]->getfirst();
        cout<<setw(12)<< left <<accts[i]->getaccounttype();
        cout<<setw(12)<<right<<accts[i]->GetInitial()<<endl;
    }
}

Account** Portfolio::GetList()
{
    return accts;
}
int Portfolio::GetSize()
{
    return size;
}


//void Portfolio::Sort(Account * a[],const int size)
//{
//
//
//}