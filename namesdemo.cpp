/***************************************************************************
* nameservercpp  -  Program to serve of last name statistics
 *
* copyright : (C) 2009 by Jim Skon
*
* This program create an index US Census name
* Data on the frequency of names in response to requestes.  
* It then allows you to look up any name, giving the 10 closest matches
* 
* 
*
***************************************************************************/
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

/* Name data structure */
struct name_record
{
  string name;         // Last name
  string percent;      // Frequency of occurance of a given name
  string cumulative;   // Cummulative freqency of all name up to and including this name
  string rank;         // Rank of this Name in terms of frequency
};


map<string,name_record> lname_map;
map<string,name_record> fname_map;
map<string,name_record> mname_map;
map<string,name_record>::iterator it;

/*
 * Read the US Census data file "dist.all.last" and load it into an
 * in memory b+tree with name as the key.
 *
 * Return 1 if success, 0 if fail
 */
int createnamemap(map<string,name_record> &name_map ,string filename) {
	
  name_record namedata;
  fstream infile(filename.c_str());
  if (infile.good()) {
	while (1)
	  {
		infile >> namedata.name;
		infile >> namedata.percent;
		infile >> namedata.cumulative;
		infile >> namedata.rank;
		if (infile.fail()) break;
		name_map[namedata.name] = namedata;
		//cout << namedata.name + " " <<  namedata.percent << " " 
		//	 << namedata.cumulative << " " << namedata.rank << endl;
	  }
	infile.close();
	return(1);
  } else {
	return(0);
  }
}


/* Server main line,create name MAP, wait for and serve requests */
int main() {
  
  string name,percent,rank,type;
  name_record result;
  int pos;
  map<string,name_record> *curMap;
  string path = "/home/class/SoftDev/namedata/";
  
  // Create the map of last name data
  if (createnamemap(lname_map,path+"dist.all.last") != 1) {
	cout << "Error Loading Database" << endl;
	exit(0);
  }
  // Create the map of male name data
  if (createnamemap(mname_map,path+"dist.male.first") != 1) {
	cout << "Error Loading Database" << endl;
	exit(0);
  }
  // Create the map of last name data
  if (createnamemap(fname_map,path+"dist.female.first") != 1) {
	cout << "Error Loading Database" << endl;
	exit(0);
  }
  char sel;
  
  cout << "Name data loaded!" << endl;
  cout << "Look up US name statistics" << endl;
  /* See what user wants */
  do {    
   
    cout << "Select one: " << endl << "  1. Last name" << endl
	 << "  2. Female first names" << endl << "  3. Male First Names" << endl
	 << "  0. End Program." << endl << "Select:";
    cin >> sel;

    if (sel == '1' || sel == '2' || sel == '3') {

      cout << "Ender name to check:";
      cin >> name;

      /* Convert verse to upper case*/
      transform(name.begin(), name.end(), name.begin(), ::toupper);
    
	// Try to find the record

      if (sel == '1') {
	//Get the closest match
	it = lname_map.lower_bound (name);
	curMap = &lname_map;

      } else  if (sel== '2') {
	//Get the closest match
	it = mname_map.lower_bound (name);
	curMap = &mname_map;

      } else  if (sel == '3') {
	//Get the closest match
	it = fname_map.lower_bound (name);
	curMap = &fname_map;
      }

      // back up 5 places
      for (int i=0 ; i<5 && (it!=curMap->begin()); i++) {
	it--;
      }

      // Get 10 results
      for (int i=0 ; i<10 && (it!=curMap->end()); i++) {
	result = (*it).second;
	name = result.name;
	percent = result.percent;
	rank = result.rank;
	cout << name << "\t" << percent << "\t" << rank << endl;;
	it++;

      }
    }
  } while (sel != '0');
}
