/***************************************************************************
 * NameEntry.h  -  Object to store name data for a single name
 *
 * copyright : (C) 2018 by Jim Skon, Kenyon College
 *
 * This is part of a program create an index US Census name
 * Data on the frequency of names in response to requestes.  
 * It then allows you to look up any name, giving the 10 closest matches
 * 
 * 
 *
 ***************************************************************************/
#ifndef NAMEENTRY_H
#define NAMEENTRY_H
#include <string>

using namespace std;

class NameEntry {
public:
  NameEntry();
  NameEntry(string aName, string aPercent, string aCumulative, string aRank);
  string name; // Last name
  string percent; // Frequency of occurrence of a given name
  string cumulative; // cumulative frequency of all name up to and including this name
  string rank; // Rank of this Name in terms of frequency
private:

};

#endif /* NAMEENTRY_H */

