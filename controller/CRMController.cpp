#include "CRMController.h"

void CRMController::displayMenu() const {
  terminalView.printMenu("Warrior Stuff", CRM_OPTIONS);
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
  crmdao.getWarriors();
}