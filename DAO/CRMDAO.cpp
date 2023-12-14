//
// Created by Joe Bekor on 2023. 11. 28..
//

#include "CRMDAO.h"
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace crm;
bool CRMDAO::createWarrior(Warrior warrior) {
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
                              stoi(warriorObj.at("BattlesLost")),
                              stoi(warriorObj.at("Exp")),
                              stoi(warriorObj.at("Level")));
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
void CRMDAO::increaseWarriorXp(const Warrior &warrior) {
  std::vector<Warrior> warriors = getWarriors();

  for(int i = 0; i <warriors.size(); i ++){
    Warrior currentWarrior = warriors.at(i);

    if(currentWarrior.name == warrior.name){
      warriors.at(i).exp += winXp;

      if(warriors.at(i).exp >= needLevelUpXp){
        increaseWarriorLevel(warriors.at(i));
        break;
      }

      updateCSVFile(warriors);
      break;
    }

  }
}
void CRMDAO::increaseWarriorLevel(const Warrior &warrior) {
  std::vector<Warrior> warriors = getWarriors();

  for(int i = 0; i <warriors.size(); i ++){
    Warrior currentWarrior = warriors.at(i);

    if(currentWarrior.name == warrior.name){
      warriors.at(i).exp = 0;
      warriors.at(i).level += 1;
      warriors.at(i).maxHp += levelUpHp;
      warriors.at(i).dmg += levelUpDmg;
      updateCSVFile(warriors);
      break;
    }

  }
}
std::string getInjuryName(int healedAmount) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  static std::vector<std::string> lightInjuryNames{"hurty hurty toenail", "ouchy finger", "paper cut", "itchy back"};
  static std::vector<std::string> injuryNames{"cut","deep cut", "bruised arm", "broken finger", "concussion"};
  static std::vector<std::string> severeInjuryNames{ "broken ribs", "severe head trauma",
                                              "how is this guy even alive lmao"};
  static std::vector<std::vector<std::string>> injuries {lightInjuryNames, injuryNames, severeInjuryNames};
  int severityLevel = healedAmount <= 3 ? 0 : healedAmount <= 5 ? 1 : 2;
  return injuries.at(severityLevel).at(std::rand() % injuries.at(severityLevel).size());
}
void CRMDAO::updateMedRecord(Warrior warrior, int healedAmount) {
  if(healedAmount < 0)return;
  std::ofstream crmDB(MED_FILE.data(), ios::app);
  if(crmDB.is_open()) {
    crmDB<< warrior.name << ";" << getInjuryName(healedAmount)
    << " healed for: " << to_string(healedAmount) << ";" << std::endl;
    crmDB.close();
  }
}
std::vector<std::string> CRMDAO::readMedHistory() {
  std::vector<std::string> result;
  std::string line;
  ifstream crmDB (MED_FILE.data());
  if(crmDB.is_open()) {
    while(getline(crmDB, line)) {
      result.push_back(line);
    }
    crmDB.close();
  }
  return result;
}
void CRMDAO::printMedicalHistory(PrintWarriors printWarriors) {
  std::vector<std::string> historyData = readMedHistory();
  std::vector<std::map<std::string, std::string>> history;
  std::string key1 = "name";
  std::string key2 = "treatment";
  int slicePos = 0;
  for(std::string line : historyData) {
    std::map<std::string, std::string> record;
    for(int i = 0, remainingKeys = 2; i < line.size(); i++) {
      if(line.at(i) == ';') {
        if(remainingKeys == 2) {
          record.insert({key1, line.substr(0, i)});
          slicePos = i + 1;
          remainingKeys = 1;
        }
        else {
          record.insert({key2, line.substr(slicePos, i)});
        }
      }
    }
    history.push_back(record);
  }
  printWarriors(history, "Medical records");
}