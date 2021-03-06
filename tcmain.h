#ifndef TCMAIN_H
#define TCMAIN_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "tcweapons.h"
using namespace std;

void populate_range(vector<int> &range, int min=0, int steps=25, int max=100) 
{
    if (min >= max) { 
	cerr << "Error_populate_range(): min must be less than max" << endl;
	return;
    }
	
    for (int i=0; i <= max ; i+=steps) {
	if (i >= min)
	    range.push_back(i);
    }
}

void print_weapon(Weapon* wep)
{
    cout << "-------------------------------------" << endl
         << wep->name << endl << "DPS: " << wep->dps
	 << " - Speed: " << wep->speed << endl;

    for ( pair<int, pair<float,float>> pair_ : wep->tpsVec) {
	cout << "| " << left << setw(3) << pair_.first << " %HS"
	     << " | R8: " << setw(7) << pair_.second.first
	     << " | R9: " << setw(7) << pair_.second.second << " |" << endl;
    }
}

void print_vec(const vector<Weapon*> weplist)
{
    for (Weapon* wep : weplist) {
	print_weapon(wep);
    }
}

void sort_vec(vector<Weapon*> &weplist, const int sortBy, bool r9)
{
    vector<Weapon*> sorted_weplist {weplist.begin(), weplist.end()};
    auto sort_lambda = [sortBy] (Weapon* wep1, Weapon* wep2)->bool
	    {return wep1->tpsVec[sortBy].second.first 
	     > wep2->tpsVec[sortBy].second.first;};

    if (r9 == true) {
	auto sort_lambda = [sortBy] (Weapon* wep1, Weapon* wep2)->bool
	    {return wep1->tpsVec[sortBy].second.second 
	     > wep2->tpsVec[sortBy].second.second;};
    }

    sort(sorted_weplist.begin(), sorted_weplist.end(), sort_lambda);
    weplist = sorted_weplist;
}

void write_file(string filename, const vector<Weapon*> &weplist, bool r9)
{
    const char delim{','};
    ofstream file(filename);
    if (!file.is_open()) {
	cerr << "Error_write_file(): '" << filename
	     << "' could not be created/opened." << endl;
	return;
    }
    
    file << "# TPS FOR WEAPONS IN 1.12 WOW DATA BY PLASK.\n# COMPARED BY PERCENTAGE (0-100). DPS, TF proc, HS threat and modifier are factored in. Stats are not. 6 second rotation with a total 3 instants is assumed.\n"; 

    if (!weplist.empty()) {
	file << "HS Spam %";
	for ( pair<int, pair<float,float>> pair_ : weplist[0]->tpsVec) {
	    file << delim << pair_.first;
	}
	file << "\n";
	for (Weapon* wep : weplist) {
	    file << wep->name;
	    for ( pair<int, pair<float,float>> pair_ : wep->tpsVec) {
		file << delim;
		if (!r9) {
		    file << fixed << setprecision(3) << pair_.second.first; 
		}
		else { 
		    file << fixed << setprecision(3) << pair_.second.second; 
		}
	    }
	    file << "\n";
	}
    }
    file.close();
}


#endif
