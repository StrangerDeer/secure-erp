#pragma once
#include <string_view>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include "Warrior.h"
#include "../ui/TerminalView.h"
using namespace std;
namespace crm {
const int ID_HEADER_INDEX(0);
const int NAME_HEADER_INDEX(1);
const int PIGEON_HEADER_INDEX(2);
const int MAX_HP_HEADER_INDEX(3);
const int CURRENT_HP_HEADER_INDEX(4);
const int DMG_HEADER_INDEX(5);
const int BATTLES_WON_HEADER_INDEX(6);
const int BATTLES_LOST_HEADER_INDEX(7);
const int EXP_HEADER_INDEX(8);
const int LEVEL_HEADER_INDEX(9);
constexpr string_view DATA_FILE{"../resource/crm.csv"};
constexpr string_view MED_FILE{"../resource/medcenter.csv"};
static vector<string> headers = {"Id", "Name", "PostPigeon", "MaxHp", "CurrentHp" ,"DMG", "BattlesWon", "BattlesLost", "Exp", "Level"};

class CRMDAO {
 public:
  using PrintWarriors = std::function<void(std::vector<std::map<std::string, std::string>>, std::string)>;
  bool registerWarrior(const Warrior& warrior);
  std::vector<Warrior> getWarriors();
  void deleteWarriorByName(const std::string& warriorName);
  void printWarriors(PrintWarriors printWarriors);
  void listTopWarriors(PrintWarriors printWarriors, int count);
  void printMedicalHistory(PrintWarriors printWarriors);

 protected:
  void updateWarriorWin(const Warrior& warrior);
  void updateWarriorLose(const Warrior& warrior);
  void decreaseWarriorHp(const Warrior& warrior);
  void makeWarriorHpMax(const Warrior& warrior);
  void increaseWarriorXp(const Warrior& warrior);

 private:
  const char valueSeparator = ';';
  const char mapSeparator = ':';
  const int winXp{20};
  const int needLevelUpXp{100};
  const int levelUpDmg{5};
  const int levelUpHp{10};
  bool writeWarriorToCSV(vector<string> warriorProps) const;
  std::vector<std::string> readWarriors();
  std::map<std::string, std::string> createWarriorObject(const std::string& line) const;
  std::vector<std::string> splitLines(const std::string& line) const;
  int findWarriorIndexByName(std::vector<Warrior> warriors, const std::string& name);
  void increaseWarriorLevelWithIndex(std::vector<Warrior> warriors, int index);
  void updateCSVFile(const std::vector<Warrior>& warriors);
  void updateMedRecord(Warrior warrior, int healedAmount);
  void orderByWinRatio(std::vector<std::map<std::string, std::string>>& warriors);
  bool compareWinRatio(const std::map<std::string, std::string> &warrior1,
                       const std::map<std::string, std::string> &warrior2);
  std::vector<std::string> readMedHistory();
};
}