//
// Created by Scottie on 4/11/2020.
//

#ifndef UNTITLED9_PASSSERVER_H
#define UNTITLED9_PASSSERVER_H
#include "hashtable.h"
#include <iostream>
#include <string>


using namespace cop4530;
    class PassServer {
    public:

        PassServer(size_t size=101);

        ~PassServer();

        bool load(const char *filename);

        bool addUser(std::pair<std::string, std::string> &kv);

        bool addUser(std::pair<std::string, std::string> &&kv);

        bool removeUser(const std::string &k);

        bool changePassword(const std::pair <std::string, std::string> &p, const std::string &newpassword);

        bool find(const std::string &user);

        void dump();

        size_t size();

        bool write_to_file(const char *filename);

    private:
        std::string encrypt(const std::string &str);
        HashTable<std::string,std::string> * passhash;      //private hashtable
    };

#endif //UNTITLED9_PASSSERVER_H
