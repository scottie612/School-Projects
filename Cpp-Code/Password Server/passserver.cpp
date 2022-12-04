//
// Created by Scottie on 4/11/2020.
//
#include "passserver.h"
#include "hashtable.hpp"

#include <stdio.h>
#include <crypt.h>

using namespace cop4530;
using namespace std;

PassServer::PassServer(size_t size) {
    passhash = new HashTable<string, string>(size);// creates a hashtable of string keys and string value of size size
}

PassServer::~PassServer() {
    passhash->clear();      //clears the hash table
}

bool PassServer::load(const char *filename) {
    return passhash->load(filename);            //loads the file into the hashtable
}

bool PassServer::addUser(std::pair<std::string, std::string> &kv) { // adds a user to the list
    auto newpw = std::make_pair(kv.first, encrypt(kv.second));      // encrypts the password and adds it to the hashtable
    return passhash->insert(newpw);
}

bool PassServer::addUser(std::pair<std::string, std::string> &&kv) {
    auto newpw = std::make_pair(std::move(kv.first), std::move(encrypt(kv.second)));// same as above but move version
    return passhash->insert(newpw);
}

bool PassServer::removeUser(const std::string &k) {                                 //calls the remove function on the username k
    return passhash->remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword) {
    if (!passhash->contains(p.first))                           //if the usernames are not the same return false
        return false;
    if (p.second == newpassword)                                 //if the new password and the old password are the same return false
        return false;
    if (passhash->match(std::make_pair(p.first, encrypt(p.second)))) {      //if the username and the password are matched in the hashtable,
        auto newpair = std::make_pair(p.first, encrypt(newpassword));       //create a new pair with the new password encrypted
        if (!passhash->match(newpair))                                      // if the new pair is not a match in the hashtable return true and insert the new pair if the insert returns true
            return passhash->insert(newpair);
    }
}

bool PassServer::find(const std::string &user) {
    return passhash->contains(user);                // see if the hash table contains the username
}

void PassServer::dump() {
    passhash->dump();                   //dump the hash aka print it
}

size_t PassServer::size() {             // return the size of the hashtable
    return passhash->GetSize();
}

bool PassServer::write_to_file(const char *filename) {
    return passhash->write_to_file(filename);           //calls the write to file fucntion of the hash table class
}


std::string PassServer::encrypt(const std::string &str) {

    char salt[] = "$1$########";
    string retval=crypt(str.c_str(),salt);
    return retval;
}
