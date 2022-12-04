#include <iostream>
#include <string>
#include "passserver.h"

using namespace std;


void Menu() {
    cout <<"\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - Hashtable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit Program" << endl;
    cout << "\nEnter Choice : ";
}

int main() {
    char input = ' ';
    size_t capacity;
    cout << "Enter preferred hash table capacity: ";
    cin >> capacity;
    PassServer x(capacity);
    do {
        string username = "";
        string password = "";
        string newpassword = "";
        string file;
        Menu();
        cin >> input;
        if (input == 'l') {
            cout << "Enter the File to be loaded in: ";
            cin.ignore();
            getline(cin, file);
            if (x.load(file.c_str())) {
                x.load(file.c_str());
                cout << "File " << file << " loaded\n";
            } else {
                cout << "File " << file << " not loaded in\n";
            }

        } else if (input == 'a') {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            auto user = make_pair(username, password);
            if (!x.addUser(user)) {
                cout << "ERROR could not add user\n";
            } else {
                x.addUser(user);
                cout << "User " << username << " added.\n";
            }
        } else if (input == 'r') {
            cout << "Enter username: ";
            cin >> username;
            if (!x.removeUser(username)) {
                cout << "Error could not delete user\n";

            } else {
                x.removeUser(username);
                cout << "User " << username << " deleted.\n";
            }
        } else if (input == 'c') {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter new password: ";
            cin >> newpassword;
            auto user = make_pair(username, password);
            if (!x.changePassword(user, newpassword)) {
                cout << "Error could not change user password\n";

            } else {
                x.changePassword(user, newpassword);
                cout << "Password Changed for user" << username << "\n";
            }
        } else if (input == 'f') {
            cout << "Enter username: ";
            cin >> username;
            if (!x.find(username))
                cout << "User '" << username << "' not found.\n";

            else {
                cout << "User '" << username << "' found.\n";
            }
        } else if (input == 'd') {
            x.dump();
        } else if (input == 's') {
            cout << "Size of hashtable: " << x.size() << endl;
        } else if (input == 'w') {
            cout << "Enter password file to write to: ";
            cin.ignore();
            getline(cin, file);
            if (!x.write_to_file(file.c_str())) {
                cout << "File not saved" << endl;

            } else {
                cout << "File Saved" << endl;
                x.write_to_file(file.c_str());
            }

        } else {
            cout << "Incorrect input Try again" << endl;
        }
    } while (input != 'x');

    return 0;
}