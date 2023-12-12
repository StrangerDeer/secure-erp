#include "CRMController.h"

void CRMController::displayMenu() const {
  terminalView.printMenu("Customer Relationship", CRM_OPTIONS);
}

std::string CRMController::createWarrior(std::string &name, std::string &postPigeon) {
  std::string id = util.generateId();
  Warrior warrior = Warrior(id, name, postPigeon);
  crmdao.createWarrior(warrior);
  return "cool";
}

void CRMController::deleteWarrior(std::string &warriorName) {
    crmdao.deleteWarrior(warriorName);
}

void CRMController::getWarriors() {
  crmdao.getWarriors();
}