//
// Created by User on 2023. 12. 11..
//

#ifndef SECURE_ERP_CPP_MODEL_WARRIOR_H_
#define SECURE_ERP_CPP_MODEL_WARRIOR_H_

#include <string>
#include "../util/Util.h"
class Warrior {
 public:
  Warrior(std::string id, std::string& name, std::string& postPigeon, int hp, int damage) :
    name(name), postPigeon(postPigeon), maxHp(hp), dmg(damage), battlesLost(0), battlesWon(0), id(id) {}

  Warrior(std::string id, std::string& name, std::string& postPigeon, int hp, int dmg, int win, int lose) :
    name(name), postPigeon(postPigeon), maxHp(hp), dmg(dmg), battlesLost(lose), battlesWon(win), id(id) {}

  std::string id;
  std::string name;
  std::string postPigeon;
  int maxHp;
  int dmg;
  int battlesWon;
  int battlesLost;
  std::string toString() {
    return "Id: " + id + " name: " + name + " postPigeon: " + postPigeon + " battles: " + to_string(battlesLost) + "/" + to_string(battlesWon);
  }
  void fight(Warrior& enemy){
      enemy.maxHp = enemy.maxHp - dmg;
  }
};

#endif //SECURE_ERP_CPP_MODEL_WARRIOR_H_
