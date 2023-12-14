//
// Created by Joe Bekor on 2023. 11. 28..
//

#include "CRMDAO.h"
#include <fstream>
#include <algorithm>
#include <ctime>
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
  int healedAmount = warriors.at(i).maxHp - warrior.currentHP;
  warriors.at(index).currentHP = warrior.maxHp;

  updateCSVFile(warriors);
  updateMedRecord(warrior, healedAmount);
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
std::string getInjuryName(int healedAmount) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  static std::vector<std::string> lightInjuryNames{"hurty hurty toenail", "ouchy finger"};
  static std::vector<std::string> injuryNames{"cut","deep cut", "bruised arm"};
  static std::vector<std::string> severeInjuryNames{ "broken rib", "severe head trauma",
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