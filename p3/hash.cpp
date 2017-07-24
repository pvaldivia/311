/*
 * @filename Hash.cpp 
 * 
 * @brief stores data in hashTable created by the STL list and implements 
 * different functions with that data 
 *
 * @author Pedro Valdivia
 * 
 * @data 10/26/16
 *
 */
#include "hash.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
/*
 * Hash Constructor
 *
 * @param collisions Number of Collisions
 * @param longestList Longest List in hashTable
 * @param runningAvgListLength Runtime Average
 *
 */
Hash::Hash()
{
    collisions = 0;
    longestList = 0;
    runningAvgListLength = 0;
    
}
/** 
 * Hash::print.
 * 
 * Goes throught all content of the hashTable and prints it to stdout
 *
 */
void Hash::print()
{
    list<string>::iterator it;

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        cout << i << ":\t";
        for(it = hashTable[i].begin(); it != hashTable[i].end(); it++)
        {
            cout << *it << ", ";
        }
        cout << endl;
    }
}
/**
 * Hash::search.
 * 
 * Goes through the content of the HashTable until it finds a key that
 * matches the key that was passed into it as a parameter
 *
 * @param key string containing word
 *
 * @returns true if a key is found in hashTable, otherwise false
 *
 */
bool Hash::search(string key)
{
    list<string>::iterator it;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        for (it = hashTable[i].begin(); it != hashTable[i].end(); it++)
        {
            if (*it == key)
            return true;
        }
    }

    return false;
}
/*
 * Hash::remove.
 *
 * Removes the a string within the hashTable if Hash::search return true,
 * otherwise does nothing.
 *
 * @param key string containing a word
 *
 * @return nothing
 *
 */
void Hash::remove(string key)
{
    list<string>::iterator it;
    if (search(key))
    {
        for (int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            for (it = hashTable[i].begin(); it != hashTable[i].end(); it++)
            {
                if (*it == key)
                {
                    hashTable[i].erase(it);
                    double currentAvgListLen = (double)entries()/nonEmptyLists();
                    runningAvgListLength = (currentAvgListLen + runningAvgListLength)/2;
                    return;
                }
            }
        }
    }
}
/*
 * @Hash::processFile.
 *
 * Goes through each line of filename and stores the content of each line 
 * into the hashTable
 *
 * @param filename file containing data
 *
 * @returns nothing
 *
 */
void Hash::processFile(string filename)
{
    string key;
    int index;
    ifstream my_ifile(filename,ios::in);
    while (getline(my_ifile,key, '\n'))
    {
        index = hf(key);
        hashTable[index].push_back(key);

        if (hashTable[index].size() > longestList)
        longestList = hashTable[index].size();
        if (hashTable[index].size() > 1)
        collisions++;

        double currentAvgListLen = (double)entries()/nonEmptyLists();
        runningAvgListLength = (currentAvgListLen + runningAvgListLength)/2;
    }
}
/*
 * @Hash::output.
 *
 * Prints the contents of hashTable to stdout in filename
 *
 * @param filename empty file
 *
 * @return nothing
 */
void Hash::output(string filename)
{
    list<string>::iterator it;
    ofstream my_ofile(filename, ios::out);
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        my_ofile << i << ":\t";
        for (it = hashTable[i].begin(); it != hashTable[i].end(); it++)
        {
            my_ofile << *it << ", ";
        }
        my_ofile << endl;
    }
}
/*
 * Hash::printStats.
 *
 * Prints out the Object's Statistics to stdout
 *
 * @returns nothing
 */
void Hash::printStats()
{
    cout << "Total Collisions = " << collisions << endl;
    cout << "Longest List Ever = " << longestList << endl;
    cout << "Average List Length Over Time = " << runningAvgListLength << endl;
    cout << "Load Factor = " << (double)entries()/HASH_TABLE_SIZE << endl;
}
/*
 * Hash::nonEmptyLists
 *
 * iterates through hashTable and counts the total of 
 * nonempty lists
 *
 * @return number of nonemptylists
 */
int Hash::nonEmptyLists()
{
    int numEmptyLists = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (hashTable[i].size() == 0)
        numEmptyLists++;
    }
    return HASH_TABLE_SIZE - numEmptyLists;
}
/*
 * Hash::entries.
 *
 * Iterates through the hashTable and counts the number of
 * elements/keys
 *
 * @returns total number of keys/elements in hashTable
 */
int Hash::entries()
{
    int entries = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        entries += hashTable[i].size();
    }

    return entries;
}
