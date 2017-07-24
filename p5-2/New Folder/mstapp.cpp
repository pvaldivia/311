/*
 * @filename mstapp.cpp
 * 
 * @brief
 *      Minimum Spanning Tree Application
 *
 * @author Pedro Valdivia
 * @date 12/07/2016
 */
#include"mstapp.h"
#include<cctype>
#include<stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::ws;
using std::isalpha;
/*
 * main
 */
int main()
{
    MSTapp mstapp;
    mstapp.readGraph();
    return 0;
}
/*
 * MSTapp::readGraph 
 * Reads a graph to standard input and utilizes class Graph
 * to create a minimum spanning tree
 *
 * @returns nothing
 */
void MSTapp::readGraph()
{
    string vertex;
    vector <string> vertexes;
    while (cin.peek() != '\n')
    {
        cin >> vertex;
        vertexes.push_back(vertex);
        myGraph.addVertex(vertex);
    }
    string vertex2;
    int weight;
    while (cin.peek() != EOF)
    {
        cin >> ws;
        if (isalpha(cin.peek()))
        {
            cin >> vertex >> vertex2 >> weight;
            myGraph.addEdge(vertex,vertex2,weight);
            myGraph.addEdge(vertex2,vertex,weight);
        }
    }
    myGraph.mst(vertexes[0]);
}

