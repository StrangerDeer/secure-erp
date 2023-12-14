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
const static int ID_TABLE_INDEX{0};
const static int NAME_TABLE_INDEX{1};
const static int POST_PIGEON_TABLE_INDEX{2};
const static int BATTLES_WON_TABLE_INDEX{3};
const static int BATTLES_LOST_TABLE_INDEX{4};
constexpr string_view DATA_FILE{"../resource/crm.csv"};
static vector<string_view> headers = {"Id", "Name", "PostPigeon", "MaxHp", "CurrentHp" ,"DMG", "BattlesWon", "BattlesLost", "Exp", "Level"};
constexpr string_view MED_FILE{"../resource/medcenter.csv"};
class CRMDAO {
 public:
  using PrintWarriors = std::function<void(std::vector<std::map<std::string, std::string>>, std::string)>;
  bool createWarrior(Warrior warrior);
  std::vector<Warrior> getWarriors();
  void deleteWarriorByName(std::string warriorName);
  void printWarriors(PrintWarriors printWarriors);
  void updateWarriorWin(std::string warriorName);
  void updateWarriorLose(std::string warriorName);
  void listTopWarriors(PrintWarriors printWarriors, int count);
  void printMedicalHistory(PrintWarriors printWarriors);
 protected:
  void decreaseWarriorHp(const Warrior& warrior);
  void makeWarriorHpMax(const Warrior& warrior);
  void increaseWarriorXp(const Warrior& warrior);
  void increaseWarriorLevel(const Warrior& warrior);
  void orderByWinRatio(std::vector<std::map<std::string, std::string>>& wariors);
  bool compareWinRatio(const std::map<std::string, std::string>& warrior1, const std::map<std::string, std::string>& warrior2);
 private:
  int winXp{20};
  int needLevelUpXp{100};
  int levelUpDmg{5};
  int levelUpHp{10};
  std::vector<std::string> readWarriors();
  std::map<std::string, std::string> createWarriorObject(std::string line);
  void updateCSVFile(const std::vector<Warrior>& warriors);
  void updateMedRecord(Warrior warrior, int healedAmount);
  std::vector<std::string> readMedHistory();
};
}