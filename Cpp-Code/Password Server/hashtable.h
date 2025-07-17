//
// Created by Scottie on 4/10/2020.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include<list>
#include <iostream>

namespace cop4530 {

    template<typename K, typename V>
    class HashTable {
    public:
        HashTable(size_t size = 101);

        ~HashTable();

        bool contains(const K &k);

        bool match(const std::pair<K, V> &kv);

        bool insert(const std::pair<K, V> &kv);

        bool insert(std::pair<K, V> &&kv);

        bool remove(const K &k);

        void clear();

        bool load(const char *filename);

        void dump();

        bool write_to_file(const char *filename);

        // max_prime is used by the helpful functions provided
        // to you.
        static const unsigned int max_prime = 1301081;
        // the default_capacity is used if the initial capacity
        // of the underlying vector of the hash table is zero.
        static const unsigned int default_capacity = 11;

        size_t GetSize();

    private:
        void makeEmpty();

        void rehash();

        size_t myhash(const K &k);

        unsigned long prime_below(unsigned long n);

        void setPrimes(std::vector<unsigned long> &vprimes);

        size_t thesize;                                     // number of elements in the table

        std::vector<std::list<std::pair<K, V>>> table;  // vector of list of pairs
    };
}

#endif
