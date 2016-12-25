#include "tcweapons.h"

void Thunderfury::calc_proc() 
{
    float procThreat = 270.0+92.0+149.0;
    float nrTPS = ((float(hasNrdmg)*((16+30)/2.0))/1.9)*modifier;
    float rotTPS = (((float(hasSlam)*2)+float(hasRev))*(1/6.0))
	*(procThreat*procRate*modifier);
    //TPS from rotation procs, SS -> RV -> SA -> SS, rot time is 6 sec

    /*
      cout << "procThreat: " << procThreat << endl;
      cout << "procRate: " << procRate << endl;
      cout << "rotTPS: " << rotTPS << endl;
      cout << "nrTPS: " << nrTPS << endl;
      cout << "hasNR: " << hasNrdmg << endl;
      cout << "hasRev: " << hasRev<< endl;
      cout << "hasSlam: " << hasSlam << endl;
    */

    procTPS = (((procThreat*procRate)*modifier)/speed)
	+ nrTPS + rotTPS;
    //cout << "procTPS: " << procTPS << endl;
}

void Ironfoe::calc_proc()
{
    //extra hits needs to consider crit/AP (NOTE, ONLY extra hits. Otherwise
    //consider crit and AP for everything).
    float extraHits = 2.0;
    float hitDmg = ((73+136)/2.0);
    float rotHits = ((((float(hasSlam)*2)+float(hasRev))*(1/6.0))
		     *procRate*extraHits);
    float rotTPS = (rotHits*hitDmg)*modifier;
    /*cout << "extraHits: " << extraHits << endl;
      cout << "procRate: " << procRate << endl;
      cout << "hasRev: " << hasRev<< endl;
      cout << "hasSlam: " << hasSlam << endl;
      cout << "rotHits: " << rotHits << endl;
    */

    procTPS = (((hitDmg*procRate*extraHits)*modifier)/speed)
	+ rotTPS;
    //cout << "procTPS: " << procTPS << endl;
}

void Viskag::calc_proc()
{
    float procDmg = 240.0;
    float rotHits = (((float(hasSlam)*2)+float(hasRev))*(1/6.0))
	*procRate;
    float rotTPS = rotHits*procDmg*modifier;
    procTPS = ((procRate*procDmg*modifier)/speed)+rotTPS;

    //cout << "procTPS: " << procTPS << endl;
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
