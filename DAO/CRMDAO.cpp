//
// Created by Joe Bekor on 2023. 11. 28..
//

#include "CRMDAO.h"
#include <fstream>
using namespace crm;
bool CRMDAO::createWarrior(Warrior warrior) {
  vector<string> warriorProps = {warrior.id, warrior.name, warrior.postPigeon, to_string(warrior.battlesWon), to_string(warrior.battlesLost)};
  std::ofstream crmDB(DATA_FILE.data());
  if(crmDB.is_open()) {
    for(int i = 0; i < headers.size(); i++){
      crmDB << headers[i] << " : " << warriorProps[i] << ";";
    }
    crmDB.close();
    return true;
  }
  else {
    return false;
  }
}