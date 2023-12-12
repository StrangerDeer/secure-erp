//
// Created by Joe Bekor on 2023. 11. 28..
//

#include "CRMDAO.h"
#include <fstream>
#include <algorithm>

using namespace crm;
bool CRMDAO::createWarrior(Warrior warrior) {
  vector<string> warriorProps = {warrior.id, warrior.name, warrior.postPigeon, to_string(warrior.battlesWon), to_string(warrior.battlesLost)};
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
    std::map<std::string,std::string> warriorObj = createWarriorObject(line);

    Warrior warrior = Warrior(warriorObj.at("Id"), warriorObj.at("Name"), warriorObj.at("PostPigeon"), stoi(warriorObj.at("BattlesWon")), stoi(warriorObj.at("BattlesLost")));
    warriors.push_back(warrior);
  }
  return warriors;
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

void CRMDAO::updateCSVFile(std::vector<Warrior> warriors) {
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
