/*
 * @filename main.cpp
 *
 * @brief Test driver used to test the functionality
 *        of a Minimum Priority Queue
 *
 * @author Pedro Valdivia
 *
 * @date 11/30/2016
 */
#include "minpriority.h"
#include <iostream>
#include <sstream>

using std::cin;
using std::ws;
using std::cout;
using std::endl;

int main()
{
    MinPriorityQ minQueue;
    string command;
    string id;
    int key;
    while (cin >> command)
    {
        if (command == "a")
        {
            cin >> ws;
            cin >> id;
            cin >> ws;
            cin >> key;
            cout << "id = " << id << " key = " << key << endl;
            minQueue.insert(id,key);
        }
        else if (command == "d")
        {
            cin >> ws;
            cin >> id;
            cin >> ws;
            cin >> key;
            cout << "id = " << id << " key = " << key << endl;
            minQueue.decreaseKey(id,key);
        }
        else if (command == "x")
        {
            string extracted;
            extracted = minQueue.extractMin();
            if (extracted != "")
            cout << extracted << endl;
        }
        else if (command == "q")
        break;
    }
    return 0;
}
