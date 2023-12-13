#include "TerminalView.h"
#include "CRMController.h"
#include "MainController.h"

int main() {
  TerminalView terminalView = TerminalView();
  crm::CRMDAO crmdao = crm::CRMDAO();
  Util util;
  CRMController crmController = CRMController(terminalView, crmdao, util);
  std::string name = "Fer!%/(enc";
  std::string pigeon = "Hedvig";
  MainController mainController = MainController(crmController, terminalView);
  mainController.menu();
  return 0;
}
