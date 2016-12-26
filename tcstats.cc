#include <iostream>
#include <map>
#include <string>
#include "tcstats.h"

using namespace std;

float Stats::calculate_crit_effect(int dmg)
{
    float miss = target.table["miss"]/100.0;
    float dodge = target.table["dodge"]/100.0;
    float parry = target.table["parry"]/100.0;
    float block = target.table["block"]/100.0;
    float crit = target.table["crit"]/100.0;
    return dmg * ((1.00 - miss - dodge - parry - block - crit) + 2 * crit); 
}

float Stats::calculate_avg_hit(int dps, float speed) 
{
    //(Weapon DPS + AP/14) * Weapon Speed
    return (dps + (ap/14.0)) * speed;
}

void Stats::printStats()
{
    cout << "AP: " << ap << endl;
    cout << "crit: " << crit << endl;
}

int main()
{
    Stats *s = new Stats(503, 16.2);
    s->printStats();
}

/*
  2% base miss
  5% dodge
  5% parry
  5% block
  25% crit
  Damage = BaseDamage * ((1.00 - 0.02 - 0.05 - 0.05 - 0.05 - 0.25) + 2 * 0.25)
  = BaseDamage * 1.08

Damage = BaseDamage * ((1.00 - 0.02 - 0.05 - 0.05 - 0.05 - 0.26) + 2 * 0.26)
       = BaseDamage * 1.09 (dis is with 26% crit)
  /*
