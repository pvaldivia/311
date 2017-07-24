/*
 * @filename rbapp.cpp
 *
 * @brief instantiates a RBTree and Reads in a set of commands 
 *
 * @author Pedro Valdivia
 * @data 11/9/11
 */
#include<iostream>
#include"rbtree.h"
#include"rbapp.h"
#include<sstream>

using std::cin;
using std::cout;
using std::ws;
using std::endl;

bool RBapp::processCommand(string& command)
{
    string key;
    string data;
    if (command == "insert")
    {
        cin >> ws;
        cin >> key;
        processInsert(key);
    }
    else if (command == "print")
    {
        processPrint();
    }
    else if (command == "find")
    {
        cin >> ws;
        cin >> key;
        vector <const string*> keys;
        keys = myRBT.rbFind(key);
        for (unsigned int i = 0; i < keys.size(); i++)
        {
            cout << key << " " << *(keys[i]) << endl;
        }
    }
    else if (command == "delete")
    {
        cin >> ws;
        cin >> key;
        processDelete(key);
    }
    else if (command == "quit")
    return false;

    return true;
}

void RBapp::processInsert(string& key)
{
    string satData;
    cin >> ws;
    getline(cin,satData);
    myRBT.rbInsert(key,satData);
}

void RBapp::processDelete(string& key)
{
    string satData;
    cin >> ws;
    getline(cin,satData);
    myRBT.rbDelete(key,satData);
}

void RBapp::processPrint()
{
    myRBT.rbPrintTree();
}

void RBapp::mainLoop()
{
    string command;
    cin >> command;
    while (processCommand(command))
    cin >> command;
}

int main()
{   
    RBapp myRBA;
    myRBA.mainLoop();
    return 0;
}

