#pragma once
#include <vector>
#include <string_view>
#include "CRMController.h"
#include "../ui/TerminalView.h"
#include "BattleController.h"
#include "MedicalController.h"
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
   MedicalController medicalController;
   TerminalView terminalView;
 public:
  MainController(const MedicalController medicalController, const CRMController &crmController, BattleController battleController,
                 const TerminalView &terminalView)
      : medicalController(medicalController), crmController(crmController), battleController(battleController),
        terminalView(terminalView) {};

  void menu();

  bool invokeMenuItem(int selectedMenu);
};
