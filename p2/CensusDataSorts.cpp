/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CensusData.h"

/* 
 * @CensusData::insertionSort takes in one parameter       
 *        insertionSort sorts the data of Records inside the vector 
 * @param int type
 *        int type decides whether to sort the data by population or  
 *        city name 
 *
 * @returns nothing 
 */
void CensusData::insertionSort(int type)
{
    Record* pop_key;
    Record* city_key;
    int i = 0;
    if (type == 0)
    {
        for (unsigned int j = 1; j < data.size(); j++)
        {
            pop_key = data[j];
            i = j - 1;
            while (i >= 0 && data[i]->population > pop_key->population)
            {
                data[i+1] = data[i];
                i--;
            }
            data[i+1] = pop_key; 
        }
    }
    if (type == 1)
    {
        for (unsigned int j = 1; j < data.size(); j++)
        {
            city_key = data[j];
            i = j - 1;
            while (i >= 0 && *(data[i]->city) > *(city_key->city))
            {
                data[i+1] = data[i];
                i--;
            }
            data[i+1] = city_key;
        }
    }
}
/*
 * @CensusData::mergeSort takes in one parameter
 *        mergeSort calls CensusData::m_mergeSort
 *        and passes the type and size of vector data
 * @param int type
 *        int type will decide whether to sort the data by 
 *        population or city name
 *
 * @returns nothing
 */
void CensusData::mergeSort(int type) 
{
    m_mergeSort(type,0,data.size() - 1);
}
/*
 * @CensusData::m_mergeSort takes int 3 parameters
 *        m_mergeSort is a recursive divide and conquer 
 *        algorithm that sorts all data when p_merge is called
 * @param int type, p, r
 *        int type will decide whether to sort the data by 
 *        population or city 
 *        int p is the first index of the vector data
 *        int r is the last index of the vector data
 *
 * @returns nothing
 */       
void CensusData::m_mergeSort(int type, int p, int r)
{
    int q = 0;
    if (p < r)
    {
        q = (p + r)/2;
        m_mergeSort(type,p,q);
        m_mergeSort(type,q+1,r);
        if (type == 0)
        p_merge(p,q,r);
        else 
        c_merge(p,q,r);

    }
}
/*
 * @CensusData::p_merge takes in 3 parameters
 *        p_merge is part of the merge sort algorithm
 *        p_merge is where all the sorting takes place for 
 *        the merge Sort algorithm
 *        p_merge sorts the vector data by the Records Population
 * @param int p, q, r
 *        int p is the first index 
 *        int q is the middle index
 *        int r is the last index
 *
 * @returns nothing
 */
void CensusData::p_merge(int p, int q, int r)
{
    int left_elements = q - p + 1;
    int right_elements = r - q;
    vector<Record*> left;
    vector<Record*> right;

    for (int i = p; i < left_elements+p; i++)
    left.push_back(data[i]);

    for (int j = q+1; j <= right_elements+q; j++)
    right.push_back(data[j]);

    unsigned int i = 0;
    unsigned int j = 0;

    for (int k = p; k <= r; k++)
    {
        if (j == right.size() || (i != left.size() && 
        left[i]->population <= right[j]->population))
        {
            data[k] = left[i];
            i++;
        }
        else if (i == left.size() || (j != right.size() && 
        right[j]->population <= left[i]->population))
        {
            data[k] = right[j];
            j++;
        }
    }
}
/*
 * @CensusData::c_merge takes in 3 parameters
 *        c_merge is part of the merge sort algorithm
 *        c_merge is where all the sorting takes place for 
 *        the merge Sort algorithm
 *        c_merge sorts the vector data by the Records City name
 * @param int p, q, r
 *        int p is the first index 
 *        int q is the middle index
 *        int r is the last index
 *
 * @returns nothing
 */

void CensusData::c_merge(int p, int q, int r)
{
    int left_elements = q - p + 1;
    int right_elements = r - q;
    vector<Record*> left;
    vector<Record*> right;

    for (int i = p; i < left_elements+p; i++)
    left.push_back(data[i]);

    for (int j = q+1; j <= right_elements+q; j++)
    right.push_back(data[j]);

    unsigned int i = 0;
    unsigned int j = 0;

    for (int k = p; k <= r; k++)
    {
        if (j == right.size() || (i != left.size() && 
        *(left[i]->city) <= *(right[j]->city)))
        {
            data[k] = left[i];
            i++;
        }
        else if (i == left.size() || (j != right.size() && 
        *(right[j]->city) <= *(left[i]->city)))
        {
            data[k] = right[j];
            j++;
        }
    }
}
/*
 * @CensusData::quickSort
 *        quickSort just calls m_quickSort
 * @param int type
 *        type decides if we're going to sort the data by 
 *        city or population
 *
 * @returns nothing
 *
 */
void CensusData::quickSort(int type)
{
     m_quickSort(type,0,data.size() - 1);
}
/*
 * @CesnsusData::m_quickSort
 *        m_quickSort is a recursive divide and conquere sorting algorithm
 * 
 * @param int type, p, r
 *        int type decides if we will sort the data by the Record's 
 *        population or city name
 *        int p is the first index of the data vector
 *        int r is the last index of the data vector
 *
 * @returns nothing 
 */
void CensusData::m_quickSort(int type, int p, int r) 
{
    int q = 0;
    if (p < r)
    {
        q = randomPartition(type,p,r);
        m_quickSort(type,p,q-1);
        m_quickSort(type,q+1,r);
    }
}
/*
 * @CensusData::randomPartition 
 *        randomPartition chooses a random index from p to r and exchanges 
 *        the data[index] with the last element of the vector
 * @param int type, p, r
 *        int type decides if we're going to sort the data by the Record's
 *        population or city name
 *        int p is the first index of the data
 *        int r is the last index of the data
 *
 * @returns an integer or index of the pivot after partition is called
 */
int CensusData::randomPartition(int type, int p, int r)
{
    int i = randomNumber(p,r);
    Record* temp_r = data[r];
    data[r] = data[i];
    data[i] = temp_r;
    if (type == 0)
    return p_partition(p,r);
    
    return c_partition(p,r);
}
/*
 * @CensusData:p_partition 
 *        p_partition is part of the quicksort algorithm.
 *        This is where all work or all sorting occurs
 *        p_partition sorts the data by the Records Population
 * @param int p, r
 *        int p is the first index of the data
 *        int r is the last index of the data
 *
 * @returns an integer or index of the pivot after partition is called
 */

int CensusData::p_partition(int p, int r)
{
    int pivot = data[r]->population;
    int i = p - 1;

    for (int j = p; j < r; j++)
    {
        if (data[j]->population <= pivot)
        {
            i++;
            Record* temp_j = data[j];
            data[j] = data[i];
            data[i] = temp_j;
        }
    }
    Record* temp_r = data[r];
    data[r] = data[i+1];
    data[i+1] = temp_r;

    return i + 1;
}
/*
 * @CensusData:c_partition 
 *        c_partition is part of the quicksort algorithm.
 *        This is where all work or all sorting occurs
 *        c_partition sorts the data by the Records city name
 * @param int p, r
 *        int p is the first index of the data
 *        int r is the last index of the data
 *
 * @returns an integer or index of the pivot after partition is called
 */

int CensusData::c_partition(int p, int r)
{
    string* pivot = new string(*(data[r]->city));
    int i = p - 1;

    for (int j = p; j < r; j++)
    {
        if (*(data[j]->city) <= *(pivot))
        {
            i++;
            Record* temp_j = data[j];
            data[j] = data[i];
            data[i] = temp_j;
        }
    }
    Record* temp_r = data[r];
    data[r] = data[i+1];
    data[i+1] = temp_r;

    return i + 1;
}
/*
 * @CensusData::randomNumber
 *        randomNumber randomly chooses an integer between p and r
 * @param int p, r
 *        int p is the first index of the vector
 *        int r is the last index of the vector
 *
 * @return an integer or index of the vector
 *
 *
 */
int CensusData::randomNumber(int p, int r)
{
    srand(time(NULL));
    int interval = (r - p) + 1;
    int number = rand() % interval;
    return number + p;
}

