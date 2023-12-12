#pragma once

#include <string_view>
#include "../ui/TerminalView.h"
#include "../model/Warrior.h"
#include "../DAO/CRMDAO.h"
using namespace std;

const static string_view CRM_OPTIONS[]{
    "Back to main menu",
    "List customers",
    "Add new customer",
    "Update customer",
    "Remove customer",
    "Subscribed customer emails"
};

class CRMController {
 public:
  CRMController(const TerminalView &terminalView, crm::CRMDAO crmdao, Util util) : terminalView(terminalView), crmdao(crmdao), util(util) {
  };
  void displayMenu() const;
  std::string createWarrior(std::string& name, std::string& postPigeon);
  void getWarriors();
  void deleteWarrior(std::string& warriorName);
 private:
  const TerminalView terminalView;
  crm::CRMDAO crmdao;
  Util util;
};
