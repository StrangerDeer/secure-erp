//
// Created by Joe Bekor on 2023. 11. 28..
//

#include "CRMDAO.h"
#include <fstream>
#include <algorithm>
using namespace crm;

void CRMDAO::printWarriors(PrintWarriors printWarriors) {
  std::vector<std::string> warriorData = readWarriors();
  std::vector<std::map<std::string,std::string>> printableWarriors;
  for(std::string line : warriorData) {
    std::map<std::string, std::string> warriorObj = createWarriorObject(line);
    printableWarriors.push_back(warriorObj);
  }
  printWarriors(printableWarriors, "Warriors");
}

bool CRMDAO::registerWarrior(const Warrior& warrior) {
  vector<string> warriorProps = {warrior.id,
                                 warrior.name,
                                 warrior.postPigeon,
                                 to_string(warrior.maxHp),
                                 to_string(warrior.currentHP),
                                 to_string(warrior.dmg),
                                 to_string(warrior.battlesWon),
                                 to_string(warrior.battlesLost),
                                 to_string(warrior.exp),
                                 to_string(warrior.level)};

  return writeWarriorToCSV(warriorProps);
}

std::vector<Warrior> CRMDAO::getWarriors() {
  std::vector<std::string> result = readWarriors();
  std::vector<Warrior> warriors;

  for(const std::string& line : result) {

    if(line.empty()){
      continue;
    }

    std::map<std::string,std::string> warriorObj = createWarriorObject(line);

    Warrior warrior = Warrior(warriorObj.at(headers.at(ID_HEADER_INDEX)),
                              warriorObj.at(headers.at(NAME_HEADER_INDEX)),
                              warriorObj.at(headers.at(PIGEON_HEADER_INDEX)),
                              stoi(warriorObj.at(headers.at(MAX_HP_HEADER_INDEX))),
                              stoi(warriorObj.at(headers.at(CURRENT_HP_HEADER_INDEX))),
                              stoi(warriorObj.at(headers.at(DMG_HEADER_INDEX))),
                              stoi(warriorObj.at(headers.at(BATTLES_WON_HEADER_INDEX))),
                              stoi(warriorObj.at(headers.at(BATTLES_LOST_HEADER_INDEX))),
                              stoi(warriorObj.at(headers.at(EXP_HEADER_INDEX))),
                              stoi(warriorObj.at(headers.at(LEVEL_HEADER_INDEX))));
    warriors.push_back(warrior);
  }

  return warriors;
}

std::map<std::string, std::string> CRMDAO::createWarriorObject(const std::string& line) const {
  std::vector<std::string> splitLine = splitLines(line);
  std::map<std::string, std::string> warrior;

  for(std::string keyValuePair : splitLine) {
    for(int i = 0; i < keyValuePair.size(); i++) {

      if(keyValuePair.at(i) == mapSeparator) {
        std::string key;
        std::string value;
        key = keyValuePair.substr(0, i);
        value = keyValuePair.substr(i + 1, keyValuePair.size());
        warrior.insert({key, value});
      }

    }
  }

  return warrior;
}

std::vector<std::string> CRMDAO::splitLines(const std::string& line) const {
  std::vector<std::string> result;
  std::string currentValue;

  for(char i : line) {
    if(i == valueSeparator) {
      result.push_back(currentValue);
      currentValue = "";
    }
    else {
      currentValue += i;
    }
  }

  return result;
}

std::vector<std::string> CRMDAO::readWarriors() {
  std::vector<std::string> result;
  std::string line;
  ifstream crmDB (DATA_FILE.data());

  if(crmDB.is_open()) {
    while(getline(crmDB, line)) {

      if(!line.empty()){
        result.push_back(line);
      }

    }

    crmDB.close();
  }

  return result;
}

bool CRMDAO::writeWarriorToCSV(vector<string> warriorProps) const {
  std::ofstream crmDB(DATA_FILE.data(), ios::app);

  if(crmDB.is_open()) {
    for(int i = 0; i < headers.size(); i++){
      crmDB << headers.at(i) << mapSeparator << warriorProps.at(i) << valueSeparator;
    }
    crmDB << std::endl;
    crmDB.close();
    return true;
  }
  else {
    return false;
  }

}

void CRMDAO::updateCSVFile(const std::vector<Warrior>& warriors) {
    std::ofstream crmDB(DATA_FILE.data(), std::ios::trunc);
    crmDB.close();

    for(const Warrior& warrior : warriors){
      registerWarrior(warrior);
    }
}

void CRMDAO::deleteWarriorByName(const std::string& warriorName) {
  std::vector<Warrior> warriors = getWarriors();
  int index = findWarriorIndexByName(warriors, warriorName);

  if(index >= 0){
    warriors.erase(warriors.begin() + index);
    updateCSVFile(warriors);
  } else {
    std::cout << "Can't find warrior with that name: " << warriorName << std::endl;
  }

}

void CRMDAO::updateWarriorWin(const Warrior& warrior) {
    std::vector<Warrior> warriors = getWarriors();
    int index = findWarriorIndexByName(warriors, warrior.name);
    warriors.at(index).battlesWon += 1;
    updateCSVFile(warriors);

}

void CRMDAO::updateWarriorLose(const Warrior& warrior) {
    std::vector<Warrior> warriors = getWarriors();
    int index = findWarriorIndexByName(warriors, warrior.name);
    warriors.at(index).battlesLost += 1;
    updateCSVFile(warriors);
}

void CRMDAO::decreaseWarriorHp(const Warrior& warrior) {
  std::vector<Warrior> warriors = getWarriors();
  int index = findWarriorIndexByName(warriors, warrior.name);

  if(warrior.currentHP < 0){
    warriors.at(index).currentHP = 0;
  } else {
    warriors.at(index).currentHP = warrior.currentHP;
  }

  updateCSVFile(warriors);
}

void CRMDAO::makeWarriorHpMax(const Warrior &warrior) {
  std::vector<Warrior> warriors = getWarriors();
  int index = findWarriorIndexByName(warriors, warrior.name);
  warriors.at(index).currentHP = warrior.maxHp;
  updateCSVFile(warriors);
}

void CRMDAO::increaseWarriorXp(const Warrior &warrior) {
  std::vector<Warrior> warriors = getWarriors();
  int index = findWarriorIndexByName(warriors, warrior.name);
  warriors.at(index).exp += winXp;

  if(warriors.at(index).exp >= needLevelUpXp){
    increaseWarriorLevelWithIndex(warriors, index);
  } else {
    updateCSVFile(warriors);
  }

}

void CRMDAO::increaseWarriorLevelWithIndex(std::vector<Warrior> warriors, int index) {
  warriors.at(index).exp = 0;
  warriors.at(index).level += 1;
  warriors.at(index).maxHp += levelUpHp;
  warriors.at(index).dmg += levelUpDmg;

  updateCSVFile(warriors);
}

int CRMDAO::findWarriorIndexByName(std::vector<Warrior> warriors, const std::string& name) {
  for(int i = 0; i <warriors.size(); i ++){
    Warrior currentWarrior = warriors.at(i);
    if(currentWarrior.name == name){
      return i;
    }
  }
  return -1;
}
