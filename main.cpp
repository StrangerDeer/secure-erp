#include "TerminalView.h"
#include "CRMController.h"
#include "MainController.h"

int main() {
  TerminalView terminalView = TerminalView();
  crm::CRMDAO crmdao = crm::CRMDAO();
  Util util;
  CRMController crmController = CRMController(terminalView, crmdao, util);
  std::string name = "1";
  std::string pigeon = "galamb";
  MainController mainController = MainController(crmController, terminalView);
  mainController.menu();
  crmController.createWarrior(name, pigeon);
  return 0;
}
