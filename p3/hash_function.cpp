/* This assignment originated at UC Riverside.
 * @filename hash_function.cpp 
 *
 * @author Pedro Valdivia
 *
 * @data 10/26/16
 */
 
#include <string>
#include<iostream>
#include "hash.h"

using std::string;
using std::stoi;
using std::endl;
using std::cout;

/*
 * hash::hf
 *
 * calculates an index value bases on the key passed in
 *
 * @param key String containing a word
 * 
 * @returns an index of hashTable 
 */
int 
Hash::hf ( string key ) {
  
  long sum = 0;
  long mult = 1;

  string::iterator it;
  for (it = key.begin(); it != key.end(); it++)
  {
    sum +=  (*it*mult);
    mult *= 256;
  }
  
  int virtual_size = HASH_TABLE_SIZE;
  
  while (virtual_size % 2  == 0 || virtual_size % 3  == 0 || 
         virtual_size % 5  == 0 || virtual_size % 7  == 0 || 
         virtual_size % 11 == 0 || virtual_size % 13 == 0 || 
         virtual_size % 17 == 0 || virtual_size % 19 == 0 ||
         virtual_size % 23 == 0 || virtual_size % 29 == 0)
         {
            if (virtual_size < 29 ) break;
            virtual_size--;
         }

  return (sum) % virtual_size;

}

