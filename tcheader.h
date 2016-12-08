#ifndef TCHEADER_H // header guards
#define TCHEADER_H
#include <string>
#include <map>

const float modifier{1.495}; //prot stance and defiance modifier
const float hs8{138+145}; //damage bonus + innate threat
const float hs9{157+145}; //damage bonus + innate threat

class Weapon
{
 public:
 Weapon(std::string n, float d, float s) : name(n), dps(d), speed(s) {};
    
    std::map<std::string, float> tpsMap;
    std::string name;
    float dps;
    float speed;

    virtual void calculate_ranges();
  
};

class Thunderfury : public Weapon
{
 public:
 Thunderfury(std::string name, std::string serv, float dps, float speed, bool hasNr, bool hass, bool hasr) : Weapon(name, dps, speed) {};

    std::string server;
    float autoProcRate{0.25};
    float procThreat{270+92+149};
    bool hasNrdmg;
    bool hasSlam;
    bool hasRev;
    float nrTPS = (float(hasNrdmg)*((16+30)/2))*(1/speed);
    float rotTPS = ((float(hasSlam)+float(hasRev))*0.16666666666666666)*(autoProcRate*procThreat); //TPS from rotation procs, rot is 6 sec
    float procTPS = ((((procThreat*autoProcRate)+rotTPS+nrTPS)*modifier)/speed);

    void calculate_ranges();
};

#endif
