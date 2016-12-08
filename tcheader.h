#ifndef TCHEADER_H
#define TCHEADER_H

const float modifier{1.495}; //prot stance and defiance modifier
const float hs8{138+145}; //damage bonus + innate threat
const float hs9{157+145}; //damage bonus + innate threat

class Weapon
{
 public:
 Weapon(std::string n, float d, float s) : name(n), dps(d), speed(s) {};
    
    std::vector<std::pair<int, std::pair<float,float>>> tpsVec;
    std::string name;
    float dps;
    float speed;
    float procTPS{0};

    virtual void calc_proc();
    void calculate_ranges(const std::vector<int> range);
  
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
    float rotTPS = ((float(hasSlam)+float(hasRev))
		    *0.16666666666666666)*(autoProcRate*procThreat); 
    //TPS from rotation procs, rot time is 6 sec
    void calc_proc();
};

#endif
