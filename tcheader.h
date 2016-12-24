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
 Thunderfury(std::string name, std::string serv, float dps, float speed, bool hasNr, bool hass, bool hasr) : Weapon(name, dps, speed), hasNrdmg(hasNr), hasSlam(hass), hasRev(hasr) {};

    std::string server;
    float autoProcRate{0.25};
    float procThreat{505};//270+92+149};
    bool hasNrdmg;
    bool hasSlam;
    bool hasRev;
    float nrTPS = 0;
    float rotTPS = 0;

    void calc_proc();
};

class Ironfoe : public Weapon
{
    
};

#endif
