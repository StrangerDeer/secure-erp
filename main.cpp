#include "TerminalView.h"
#include "CRMController.h"
#include "MainController.h"
#include "BattleController.h"

int main() {
  TerminalView terminalView = TerminalView();
  crm::CRMDAO crmdao = crm::CRMDAO();
  Util util;

  CRMController crmController = CRMController(terminalView, crmdao, util);
  BattleController battleController(terminalView, battle::BattleDAO(), util);

  MainController mainController = MainController(crmController, battleController, terminalView);
  mainController.menu();


  return 0;
}
