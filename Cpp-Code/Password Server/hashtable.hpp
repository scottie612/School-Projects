//
// Created by Scottie on 4/10/2020.
//

#ifndef UNTITLED9_HASHTABLE_HPP
#define UNTITLED9_HASHTABLE_HPP

#include<vector>
#include <iostream>
#include "hashtable.h"
#include <fstream>
#include <sstream>


using namespace cop4530;

//public functions
template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size)                     //constructor
{
    if (size < 11) {                // if the size of the wanted hash table is less then 11 set it to default capacity
        size = default_capacity;
    }
    table.resize(prime_below(size));    //resize the vector to the size of the closet prime number below size
    thesize = 0;                        // number of elements in the hashtable
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {                             //destructor
    makeEmpty();                        // clears the hashtable
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K &k) {
    auto &templist = table[myhash(k)];      // get the list at the hashed key location
    for (auto key : templist) {             // for every pair in the list
        if (key.first == k)                 // if the key eqaual the parameter k, then the key is in the list
            return true;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) {
    auto &List = table[myhash(kv.first)];   // get the list at the hashed key location
    if (List.empty())                       // if the list is empty return false
        return false;
    for (auto &temp : List) {                // for every pair in the list
        if (temp.first == kv.first)          //if the key in the list equals the given parameter key continue
            if (temp.second == kv.second)   //if the value of the list and the parameter value are the same then return true
                return true;
    }
    return false;

}

template<typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> &kv) {
    auto &List = table[myhash(kv.first)];// get the list at the hashed key location
    if (List.empty()) {                     //if the list is empty
        List.push_back(kv);                 // add the pair to the list
    } else {
        for (auto &pair : List) {            // for every pair in the list
            if (pair.first == kv.first) {       //checks to make sure the pair is not being duplicated in the list
                if (pair.second == kv.second) {
                    return false;
                } else {                        //if the values are different update the pair
                    pair.second = kv.second;
                    break;
                }
            } else {
                List.push_back(kv);                 // add the pair to the list
                break;
            }
        }
    }
    thesize++;                                  //increase the number of elements
    if (thesize > table.size()) {               //if the number of elements is greater then the table size then rehash
        rehash();
    }
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> &&kv) {        //same as above but move version
    auto &List = table[myhash(kv.first)];
    if (List.empty()) {
        List.push_back(kv);
    } else {
        for (auto &pair : List) {
            if (pair.first == kv.first) {
                if (pair.second == kv.second) {
                    return false;
                } else {
                    pair.second = kv.second;
                    break;
                }
            } else {
                List.push_back(std::move(kv));
                break;
            }
        }
    }
    thesize = thesize + 1;
    if (thesize > table.size()) {
        rehash();
    }
    return true;
}


template<typename K, typename V>
bool HashTable<K, V>::remove(const K &k) {
    if(contains(k))                                 //if the key is in the table, keepgoing, otherwise return false;
    {
        auto & List = table[myhash(k)];             // make the list at the hashed iterators position
        for(auto i=List.begin();i!= List.end();i++) {   // loop through the list and if the key matches, erase it, and return true
            if (i->first == k) {
                List.erase(i);
                return true;
            }
        }
    }
    return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();                //clears the hashtable
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    std::ifstream inf;      // create an istream
    inf.open(filename);     //open the file
    if (inf.is_open()) {     // check to see if the file opened correctly
        while (!inf.eof()) {    // while its no the end of the file
            K key;              // input key,val as a pair to the table
            V val;
            inf >> key >> val;
            auto temp = make_pair(key, val);
            insert(temp);
        };
        inf.close();                // closes the ifstream
        return true;
    } else {
        inf.close();
        return false;
    }

}

template<typename K, typename V>
void HashTable<K, V>::dump() { // prints the hashtable
   int i=0;                    // index counter
       for (auto & List : table) { //for every list in the table
           int j=0;                 // counter for items in the list
           std::cout<<"\nv["<<i<<"]: ";     // output the index and increase it by one
           i++;
           for (auto & pair : List) {   //for every pair in the list out put the key and then the value,if the next index is greater than 1 the output a semicolon
               if(j+1> 1)
                   std::cout<<" : ";
               std::cout<< pair.first <<" "<< pair.second;
               j++;
           }
       }

}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) {
    std::ofstream outp;                                                         // create output file stream
    outp.open(filename);                                                        // open the given file
    if(outp.is_open()) {                                                        // make sure it opened correctly
        for (auto & List : table) {                                             // for every element in the list
            for (auto &pair : List) {
                outp << pair.first << " " << pair.second << std::endl;          // print the key followed by a space followed by the value
            }
        }
        outp.close();                                                           //close the output file stream
    } else{
        outp.close();
        return false;
    }
}
template<typename K, typename V>
size_t HashTable<K, V>::GetSize()
{
    return thesize;         // returns the amount of elements in the table
}


//Private member functions
template<typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (auto &pair : table)      //for every element in the table( which should be list's) use the std::list clear() function to clear every list
    {
        pair.clear();
    }
    thesize = 0;          // set the size back to zero

}

template<typename K, typename V>
void
HashTable<K, V>::rehash() {                            //used the geeksforgeeks site for help on rehashing   https://www.geeksforgeeks.org/load-factor-and-rehashing/
    std::vector<std::list<std::pair<K, V>>> temp = table;// copyies the table to a temp table
    table.resize(prime_below(table.size() * 2));    //resize the table by twice its current size
    clear();                                        //clears the table
    thesize = 0;                                    //sets the size of the table to zero
    for (auto &List : temp) {                       //for every element in the old table, insert it to the new table
        for (auto &pair : List)
            insert(pair);
    }
}

template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) {
    std::hash<K> hashvalue;                             // use the std::hash function to make a hash of an arbitrary type

    return 41 * hashvalue(k) % table.size();            //calculates the index base on the prime number 41
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template<typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n) {                       // given
    if (n > max_prime) {
        std::cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime) {
        return max_prime;
    }
    if (n <= 1) {
        std::cerr << "** input too small \n";
        return 0;
    }

    // now: 2 <= n < max_prime
    std::vector<unsigned long> v(n + 1);
    setPrimes(v);
    while (n > 2) {
        if (v[n] == 1)
            return n;
        --n;
    }

    return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
template<typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long> &vprimes) {
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
        vprimes[i] = 1;

    for (i = 2; i * i < n; ++i) {
        if (vprimes[i] == 1)
            for (j = i + i; j < n; j += i)
                vprimes[j] = 0;
    }
}                   // given


#endif //UNTITLED9_HASHTABLE_HPP
