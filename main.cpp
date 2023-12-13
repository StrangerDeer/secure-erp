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

  std::string name1 = "Ferenc";
  std::string pigeon1 = "Hedvig";
  std::string name2 = "Jozsi";
  std::string pigeon2 = "Hedvig";


    MainController mainController = MainController(crmController, terminalView);
  mainController.menu();
  battleController.battle(name1, name2);


  return 0;
}
