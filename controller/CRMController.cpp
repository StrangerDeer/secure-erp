#include "CRMController.h"

void CRMController::displayMenu() {
  terminalView.printMenu("Warrior Stuff", CRM_OPTIONS);
  int menuItemIndex = terminalView.getNumberInput("Please select a menu item!");
  switch(menuItemIndex) {
    case 1: {
      this->getWarriors();
    }
    break;
  }
}

std::string CRMController::createWarrior(std::string &name, std::string &postPigeon) {
  std::string id = util.generateId();
  Warrior warrior = Warrior(id, name, postPigeon);
  crmdao.createWarrior(warrior);
  return "cool";
}

void CRMController::deleteWarriorByName(std::string &warriorName) {
    crmdao.deleteWarriorByName(warriorName);
}

void CRMController::getWarriors() {
  crmdao.printWarriors([this](std::vector<std::map<std::string, std::string>> resultMap, std::string label) {
    terminalView.printGeneralResults(resultMap, label);
  });
}