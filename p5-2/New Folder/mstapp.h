/*
 * @filename mstapp.h 
 *
 * @brief
 *      Minimum Spanning Tree Application.
 *
 * @author Pedro Valdivia
 * @date 12/07/16
 */
#ifndef MSTAPP_H_
#define MSTAPP_H_

#include<iostream>
#include"graph.h"

class MSTapp 
{
    public: 
    void readGraph();

    private:
    Graph myGraph;
};

#endif 
