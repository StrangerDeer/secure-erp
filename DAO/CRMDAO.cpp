//
// Created by Joe Bekor on 2023. 11. 28..
//

#include "CRMDAO.h"
#include <fstream>
#include <algorithm>
using namespace crm;
bool CRMDAO::createWarrior(Warrior warrior) {
  vector<string> warriorProps = {warrior.id,
                                 warrior.name,
                                 warrior.postPigeon,
                                 to_string(warrior.maxHp),
                                 to_string(warrior.currentHP),
                                 to_string(warrior.dmg),
                                 to_string(warrior.battlesWon),
                                 to_string(warrior.battlesLost)};

  std::ofstream crmDB(DATA_FILE.data(), ios::app);
  if(crmDB.is_open()) {
    for(int i = 0; i < headers.size(); i++){
      crmDB << headers[i] << ":" << warriorProps[i] << ";";
    }
    crmDB << std::endl;
    crmDB.close();
    return true;
  }
  else {
    return false;
  }
}

std::vector<Warrior> CRMDAO::getWarriors() {
  std::vector<std::string> result = readWarriors();
  std::vector<Warrior> warriors;
  for(std::string line : result) {

      if(line.size() == 0){
          continue;
      }

    std::map<std::string,std::string> warriorObj = createWarriorObject(line);

    Warrior warrior = Warrior(warriorObj.at("Id"),
                              warriorObj.at("Name"),
                              warriorObj.at("PostPigeon"),
                              stoi(warriorObj.at("MaxHp")),
                              stoi(warriorObj.at("CurrentHp")),
                              stoi(warriorObj.at("DMG")),
                              stoi(warriorObj.at("BattlesWon")),
                              stoi(warriorObj.at("BattlesLost")));
    warriors.push_back(warrior);
  }
  return warriors;
}
void CRMDAO::printWarriors(PrintWarriors printWarriors) {
  std::vector<std::string> warriorData = readWarriors();
  std::vector<std::map<std::string,std::string>> printableWarriors;
  for(std::string line : warriorData) {
    std::map<std::string, std::string> warriorObj = createWarriorObject(line);
    printableWarriors.push_back(warriorObj);
  }
  printWarriors(printableWarriors, "Warriors");
}
void CRMDAO::listTopWarriors(PrintWarriors printWarriors, int count) {
  std::vector<std::string> warriorData = readWarriors();
  std::vector<std::map<std::string,std::string>> warriors;
  for(std::string line : warriorData) {
    std::map<std::string, std::string> warriorObj = createWarriorObject(line);
    warriors.push_back(warriorObj);
  }
  orderByWinRatio(warriors);
  printWarriors(std::vector<std::map<std::string, std::string>>(warriors.begin(), warriors.size() >= count ? warriors.begin() + count : warriors.end()), "Best Warriors");
}
void CRMDAO::orderByWinRatio(std::vector<std::map<std::string, std::string>>& warriors) {
  std::sort(warriors.begin(), warriors.end(),
            [this](const auto& warrior1, const auto& warrior2) {
              return this->compareWinRatio(warrior1, warrior2);
            });
}
bool CRMDAO::compareWinRatio(const std::map<std::string, std::string> &warrior1,
                             const std::map<std::string, std::string> &warrior2) {
  return (std::stoi(warrior1.at("BattlesWon")) / ((std::stoi(warrior1.at("BattlesLost"))) + std::stoi(warrior1.at("BattlesWon")))) >
      (std::stoi(warrior2.at("BattlesWon")) / ((std::stoi(warrior2.at("BattlesLost"))) + std::stoi(warrior2.at("BattlesWon"))));
}
void CRMDAO::deleteWarriorByName(std::string warriorName) {
    std::vector<Warrior> warriors = getWarriors();
    for(int i = 0; i <warriors.size(); i ++){
        Warrior warrior = warriors.at(i);
        if(warrior.name == warriorName){
            warriors.erase(warriors.begin() + i);
            updateCSVFile(warriors);
        }
    }
}
std::map<std::string, std::string> CRMDAO::createWarriorObject(std::string line) {
  std::vector<std::string> splitLine;
  std::map<std::string, std::string> warrior;
  std::string currentValue;

  for(int i = 0; i < line.size(); i++) {
    if(line.at(i) == ';') {
      splitLine.push_back(currentValue);
      currentValue = "";
    }
    else {
      currentValue += line.at(i);
    }
  }
  for(std::string keyValuePair : splitLine) {
    for(int i = 0; i < keyValuePair.size(); i++) {
      if(keyValuePair.at(i) == ':') {
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

std::vector<std::string> CRMDAO::readWarriors() {
  std::vector<std::string> result;
  std::string line;
  ifstream crmDB (DATA_FILE.data());
  if(crmDB.is_open()) {
    while(getline(crmDB, line)) {
      result.push_back(line);
    }
    crmDB.close();
  }
  return result;
}

void CRMDAO::updateCSVFile(const std::vector<Warrior>& warriors) {
    std::ofstream crmDB(DATA_FILE.data(), std::ios::trunc);
    crmDB.close();

    for(Warrior warrior : warriors){
        createWarrior(warrior);
    }
}

void CRMDAO::updateWarriorWin(std::string warriorName) {
    std::vector<Warrior> warriors = getWarriors();
    for(int i = 0; i <warriors.size(); i ++){
        Warrior warrior = warriors.at(i);
        if(warrior.name == warriorName){
            warriors.at(i).battlesWon += 1;
            updateCSVFile(warriors);
        }
    }
}

void CRMDAO::updateWarriorLose(std::string warriorName) {
    std::vector<Warrior> warriors = getWarriors();

    for(int i = 0; i <warriors.size(); i ++){
        Warrior warrior = warriors.at(i);
        if(warrior.name == warriorName){
            warriors.at(i).battlesLost += 1;
            updateCSVFile(warriors);
            break;
        }
    }
}
void CRMDAO::decreaseWarriorHp(const Warrior& warrior) {
  std::vector<Warrior> warriors = getWarriors();

  for(int i = 0; i <warriors.size(); i ++){
    Warrior currentWarrior = warriors.at(i);

    if(currentWarrior.name == warrior.name){

      if(warrior.currentHP < 0){
        warriors.at(i).currentHP = 0;
      } else {
        warriors.at(i).currentHP = warrior.currentHP;
      }

      updateCSVFile(warriors);

      break;
    }

  }
}
void CRMDAO::makeWarriorHpMax(const Warrior &warrior) {
  std::vector<Warrior> warriors = getWarriors();

  for(int i = 0; i <warriors.size(); i ++){
    Warrior currentWarrior = warriors.at(i);

    if(currentWarrior.name == warrior.name){
      int healedAmount = warriors.at(i).maxHp - warrior.currentHP;
      warriors.at(i).currentHP = warrior.maxHp;
      updateMedRecord(warrior, healedAmount);
      updateCSVFile(warriors);
      break;
    }
  }
}
void CRMDAO::updateMedRecord(Warrior warrior, int healedAmount) {
  if(healedAmount <= 0)return;
  std::ofstream crmDB("../resource/medcenter.csv", ios::app);
  if(crmDB.is_open()) {
    crmDB<< warrior.name << ";" << to_string(healedAmount) << ";" << std::endl;
    crmDB.close();
  }
}
