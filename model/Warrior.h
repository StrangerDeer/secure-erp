//
// Created by User on 2023. 12. 11..
//

#ifndef SECURE_ERP_CPP_MODEL_WARRIOR_H_
#define SECURE_ERP_CPP_MODEL_WARRIOR_H_

#include <string>
#include "../util/Util.h"
class Warrior {
 public:
  Warrior(std::string id, std::string& name, std::string& postPigeon) : name(name), postPigeon(postPigeon), battlesLost(0), battlesWon(0), id(id) {}
  std::string& id;
  std::string& name;
  std::string& postPigeon;
  int battlesWon;
  int battlesLost;
};

#endif //SECURE_ERP_CPP_MODEL_WARRIOR_H_
