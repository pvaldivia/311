/*
 * @filename mstapp.cpp
 * 
 * @brief
 *      Minimum Spanning Tree Application
 *
 * @author Pedro Valdivia
 * @date 12/07/2016
 */
#include"spapp.h"
#include<cctype>
#include<fstream>
#include<stdlib.h>
#include<cstring>

using std::cout;
using std::cin;
using std::endl;
using std::ws;
using std::isalpha;
using std::ifstream;
using std::ios;

int getRow(string);
int getCol(string);

/*
 * main
 */
SPapp spapp;

int main()
{
    int numObs = 0;
    int actRow = 0;
    int col = 0;
    char *row = NULL;
    string number;
    string starting;
    string end;
    string letter1;
    string obst;
    
    cout << "Welcome to the Shortest Path Application! Here is your starting grid"
         << endl;

    spapp.printGrid();
    spapp.readGraph();
    cout << "Pick a starting position: ";
    cin  >> starting;
    actRow = getRow(starting);
    col = getCol(starting);
    spapp.setStart(actRow,col);
    if (islower(starting[0]))
    starting = spapp.toUpperLower(starting);


    cout << "Pick ending position: ";
    cin  >> end;
    actRow = getRow(end);
    col = getCol(end);
    spapp.setEnd(actRow,col);
    if (islower(end[0]))
    end = spapp.toUpperLower(end);
    
    actRow = 0;
    col = 0;

    cout << "How many Obstacles would you like? ";
    cin  >> numObs;
    system("clear");

    while (numObs > 0)
    {
        spapp.printGrid();
        while ((actRow < 1 || actRow > 10) || (col < 1 || col > 10))
        {
            cout << "Select an obstacle to remove (Eg. A3): ";
            cin  >> obst;
            if (islower(obst[0]))
            obst = spapp.toUpperLower(obst);
            while (obst == starting || obst == end)
            {
                cout << "Cannot remove start or end positions."
                     << " Select an obstacle to remove: ";
                cin  >> obst;
                if (islower(obst[0]))
                obst = spapp.toUpperLower(obst);
            }
            actRow = getRow(obst);
            col = getCol(obst);
        }
        spapp.removeObs(actRow,col);
        spapp.removeVert(obst);
        actRow = 0;
        col = 0;
        numObs--;
        system("clear");
    }
    spapp.finalGraph(starting,end);
    delete row;
    return 0;
}
SPapp::SPapp()
{
    grid.resize(11);
    for (unsigned int row = 0; row < grid.size(); row++)
    grid[row].resize(11);

    for (unsigned int row = 1; row < grid.size(); row++)
    {
        for (unsigned int col = 1; col < grid[0].size(); col++)
        grid[row][col] = "[_]";
    }
    char ascii = 65;
    for (unsigned int row = 1; row < grid.size(); row++)
    {
        grid[row][0] = ascii;
        ascii++;
    }
    int num = 0;
    for (unsigned int col = 1; col < grid[0].size(); col++)
    {
        grid[0][col] = " " + std::to_string(num)  + " ";
        num++;
    }
    grid[0][0] = " ";
}

SPapp::~SPapp()
{

}
int getRow(string target)
{
    char *row = NULL;
    string letter = target.substr(0,1);
    row = new char [letter.length()+1];
    std::strcpy(row,letter.c_str());
    if (islower(*row))
    *row = toupper(*row);

    return *row - 64;
}
int getCol(string target)
{
    string number = target.substr(1,1);
    return std::stoi(number) + 1;
}
string SPapp::toUpperLower(string target)
{
    string letter1;
    string number;
    char *row = NULL;

    letter1 = target.substr(0,1);
    row = new char [letter1.length()+1];
    std::strcpy(row,letter1.c_str());
    number = target.substr(1,1);
    if (islower(*row))
    *row = toupper(*row);
    else
    *row = tolower(*row);

    return *row + number;
}

void SPapp::finalGraph(string start, string end)
{
    map<string,Graph::Vertex>::iterator it;
    map<string,Graph::Vertex> set;
    set = myGraph.dijkstra(start);
    
    it = set.find(end);
    if (it->second.pi != "nil")
    {
    while (it->second.pi != "nil")
    {
        it = set.find(it->second.pi);
        if (it->second.pi == "nil") continue;
        spapp.setPath(it->first);
    }
    }
    else 
    cout << "Sorry. No Available path." << endl;
    spapp.printGrid();
}
void SPapp::setPath(string path)
{
    int actRow = 0;
    int col = 0;

    actRow = getRow(path);
    col = getCol(path);

    spapp.setShit(actRow,col);
}
void SPapp::setShit(int row, int col)
{
    grid[row][col] = "[O]";
}

void SPapp::setStart(int row, int col)
{
    grid[row][col] = "[S]";
}
void SPapp::setEnd(int row, int col)
{
    grid[row][col] = "[F]";
}

void SPapp::removeVert(string target)
{
    myGraph.removeVertex(target);
}

void SPapp::printGrid()
{   
    for (unsigned int row = 0; row < grid.size(); row++)
    {
        for (unsigned int col = 0; col < grid[0].size(); col++)
        cout << grid[row][col];
        cout << endl;
    }
}

void SPapp::removeObs(int row, int col)
{
    grid[row][col] = "[X]"; 
}

/*
 * MSTapp::readGraph 
 * Reads a graph to standard input and utilizes class Graph
 * to create a minimum spanning tree
 *
 * @returns nothing
 */
void SPapp::readGraph()
{
    ifstream my_ifile("igraph.txt",ios::in);
    string vertex;
    vector <string> vertexes;
    while (my_ifile.peek() != '\n')
    {
        my_ifile >> vertex;
        vertexes.push_back(vertex);
        myGraph.addVertex(vertex);
    }
    string vertex2;
    int weight;
    while (my_ifile.peek() != EOF)
    {
        my_ifile >> ws;
        if (isalpha(my_ifile.peek()))
        {
            my_ifile >> vertex >> vertex2 >> weight;
            myGraph.addEdge(vertex,vertex2,weight);
            myGraph.addEdge(vertex2,vertex,weight);
        }
    }
}

