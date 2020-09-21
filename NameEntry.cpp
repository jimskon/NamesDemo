/***************************************************************************
 * NameEntry.cpp  -  Object to store name data for a single name
 *
 * copyright : (C) 2018 by Jim Skon, Kenyon College 
 *                                                          
 * This is part of a program create an index US Census name
 * Data on the frequency of names in response to requestes.  
 * It then allows you to look up any name, giving the 10 closest matches
 *                                                                                                                          
 * ***************************************************************************/
#include "NameEntry.h"

NameEntry::NameEntry() {
    name = ""; // Last name
    percent = ""; // Frequency of occurrence of a given name
    cumulative = ""; // cumulative frequency of all name up to and including this name
    rank = "";
}

NameEntry::NameEntry(string aName, string aPercent, string aCumulative, string aRank) {
    name = aName; 
    percent = aPercent; 
    cumulative = aCumulative;
    rank = aRank;
}



