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
  Warrior(std::string id, std::string& name, std::string& postPigeon, int win, int lose) : name(name), postPigeon(postPigeon), battlesLost(lose), battlesWon(win), id(id) {}
  Warrior(const Warrior& other) : id(other.id), name(other.name), postPigeon(other.postPigeon), battlesWon(other.battlesWon), battlesLost(other.battlesLost) {}
  std::string id;
  std::string name;
  std::string postPigeon;
  int battlesWon;
  int battlesLost;
  std::string toString() {
    return "Id: " + id + " name: " + name + " postPigeon: " + postPigeon + " battles: " + to_string(battlesLost) + "/" + to_string(battlesWon);
  }
};

#endif //SECURE_ERP_CPP_MODEL_WARRIOR_H_
