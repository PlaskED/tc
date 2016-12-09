#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "tcheader.h"

using namespace std;

const string delimiter{"Thunderfury"};

void Weapon::calc_proc() 
{
    cerr << "Error_Weapon::calc_proc(): did you call this by mistakes?" << endl;
    procTPS=0;
}

void Thunderfury::calc_proc() 
{
     nrTPS = (float(hasNrdmg)*((16+30)/2.0))*(1.0/speed);
    rotTPS = ((float(hasSlam)+float(hasRev))
		    *0.16666666666666666)*(autoProcRate*procThreat);
    //TPS from rotation procs, rot time is 6 sec
    cout << "procThreat: " << procThreat << endl;
    cout << "autoProcRate: " << autoProcRate << endl;
    cout << "rotTPS: " << rotTPS << endl;
    cout << "nrTPS: " << nrTPS << endl;
    cout << "hasNR: " << hasNrdmg << endl;
    cout << "hasRev: " << hasRev<< endl;
    cout << "hasSlam: " << hasSlam << endl;

    procTPS = ((((procThreat*autoProcRate)+rotTPS+nrTPS)*modifier)/speed);
}

void Weapon::calculate_ranges(const vector<int> range)
{
    if (range.size() == 0) { 
	cerr << "Error_calculate_range(): range vector is empty." << endl;
	return;
    }

    pair<int, pair<float,float>> val;
    pair<float,float> sec;

    calc_proc();
    cout << procTPS << endl;

    for ( auto it = range.rbegin() ; it != range.rend(); ++it) {
	int ra = *it;
	float r8 = (((hs8*modifier)/speed)*(ra/100.0))+(dps*modifier)+procTPS;
	float r9 = (((hs9*modifier)/speed)*(ra/100.0))+(dps*modifier)+procTPS;
	sec.first = r8; 
	sec.second = r9;
	val.first = ra;
	val.second = sec;
	tpsVec.push_back(val);
    }
}

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
    cout << "Sorted by field: " << sortBy << endl;
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

void write_xmlfile(string filename, const vector<Weapon*> &weplist, const int sortBy, bool r9)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
	cerr << "Error_write_xmlfile(): '" << filename
	     << "' could not be created." << endl;
	
	return;
    }
    
}

int main()
{ 
    string filename;
    ifstream file;
    stringstream ss;
    string line, name;
    vector<Weapon*> wepvec;
    float dps, speed;
    //int min=0, int steps=10, int max=100;
    vector<int> range;
    int i{0};

    cout << "- Weapon TPS calculator - " << endl
	 << "Filename: ";

    while (!file.is_open() && getline(cin, filename)) {
	file.open(filename);
	if (file.is_open()) {
	    break;
	}
	cerr << "Error_main(): '" << filename
	     << "' could not be opened." << endl;
	cout << "Filename: ";
	
    }
    cin.clear();

    int min=5, steps=10, max=100;
    populate_range(range, min, steps, max);

    while(getline(file, name) && i < 0) {
	if (name != "-") {
	    getline(file,line);
	    dps = stof(line);

	    getline(file,line);
	    speed = stof(line);
	    
	    wepvec.push_back(new Weapon(name, dps, speed));
	    wepvec[wepvec.size()-1]->calculate_ranges(range);
	}
	ss.str("");
	ss.clear();
	i++;
    }

    wepvec.push_back(new Thunderfury("Thunderfury, Blessed Blade of the Windseeker", "Nostalrius", 53.90, 1.90, true, false, true));
    wepvec[wepvec.size()-1]->calculate_ranges(range);
    
    sort_vec(wepvec, 0, false);
    print_vec(wepvec);

    return 0;
}
