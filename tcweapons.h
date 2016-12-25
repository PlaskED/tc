#ifndef TCWEAPONS_H
#define TCWEAPONS_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const float modifier{1.495}; //prot stance and defiance modifier
const float hs8{138+145}; //damage bonus + innate threat
const float hs9{157+145}; //damage bonus + innate threat

class Weapon
{
 public:
 Weapon(string n, float d, float s) : name(n), dps(d), speed(s) {};
    ~Weapon() {}

    vector<pair<int, pair<float,float>>> tpsVec;
    string name;
    float dps;
    float speed;
    float procTPS{0};

    virtual void calc_proc() {};
    void calculate_ranges(const vector<int> range);
  
};

class ProcWeapon : public Weapon
{
 public:
 ProcWeapon(string name, string serv, float proc,
	    float dps, float speed, bool hass, bool hasr)
     : Weapon(name, dps, speed), 
	procRate(proc), hasSlam(hass), hasRev(hasr) {};
    ~ProcWeapon() {}

    std::string server;
    float procRate;
    bool hasSlam;
    bool hasRev;

    virtual void calc_proc() = 0;
};

class Thunderfury : public ProcWeapon
{
 public:
 Thunderfury(string name, string server, float proc,
	     float dps, float speed, bool hasNr,
	     bool hass, bool hasr) 
     : ProcWeapon(name, server, proc, dps, speed, hass, hasr),
	hasNrdmg(hasNr) {};
    ~Thunderfury() {}

    bool hasNrdmg;

    void calc_proc();
};

class Ironfoe : public ProcWeapon
{
 public:
 Ironfoe(string name, string serv, float proc,
	 float dps, float speed, bool hass, bool hasr) 
     : ProcWeapon(name, serv, proc, dps, speed, hass, hasr) {};
    ~Ironfoe() {}
    
    void calc_proc();
};

class Viskag : public ProcWeapon
{
 public:
 Viskag(string name, string serv, float proc,
	 float dps, float speed, bool hass, bool hasr) 
     : ProcWeapon(name, serv, proc, dps, speed, hass, hasr) {};
    ~Viskag() {}

    void calc_proc();
};

#endif
