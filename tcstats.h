#ifndef TCSTATS_H
#define TCSTATS_H

class Target
{
 public:
 Target(int arm, int lvl, map<string,float> atker) : armor(arm),
	level(lvl), table(atker) {}
    ~Target() {}
    int armor;
    int level = 63;
    map<string,float> table;
    //float get_reduction();
};

class Stats
{
 public:
 Stats(int a, float c) 
     : ap(a), crit(c) {}
    ~Stats() {}
    float ap;
    float crit;
    Target target;
    
    float calculate_avg_hit(int dps, float speed);
    float calculate_crit_effect(int dmg)
    void printStats();
};



#endif
