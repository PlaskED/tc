#include "tcmain.h"

using namespace std;

int main()
{ 
    string filename;
    ifstream file;
    stringstream ss;
    string line, name;
    vector<Weapon*> wepvec;
    float dps, speed;
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

    while(getline(file, name)) {
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
    file.close();

    wepvec.push_back(new Thunderfury("Thunderfury", "Nostalrius", 0.25, 41.90, 1.90, true, true, true));
    wepvec[wepvec.size()-1]->calculate_ranges(range);
    wepvec.push_back(new Ironfoe("Ironfoe", "Nostalrius", 0.05, 43.50, 2.40, true, true));
    wepvec[wepvec.size()-1]->calculate_ranges(range);
    wepvec.push_back(new Viskag("Viskag", "Nostalrius", 0.05, 55.20, 2.60, true, true));
    wepvec[wepvec.size()-1]->calculate_ranges(range);
    
    sort_vec(wepvec, 0, false);
    print_vec(wepvec);
    write_file("datar8.csv", wepvec, false);
    write_file("datar9.csv", wepvec, true);

    return 0;
}
