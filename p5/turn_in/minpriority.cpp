/*
 * @filename minpriority.cpp
 *
 * @brief Implements a minimum priority queue using heapsort
 *
 * @author Pedro Valdivia
 *
 * @date 11/29/2016
 */

#include"minpriority.h"
#include<climits>

using std::cout;
using std::endl;


MinPriorityQ::MinPriorityQ()
{}

MinPriorityQ::Element::~Element()
{

}
/* MinPriorityQ::print
 *
 * Iterates through the vector and prints each 
 * Element Objects id and key
 *
 * @returns nothing 
 *
 */
void MinPriorityQ::print()
{
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        cout << *(elements[i]->m_id) << " ";
        cout << elements[i]->m_key << endl;
    }
}
/*
 * MinPriorityQ::insert
 *
 * Creates a new element object with the passed in parameters.
 * Then pushes the new element object into the minQ and calls 
 * the function decrease key to put object into its correct 
 * location in the minQ.
 *
 * @param id String holding the name of the element object
 * @param key Integer value that holds the priority of the 
 *            element object
 *
 * @returns nothing
 */
void MinPriorityQ::insert(string id, int key)
{
    Element* object = new Element(id,INT_MAX);
    elements.push_back(object);
    decreaseKey(id,key);
}
/*
 * MinPriorityQ::decreaseKey
 *
 * If the passed in param id is found in the minQ,
 * then utilizes a while loop to decrease the key of 
 * the element object with the passed in id. Also changes 
 * the location of the element object into its correct location
 * in minQ.
 *
 * @param id String holding the name of the element object
 * @param newKey Integer value that holds the priority of the element object
 *
 * @returns nothing
 */
void MinPriorityQ::decreaseKey(string id, int newKey)
{
    if (!isMember(id))
    return;
   
    int index = 0;
    while (*(elements[index]->m_id) != id)
    index++;

    if (newKey > elements[index]->m_key)
    {
        cout << "new key is bigger than current key" << endl;
        return;
    }

    int key_temp = 0;
    string* id_temp = NULL;
    elements[index]->m_key = newKey;

    while (index > 0 && elements[parent(index)]->m_key > elements[index]->m_key)
    {
        key_temp = elements[index]->m_key;
        id_temp = elements[index]->m_id;
        elements[index]->m_key = elements[parent(index)]->m_key;
        elements[index]->m_id = elements[parent(index)]->m_id;
        elements[parent(index)]->m_key = key_temp;
        elements[parent(index)]->m_id = id_temp;
        index = parent(index);
    }
}
/*
 * MinPriorityQ::extractMin
 *
 * Exracts or pops the first element object of the minQ.
 * Then calls minHeapify on first element of the vector.
 *
 * @returns a String holding the name of the Element object
 *  that was extracted
 */
string MinPriorityQ::extractMin()
{
    string min;
    Element* temp_element = NULL;
    unsigned heapsize = elements.size() - 1;

    if (elements.size() < 1)
    {
        cout << "empty" << endl;
        min = "";
    }
    else
    {
        min = *(elements[0]->m_id);
        elements[0]->m_key = elements[heapsize]->m_key;
        *(elements[0]->m_id) = *(elements[heapsize]->m_id);
        temp_element = elements[heapsize];
        elements.pop_back();
        delete temp_element->m_id;
        delete temp_element;
        minHeapify(0);
    }
    return min;
}
/*
 * MinPriorityQ::isMember
 *
 * Iterates through the vector of Element pointer objects
 * until it either finds a match with the string id parameter
 * that was passed in or untile it reaches the end.
 *
 * @returns true if match found
 *               else returns false
 *
 */
bool MinPriorityQ::isMember(string id)
{
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        if (*(elements[i]->m_id) == id)
        return true;
    }
    
    return false;
}
/*
 * MinPriorityQ::buildMinHeap
 *
 * Creates the minQ of our member vector that holds Element
 * object pointers based on each elements keys
 *
 * @returns nothing
 *
 */
void MinPriorityQ::buildMinHeap()
{
    unsigned heap_size = elements.size();

    for (unsigned int i = heap_size/2; i > 0; i--)
    minHeapify(i);
}
/*
 * MinPriorityQ::minHeapify
 *
 * Maintains the heap property of having 
 * left and right children with keys greater than the 
 * parent of the children. This property is applied to 
 * the subtree of the index that was passed in.
 *
 * @param index Integer value that holds the index position of our minQ
 *  
 * @return nothing
 */
void MinPriorityQ::minHeapify(int index)
{
    unsigned int Left;
    unsigned int Right;
    unsigned int heapsize = elements.size() - 1;
    string* id_temp = NULL;
    int key_temp = 0;
    int smallest;
    
    Left = left(index);
    Right = right(index);

    if(Left <= heapsize && elements[Left]->m_key < elements[index]->m_key)
    smallest = Left;
    else
    smallest = index;

    if(Right <= heapsize && elements[Right]->m_key < elements[smallest]->m_key)
    smallest = Right;
    
    if(smallest != index)
    {
        key_temp = elements[index]->m_key;
        id_temp = elements[index]->m_id;
        elements[index]->m_key = elements[smallest]->m_key;
        elements[index]->m_id = elements[smallest]->m_id;
        elements[smallest]->m_key = key_temp;
        elements[smallest]->m_id = id_temp;
        minHeapify(smallest);
    }
}
/*
 * MinPriorityQ::parent
 *
 * @param index Integer value that holds an index position of our minQ
 *
 * @returns the parent of the passed in index position
 */
int MinPriorityQ::parent(int index)
{
    return (index/2);
}
/*
 * MinPriorityQ::left
 *
 * @param index Integer value that holds an index position of our minQ
 *
 * @returns an int that holds the position of the left child of the passed in index 
 */
int MinPriorityQ::left(int index)
{
    return (2*index);
}
/*
 * MinPriorityQ::right
 *
 * @param index Integer value that holds an index position of our minQ
 *
 * @returns an int that holds the position of the right child of the passed in index
 */
int MinPriorityQ::right(int index)
{
    return (2*index + 1);                                                      
}
