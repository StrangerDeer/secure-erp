#pragma once
#include <string_view>
#include <vector>
#include <iostream>
#include <map>
#include "Warrior.h"

using namespace std;

namespace crm {
const static int ID_TABLE_INDEX{0};
const static int NAME_TABLE_INDEX{1};
const static int POST_PIGEON_TABLE_INDEX{2};
const static int BATTLES_WON_TABLE_INDEX{3};
const static int BATTLES_LOST_TABLE_INDEX{4};
constexpr string_view DATA_FILE{"../resource/crm.csv"};
static vector<string_view> headers = {"Id", "Name", "PostPigeon", "BattlesWon", "BattlesLost"};

class CRMDAO {
 public:
  bool createWarrior(Warrior warrior);
  std::vector<Warrior> getWarriors();
 private:
  std::vector<std::string> readWarriors();
  std::map<std::string, std::string> createWarriorObject(std::string line);
};
}