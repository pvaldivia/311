/*
 * @filename graph.cpp Represents a minimum spanning tree
 *
 * @brief 
 *      creates a weighted undirected graph of vertices.
 *
 * @author Pedro Valdivia
 * @date 12/07/2016
 */
#include"graph.h"
#include<climits>
#include<algorithm>
#include<iostream>

using std::pair;
using std::cout;
using std::endl;
/*
 * Graph::addVertex
 * Adds a string that maps to a Vertex object into the vertices map
 *
 * @param vertex String holding the name of Vertex object
 *
 * @returns nothing
 */
void Graph::addVertex(string vertex)
{
    Vertex newVertex;
    newVertex.pi = "";
    newVertex.key = 0;
    vertices.insert(pair<string,Vertex>(vertex,newVertex));
    
}
/*
 * Graph::addEdge
 * Adds a Neighbor object to a specific vertex of the graph
 *
 * @param from String holding the vertex to add a Neighbor to
 * @param to String holding the name of Neighbor that is to be added to "from"
 *           neighbors
 *
 * @returns nothing
 */
void Graph::addEdge(string from, string to, int weight)
{
    map<string, vector<Neighbor>>::iterator it;
    it = adjList.begin();
    
    while (!adjList.empty() && it != adjList.end() && it->first != from)
    it++;

    if (adjList.empty() || it == adjList.end())
    {
        vector<Neighbor> nectar;
        adjList.insert (pair<string,vector<Neighbor>>(from,nectar));
        it = adjList.find(from);
    }
    
    Neighbor amigo;
    amigo.name = to;
    amigo.weight = weight;
    it->second.push_back(amigo);
}
void Graph::printVer()
{
    map<string,Vertex>::iterator it;
    
    for (it = vertices.begin(); it != vertices.end(); it++)
    {
        cout << it->first << " ";
    }
    cout << endl;
}
void Graph::printAdj()
{
    map<string,vector<Neighbor>>::iterator it;

    for (it = adjList.begin(); it != adjList.end(); it++)
    {
        cout << it->first << " ";
        for (unsigned int i = 0; i < it->second.size(); i++)
        {
            cout << it->second[i].name << " ";
        }
        cout << endl;
    }
}
/*
 * Graph::adjList
 * Uses std::sort to sort a vector full of neighbors 
 * based on the the neighbors name
 *
 * @para sorted A vector of Neighbor objects
 *
 * @returns nothing
 */
void Graph::adjListSort(vector<Neighbor>& sorted)
{
    std::sort(sorted.begin(),sorted.end());
}
/*
 * Graph::weight
 * Finds the weight between two vertices
 *
 * @param u String that holds the name of the vertex
 * @param v String that holds the name of the neighbor to "u"
 *
 * @returns an integer that holds the weight between two vertices
 */
int Graph::weight(string u, string v)
{
    map<string,vector<Neighbor>>::iterator it;
    it = adjList.begin();

    while (it->first != u && it != adjList.end())
    it++;

    if (it == adjList.end())
    return -1;

    for(unsigned int i = 0; i < it->second.size(); i++)
    {
        if (it->second[i].name == v)
        return it->second[i].weight;
    }

    return -1;
}
void Graph::removeVertex(string node)
{
    map<string,Vertex>::iterator it;
    map<string,vector<Neighbor>>::iterator it2;

    it = vertices.find(node);
    vertices.erase(it);
    it2= adjList.find(node);
    adjList.erase(it2);

    for (it2 = adjList.begin(); it2 != adjList.end(); it2++)
    {
        for (unsigned int i = 0; i < it2->second.size(); i++)
        {
            if (node == it2->second[i].name)
            it2->second.erase(it2->second.begin()+i);
        }
    }
}
/*
 * Graph::mst
 * Finds a minimum spanning tree based on a given graph
 *
 * @param root String that indicates which vertex to start the mst
 *
 * @returns nothing
 */
map<string,Graph::Vertex> Graph::dijkstra(string root)
{
    map<string,Vertex>::iterator it;
    map<string,vector<Neighbor>>::iterator it2;


    for (it2 = adjList.begin(); it2 != adjList.end(); it2++)
    adjListSort(it2->second);

    for (it = vertices.begin(); it != vertices.end(); it++)
    {
        it->second.pi = "nil";
        it->second.key = INT_MAX;
    }

    it = vertices.find(root);

    it->second.key = 0;
    
    for (it = vertices.begin(); it != vertices.end(); it++)
    minQ.insert(it->first,it->second.key);
        
    map<string,Vertex> newSet; 

    int counter = 0;
    while (!minQ.empty())
    {
        Vertex newVertex;
        string extracted;
        extracted = minQ.extractMin();
        it = vertices.find(extracted);
        newVertex.pi = it->second.pi;
        newVertex.key = it->second.key;
        newSet.insert(pair<string,Vertex>(it->first,newVertex));

        it2 = adjList.find(extracted);
        if (newVertex.pi != "nil" || counter == 0)
        {
            for (unsigned int i = 0; i < it2->second.size(); i++)
            {
                it = vertices.find(it2->second[i].name);
                if (it->second.key > (newVertex.key + it2->second[i].weight))
                {
                    it->second.key = newVertex.key + it2->second[i].weight;
                    it->second.pi = extracted;
                    minQ.decreaseKey(it->first,it->second.key);
                }
            }
        }
        counter++;
    }
    return newSet;
}

void Graph::printTree(map<string,Vertex> set)
{
    map<string,Vertex>::iterator it;
    int counter = 0;
    for (it = set.begin(); it != set.end(); it++)
    {
        if (counter % 5 == 0)
        cout << endl;
        cout << it->first << it->second.key << it->second.pi << " ";
        counter++;
    }
}
