/*
 * @filename spapp.h 
 *
 * @brief
 *      Minimum Spanning Tree Application.
 *
 * @author Pedro Valdivia
 * @date 12/07/16
 */
#ifndef SPAPP_H_
#define SPAPP_H_

#include<iostream>
#include"graph.h"

class SPapp 
{
    public: 
    SPapp();
    ~SPapp();
    void readGraph();
    void printGrid();
    void finalGraph(string,string);
    void removeObs(int,int);
    void removeVert(string);
    string toUpperLower(string);
    void setPath(string);
    void setShit(int,int);
    void setStart(int,int);
    void setEnd(int,int);

    private:
    Graph myGraph;
    vector<vector<string>> grid;
};

#endif 
