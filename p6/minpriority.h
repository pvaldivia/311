/*
 * @filename minpriority.h
 *
 * @brief  
 *
 * @author Pedro Valdivia
 *
 * @date 11/14/16
 *
 */

#ifndef MINPRIORITY_H
#define MINPRIORITY_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;


class MinPriorityQ
{
    public:
        MinPriorityQ();
        void insert(string,int);
        void decreaseKey(string,int);
        void print();
        string extractMin();
        bool isMember(string);
        bool empty();
        

    private:

        class Element
        {
            public:
                Element (string id, int key)
                {m_id = new string(id); m_key = key;}
                ~Element();
                string* m_id;
                int m_key;
        };

        vector <Element*> elements;

        void buildMinHeap();
        void minHeapify(int);
        int  parent(int);
        int  left(int);
        int  right(int);

};

#endif 
