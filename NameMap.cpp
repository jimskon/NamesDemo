/***************************************************************************
 * NameMap.cpp - Object to store a map of all names and data about that name, 
 * and allow insertion and and looking up of names.
 *
 * copyright : (C) 2018 by Jim Skon, Kenyon College
 *
 * This is part of a program create an index US Census name
 * Data on the frequency of names in response to requestes.  
 * It then allows you to look up any name, giving the 10 closest matches
 * 
 ***************************************************************************/
#include "NameMap.cpp"

NameMap::NameMap(string filename) {

    NameEntry nameData;
    fstream infile(filename);
    if (infile.good()) {
        while (1) {
            infile >> nameData.name;
            infile >> nameData.percent;
            infile >> nameData.cumulative;
            infile >> nameData.rank;
            if (infile.fail()) break;
            nameMap[nameData.name] = nameData;
        }
        infile.close();
        success = true;
    } else {
        success = false;
    }
}

bool NameMap::NameMapSuccess() {
    return success;
}

vector<NameEntry> NameMap::getMatches(string name) {
    vector<NameEntry> matchList;
    NameEntry match;
    // Look up the closest lower match
    map<string, NameEntry>::iterator it = nameMap.lower_bound(name);

    // back up (up to) 5 places
    for (int i = 0; i < 5 && (it != nameMap.begin()); i++) {
        it--;
    }

    // Get (up to) 10 results
    for (int i = 0; i < 10 && (it != nameMap.end()); i++) {
        
        match = (*it).second;
        matchList.push_back(match);
        it++;
    }
    return matchList;;
}
