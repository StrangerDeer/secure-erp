#include "TerminalView.h"
#include "CRMController.h"
#include "MainController.h"

int main() {
  TerminalView terminalView = TerminalView();
  CRMController crmController = CRMController(terminalView);

  MainController mainController = MainController(crmController, terminalView);
  return 0;
}
