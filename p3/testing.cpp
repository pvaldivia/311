#include<iostream> 
#include<list>
#include<string>
#include<fstream>

using namespace std;

int main()
{
    list <string> mylist [5];
    list <string>::iterator it;

    mylist[1].resize(2);
    cout << "mylist[1].size = " << mylist[1].size() << endl;
    mylist[4].resize(10);
    cout << "mylist[4].size = " << mylist[4].size() << endl;

    it = mylist[1].begin();
    mylist[1].insert(it,"Pedro");
    it++;
    mylist[1].insert(it,"is");
    it = mylist[4].begin();

    mylist[4].insert(it,"Mah Boy");
    mylist[4].insert(it,"Whats good");

    for (int i = 0; i < 5; i++)
    {
        cout << "Row:" << i << "\t";
        for (it = mylist[i].begin(); it !=  mylist[i].end(); it++)
        {
            cout << *it << ", ";
        }
        cout << endl;
    }
    string key;
    int i = 0;
    ifstream my_ifile("hash.in", ios::in);
    while (getline(my_ifile,key, '\n'))
    {
        cout << "key = " << key << endl;
        mylist[i].push_back(key);
        if (i > 3)
        i = 0;

        i++;
        cout << "success" << " i = " << i << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << "Row:" << i << "\t";
        for (it = mylist[i].begin(); it !=  mylist[i].end(); it++)
        {
            cout << *it << ", ";
        }
        cout << endl;
    }

    ofstream my_ofile("hash.out2", ios::out);
    for (int i = 0; i < 5; i++)
    {
        my_ofile << "Row:" << i << "\t";
        for (it = mylist[i].begin(); it !=  mylist[i].end(); it++)
        {
            my_ofile << *it << ", ";
        }
        my_ofile << endl;
    }
    
    
/*    mylist.resize(5);

    list <string>::iterator it;
    
    it = mylist.begin();
    mylist.insert(it,"Pedro");
    it++;
    mylist.insert(it,"is");
    it++;
    mylist.insert(it,"the");
    it++;
    mylist.insert(it,"best");
    it++;
    mylist.insert(it,"mah boy!");
    for (it = mylist.begin(); it != mylist.end();it++)
    {
        cout << ' ' << *it;
    }
    it = mylist.begin();
*/
    return 0;
}
