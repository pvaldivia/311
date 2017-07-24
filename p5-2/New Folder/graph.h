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
        void addVertex(string);
        void addEdge(string,string,int);
        void mst(string);
        void printVertex();
        void printEdges();

    private:
        class Vertex 
        {
            public:
            string pi;
            int key;
        };
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
};

#endif
