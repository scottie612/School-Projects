#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cctype>
#include "Account.cpp"
 using namespace std;



void ShowMenu()
{
    cout << "*** Portfolio Management menu ***\n" << endl;
    cout << "I\tImport accounts from file"<< endl;
    cout << "S\tShow accounts (brief)" << endl;
    cout << "E\tExport a banking report (to file)" << endl;
    cout << "O\tSort the account list"<< endl;
    cout << "M\tShow this menu" << endl;
    cout << "Q\tQuit program\n" << endl;
}

int main() {

char ifile[80];
char ofile[80];
char selection;

ShowMenu();
    Portfolio main;
    do
    {
        cout<<">";
        cin>> selection;
        selection=toupper(selection);

        switch(selection)
        {
            case 'I':
            {
                cout << "Enter filename: ";
                cin >> ifile;
                main.importFile(ifile);
                break;
            }
            case 'S':
            {
                main.showAccounts();
                break;
            }
            case 'E':
            {
                cout << "Enter filename: ";
                cin >> ofile;
                main.createReportFile(ofile);
                break;
            }
            case 'O':
            {
                //main.Sort(main.GetList(),main.GetSize());
                break;
            }
            case 'M':
            {
                ShowMenu();
                break;
            }
            case 'Q':
            {
                break;
            }
            default:
            {
                cout<<"Invalid Selection, Please try again"<< endl;
                break;
            }
        }
    }while(selection !='Q');
    cout<<"\nGoodbye!"<<endl;
    return 0;
}
