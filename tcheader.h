class Weapon 
{
 public:
  std::string name;
  float dps,speed,tpsr8_100,tpsr9_100,tpsr8_75,tpsr9_75,tpsr8_50,tpsr9_50,tpsr8_25,tpsr9_25;
  
  void calculate_tps();
};

class Thunderfury: public Weapon
{
 public:
  std::string server;
  const float autoProcRate{0.25};
  std::map <std::string,int> ProcThreat = { };
  
};
