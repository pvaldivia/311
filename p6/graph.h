#ifndef GRAPH_H_
#define GRAPH_H_

#include<iostream>
#include<map>
#include<string>
#include"minpriority.h"

using std::map;

class Graph
{
    public:
        class Vertex 
        {
            public:
            string pi;
            int key;
        };
        void addVertex(string);
        void addEdge(string,string,int);
        map<string,Vertex> dijkstra(string);
        void removeVertex(string);
        void printVertex();
        void printEdges();
        void printAdj();
        void printVer();
    private:
        class Neighbor
        {
            public:
            string name;
            int weight;
            bool operator<(const Neighbor& n) const {return name < n.name;}
        };
        MinPriorityQ minQ;
        map<string,Vertex> vertices;
        map<string,vector<Neighbor>> adjList;
        int weight(string,string);
        void adjListSort(vector<Neighbor>&);
        void printTree(map<string,Vertex>);
};

#endif
