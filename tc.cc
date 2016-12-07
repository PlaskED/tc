#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "tcheader.h"

using namespace std;


void Thunderfury::calculate_ranges()
{
    tpsMap["tpsr8_100"] = ((hs8*modifier)/speed)+(dps*modifier)+procTPS;
    tpsMap["tpsr9_100"] = ((hs9*modifier)/speed)+(dps*modifier)+procTPS;
    tpsMap["tpsr8_75"] = ((((hs8*modifier)/speed))*0.75)+(dps*modifier)+procTPS;
    tpsMap["tpsr9_75"] = ((((hs9*modifier)/speed))*0.75)+(dps*modifier)+procTPS;
    tpsMap["tpsr8_50"] = ((((hs8*modifier)/speed))*0.50)+(dps*modifier)+procTPS;
    tpsMap["tpsr9_50"] = ((((hs9*modifier)/speed))*0.50)+(dps*modifier)+procTPS;
    tpsMap["tpsr8_25"] = ((((hs8*modifier)/speed))*0.25)+(dps*modifier)+procTPS;
    tpsMap["tpsr9_25"] = ((((hs9*modifier)/speed))*0.25)+(dps*modifier)+procTPS;
}

void Weapon::calculate_ranges()
{
    tpsMap["tpsr8_100"] = ((hs8*modifier)/speed)+(dps*modifier);
    tpsMap["tpsr9_100"] = ((hs9*modifier)/speed)+(dps*modifier);
    tpsMap["tpsr8_75"] = ((((hs8*modifier)/speed))*0.75)+(dps*modifier);
    tpsMap["tpsr9_75"] = ((((hs9*modifier)/speed))*0.75)+(dps*modifier);
    tpsMap["tpsr8_50"] = ((((hs8*modifier)/speed))*0.50)+(dps*modifier);
    tpsMap["tpsr9_50"] = ((((hs9*modifier)/speed))*0.50)+(dps*modifier);
    tpsMap["tpsr8_25"] = ((((hs8*modifier)/speed))*0.25)+(dps*modifier);
    tpsMap["tpsr9_25"] = ((((hs9*modifier)/speed))*0.25)+(dps*modifier);
}

void print_weapon(Weapon* wep)
{
    cout << "-------------------------------------" << endl
	 << wep->name << endl << "DPS: " << wep->dps
	 << endl << "Speed: " << wep->speed << endl
	 << "100% HS: " << "R8: " << wep->tpsMap["tpsr8_100"] 
	 << "  R9: " << wep->tpsMap["tpsr9_100"] << endl
	 << "75% HS:  " << "R8: " << wep->tpsMap["tpsr8_75"]
	 << "  R9: " << wep->tpsMap["tpsr9_75"] << endl
	 << "50% HS:  " << "R8: " << wep->tpsMap["tpsr8_50"] 
	 << "  R9: " << wep->tpsMap["tpsr9_50"] << endl
	 << "25% HS:  " << "R8: " << wep->tpsMap["tpsr8_25"] 
	 << "  R9: " << wep->tpsMap["tpsr9_25"] << endl;
}

void print_map_sorted(const map<int,Weapon*> &weplist, const string sortBy)
{
    //Prints out the weaponlist sorted after the values from pair1 and pair2.
    cout << "Sorted by field: " << sortBy << endl;
    vector<pair<int,Weapon*>> sorted_weplist {weplist.begin(), weplist.end()};

    auto sort_lambda = [] (pair<int,Weapon*> pair1, pair<int,Weapon*> pair2)->bool
	{return pair1.second->tpsMap[sortBy] > pair2.second->tpsMap[sortBy];};

    sort(sorted_weplist.begin(), sorted_weplist.end(), sort_lambda);
    for (pair<int,Weapon*> pair_ : sorted_weplist)
    {
	print_weapon(*pair_.second);
    }
}

int main()
{ 
    string filename;
    ifstream file;
    stringstream ss;
    string line;
    map<int,Weapon*> wepmap;
    float name, dps, speed;
    int i{0};

    cout << "- Weapon TPS calculator - " << endl
	 << "Filename: ";
  
    cin >> filename;
    file.open(filename);
    if (!file.is_open())
    {
	cerr << "'" << filename
	     << "' could not be opened" << endl;
	return 1;
    }
    cin.clear();
  

    while(getline(file, name))
    {
	if (name != "-")
	{
	    getline(file,line);
	    dps = float(line);

	    getline(file,line);
	    speed = float(line);

	    wepmap[i] = new Weapon(name, dps, speed);
	    wepmap[i]->calculate_ranges();
	}
	ss.str("");
	ss.clear();
	i++;
    }

    wepmap[i] = new Thunderfury("Thunderfury, Blessed Blade of the Windseeker", 
				53.9, 1.90, true, false, true);
    wepmap[i]->calculate_ranges();
    
    
    print_map_sorted(wepmap, "tpsr8_100");

    return 0;
}
