#pragma once

#include <string_view>
#include "../ui/TerminalView.h"
#include "../model/Warrior.h"
#include "../DAO/CRMDAO.h"
using namespace std;

static string_view CRM_OPTIONS[]{
    "Back to main menu",
    "List warriors",
    "Add new warrior",
    "Update warrior",
    "Absolutely murder warrior",
    "Promising warriors",
    ""
};

class CRMController {
 public:
  CRMController(const TerminalView &terminalView, crm::CRMDAO crmdao, Util util) : terminalView(terminalView), crmdao(crmdao), util(util) {
  };
  void displayMenu();
  std::string createWarrior(std::string& name, std::string& postPigeon, int hp, int dmg);

  void getWarriors();
  void deleteWarriorByName(std::string& warriorName);
  void addWarrior();
  void updateWarriorsWin(std::string& warriorName);
  void updateWarriorLose(std::string& warriorName);
  void deleteWarrior();
  void updateWarrior();
  void listTopWarriors();

 private:
  TerminalView terminalView;
  crm::CRMDAO crmdao;
  Util util;
};
