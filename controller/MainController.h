#pragma once
#include <vector>
#include <string_view>
#include "CRMController.h"
#include "../ui/TerminalView.h"
#include "BattleController.h"

using namespace std;

static string_view MAIN_OPTIONS[]{
    "Exit program",
    "Warrior Management",
    "Battle Management",
    "Medical Center",
    ""
};

class MainController {
 private:
   CRMController crmController;
   BattleController battleController;
   TerminalView terminalView;
 public:
  MainController(const CRMController &crmController, BattleController battleController,
                 const TerminalView &terminalView)
      : crmController(crmController), battleController(battleController),
        terminalView(terminalView) {};

  void menu();

  bool invokeMenuItem(int selectedMenu);
};
