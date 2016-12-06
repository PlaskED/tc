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

const float modifier{1.495}; //prot stance and defiance modifier
const float hs8{138+145}; //damage bonus + innate threat
const float hs9{157+145}; //damage bonus + innate threat

void Weapon::calculate_tps()
{
  cout << name << endl;
  if (name == "Thunderfury, Blessed Blade of the Windseeker (buffed)") {
    float procCha1 = 0.25;
    float Procthreat1 = 270+92+149;
    float procTPS1 = ((Procthreat1*modifier*procCha1)/speed); //threat per proc divided by speed and 0,25 multiplier as 25% procchance
    float nrDMG1 = ((16+30)/2); //the extra NR dmg per hit calculated in weapon dps
    //float nrDMG = 0; //Currently bugged on nost
    float fullrot1=0.166666666666666*0.25*Procthreat1; //2/6 abilities in 6 sec rotrocs as SS doesnt proc
    cout << "fullrot: " << fullrot1
	 << " Procthreat: " << Procthreat1 
	 << " procTPS: " << procTPS1 << endl;
    
    tpsr8_100 = (((nrDMG1+hs8)*modifier)/speed)+((dps+fullrot1)*modifier)+procTPS1;
    tpsr9_100 = (((nrDMG1+hs9)*modifier)/speed)+((dps+fullrot1)*modifier)+procTPS1;
    tpsr8_75 = ((((nrDMG1+hs8)*modifier)/speed)*0.75)+((dps+fullrot1)*modifier)+procTPS1;
    tpsr9_75 = ((((nrDMG1+hs9)*modifier)/speed)*0.75)+((dps+fullrot1)*modifier)+procTPS1;
    tpsr8_50 = ((((nrDMG1+hs8)*modifier)/speed)*0.50)+((dps+fullrot1)*modifier)+procTPS1;
    tpsr9_50 = ((((nrDMG1+hs9)*modifier)/speed)*0.50)+((dps+fullrot1)*modifier)+procTPS1;
    tpsr8_25 = ((((nrDMG1+hs8)*modifier)/speed)*0.25)+((dps+fullrot1)*modifier)+procTPS1;
    tpsr9_25 = ((((nrDMG1+hs9)*modifier)/speed)*0.25)+((dps+fullrot1)*modifier)+procTPS1;
  }
  else if (name == "Thunderfury, Blessed Blade of the Windseeker")
  {
    float procCha = 0.15;
    float Procthreat = 270+92+149;
    float procTPS = ((Procthreat*modifier*procCha)/speed); //threat per proc divided by speed and 0,25 multiplier as 25% procchance
    //float nrDMG{((16+30)/2)}; //the extra NR dmg per hit calculated in weapon dps
    float nrDMG = 0; //Currently bugged on nost
    float fullrot = 0.16666666666666666*0.20*Procthreat; //1/6 abilities in 6 sec rot procs as SS doesnt proc
    cout << "fullrot: " << fullrot
	 << " Procthreat: " << Procthreat 
	 << " procTPS: " << procTPS << endl;
    
    tpsr8_100 = (((nrDMG+hs8)*modifier)/speed)+((dps+fullrot)*modifier)+procTPS;
    tpsr9_100 = (((nrDMG+hs9)*modifier)/speed)+((dps+fullrot)*modifier)+procTPS;
    tpsr8_75 = ((((nrDMG+hs8)*modifier)/speed)*0.75)+((dps+fullrot)*modifier)+procTPS;
    tpsr9_75 = ((((nrDMG+hs9)*modifier)/speed)*0.75)+((dps+fullrot)*modifier)+procTPS;
    tpsr8_50 = ((((nrDMG+hs8)*modifier)/speed)*0.50)+((dps+fullrot)*modifier)+procTPS;
    tpsr9_50 = ((((nrDMG+hs9)*modifier)/speed)*0.50)+((dps+fullrot)*modifier)+procTPS;
    tpsr8_25 = ((((nrDMG+hs8)*modifier)/speed)*0.25)+((dps+fullrot)*modifier)+procTPS;
    tpsr9_25 = ((((nrDMG+hs9)*modifier)/speed)*0.25)+((dps+fullrot)*modifier)+procTPS;
  }
  else {
    tpsr8_100 = ((hs8*modifier)/speed)+(dps*modifier);
    tpsr9_100 = ((hs9*modifier)/speed)+(dps*modifier);
    tpsr8_75 = (((hs8*modifier)/speed)*0.75)+(dps*modifier);
    tpsr9_75 = (((hs9*modifier)/speed)*0.75)+(dps*modifier);
    tpsr8_50 = (((hs8*modifier)/speed)*0.50)+(dps*modifier);
    tpsr9_50 = (((hs9*modifier)/speed)*0.50)+(dps*modifier);
    tpsr8_25 = (((hs8*modifier)/speed)*0.25)+(dps*modifier);
    tpsr9_25 = (((hs9*modifier)/speed)*0.25)+(dps*modifier);
  }
}

void print_weapon(const Weapon wep)
{
  cout << "-------------------------------------" << endl
       << wep.name << endl 
       << "DPS: " << wep.dps
       << endl << "Speed: "
       << wep.speed << endl
       << "100% HS: " << "R8: "
       << wep.tpsr8_100 << "  R9: " << wep.tpsr9_100 << endl
       << "75% HS:  " << "R8: "
       << wep.tpsr8_75 << "  R9: " << wep.tpsr9_75 << endl
       << "50% HS:  " << "R8: "
       << wep.tpsr8_50 << "  R9: " << wep.tpsr9_50 << endl
       << "25% HS:  " << "R8: "
       << wep.tpsr8_25 << "  R9: " << wep.tpsr9_25 << endl;
}

void print_map_sorted(const map<int,Weapon*> &weplist)
{
  //Prints out the weaponlist sorted after the values from pair1 and pair2. 
  vector<pair<int,Weapon*>> sorted_weplist {weplist.begin(), weplist.end()};

  auto sort_lambda = [] (pair<int,Weapon*> pair1, pair<int,Weapon*> pair2)->bool
    {return pair1.second->tpsr8_100 > pair2.second->tpsr8_100;};

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
  string line,wepname;
  map<int,Weapon*> wepmap;
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
  

  while(getline(file,wepname))
  {
    if (wepname != "-")
    {
      wepmap[i] = new Weapon;
      wepmap[i]->name = wepname;

      getline(file,line);
      wepmap[i]->dps = stof(line);

      getline(file,line);
      wepmap[i]->speed = stof(line);
      wepmap[i]->calculate_tps();
      //print_weapon(*wepmap[i]);
    }
    ss.str("");
    ss.clear();
    i++;
  }
    
  print_map_sorted(wepmap);

  return 0;
}
