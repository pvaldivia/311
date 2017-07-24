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

    while (it->first != from && it != adjList.end())
    it++;

    if (it == adjList.end())
    {
        cout << "From Edge not found" << endl;
        vector<Neighbor> nectar;
        adjList.insert (pair<string,vector<Neighbor>>(from,nectar));
        it = adjList.find(from);
    }
    
    Neighbor amigo;
    amigo.name = to;
    amigo.weight = weight;
    it->second.push_back(amigo);
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
/*
 * Graph::mst
 * Finds a minimum spanning tree based on a given graph
 *
 * @param root String that indicates which vertex to start the mst
 *
 * @returns nothing
 */
void Graph::mst(string root)
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

    it = vertices.begin();
    while (it->first != root && it != vertices.end())
    it++;

    if (it == vertices.end())
    {
        cout << "root not in graph" << endl;
        return;
    }

    it->second.key = 0;

    for (it = vertices.begin(); it != vertices.end(); it++)
    minQ.insert(it->first,it->second.key);

    vector<Vertex> extracted;
    vector<string> sv_extracted;

    while (!minQ.empty())
    {
        string s_extracted = minQ.extractMin();
        it = vertices.find(s_extracted);
        if (it != vertices.end())
        {
            Vertex ext_vertex;
            ext_vertex.pi = it->second.pi;
            ext_vertex.key = it->second.key;
            extracted.push_back(ext_vertex);
            sv_extracted.push_back(s_extracted);
        }

        it2 = adjList.begin();
        while (it2->first != s_extracted && it2 != adjList.end())
        it2++;

        if (it2 != adjList.end())
        {
            for (unsigned int i = 0; i < it2->second.size(); i++)
            {
                it = vertices.find(it2->second[i].name);
                if (minQ.isMember(it2->second[i].name) && 
                   weight(s_extracted,it2->second[i].name) < it->second.key)
                {
                    it = vertices.begin();
                    while(it->first != it2->second[i].name && 
                          it != vertices.end())
                          it++;

                    it->second.pi = s_extracted;
                    it->second.key = weight(s_extracted,it2->second[i].name);
                    
                    minQ.decreaseKey(it->first, it->second.key);
                }
            }
        }
    }
    int total_weight = 0;
    for (unsigned int i = 0; i < sv_extracted.size(); i++)
    {
        cout << sv_extracted[i] << " "
             << extracted[i].pi << " ";
        if (extracted[i].key == INT_MAX)
        extracted[i].key = 0;

        cout << extracted[i].key << endl;
        if (extracted[i].pi != "nil")
        total_weight += extracted[i].key;
    }
    cout << total_weight << endl;

}

