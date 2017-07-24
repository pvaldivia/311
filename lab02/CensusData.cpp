/**
 * @file CensusData.cpp   Represents census population data.
 *
 * @brief
 *    Stores census data and implements several different types
 * of sorts. Data can be sorted by population or by name of town. Sort
 * functions are defined in a separate file.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CensusData.h"
using std::ios;
using std::istringstream;
using std::cout;
using std::endl;


/**
 * Record constructor.
 *
 * @param c The city.
 * @param s The state.
 * @param p The population.
 */
CensusData::Record::Record(string& c, string& s, int p) {
   city = new string(c);
   state = new string(s);
   population = p;
}

/**
 * Record destructor.
 */
CensusData::Record::~Record() {
   delete city;
   delete state;
}

/**
 * CensusData destructor.
 */
CensusData::~CensusData() {
   vector<Record*>::iterator it = data.begin();
   while (it != data.end()) {
      delete *it;
      it++;
   }
}

/**
 * CensusData::initialize.
 *
 * Rewinds to the beginning of the file. Parses each line to create a
 * Record and stores it.
 *
 * @param fp File pointer containing the census data.
 */
void CensusData::initialize(ifstream& fp) {
   fp.clear();
   fp.seekg(0, ios::beg);
   string line, city, state;
   int population;
   int pos1, pos2;
   CensusData::Record* record;
   while (getline(fp, line)) {
      pos1 = line.find(',');
      city = line.substr(0, pos1);
      pos2 = line.find(',', pos1+1);
      state = line.substr(pos1+1, pos2-pos1-1);
      istringstream popstrm (line.substr(pos2+1), istringstream::in);
      popstrm >> population;
      record = new CensusData::Record(city, state, population);
      data.push_back(record);
   }
}

/**
 * CensusData::makeHash.
 *
 * Make and use std::unordered_Map.
 */
void CensusData::makeHash() {

   unordered_map<string,Record*> mymap;
   cout << "Slots Available = "<< mymap.max_bucket_count() - mymap.size() << endl;
   cout << "Load factor = " << mymap.load_factor() << endl;
   cout << "Max Load Factor = " << mymap.max_load_factor() << endl;
   for (int i = 0; i < data.size(); i++)
   {
        mymap.insert(*(data[i]->city*),data[i]);
   }
   cout << "Slots Available = " << mymap.max_bucket_count() - mymap.size() << endl;
   cout << "Load factor = " << mymap.load_factor() << endl;
   cout << mymap[San Francisco]->population;
   

   // for now just print - delete this and replace with assigned steps
}

/**
 * CensusData::print.
 *
 * Iterates through the Records and prints the contents of each to stdout.
 */
void CensusData::print() {
   vector<Record*>::iterator it = data.begin();
   while (it != data.end()) {
      cout << *(*it)->city << ", "
                << *(*it)->state << ", "
                << (*it)->population << endl;
      it++;
   }
}

int main(int argc, char *argv[]){
   if ( argc != 2 ) {
      std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
      return 0;
   }

   ifstream fp;
   fp.open(argv[1], std::ios::in);
   if (!fp.is_open()) {
      std::cout << "can't open file " << argv[1] << std::endl;
      return 0;
   }

   CensusData myData;
   myData.initialize(fp);
   myData.makeHash();
}
