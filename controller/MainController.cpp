#include "MainController.h"

bool MainController::invokeMenuItem(int selectedMenu) {
  switch (selectedMenu) {
    case 0:return false;
    case 1:
      crmController.displayMenu();
      break;
    case 2:
      battleController.displayMenu();
      break;
    case 3:
      medicalController.displayMenu();
    default:
      terminalView.printErrorMessage("Invalid menu item selected!\n");
      break;
  }
  return true;
}
void MainController::menu() {
  bool isRunning = true;
  while (isRunning) {
    terminalView.printMenu("Main menu", MAIN_OPTIONS);
    int menuItemIndex = terminalView.getNumberInput("Please select a menu item!");
    isRunning = invokeMenuItem(menuItemIndex);
  }
}
