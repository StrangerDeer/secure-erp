#include "CRMController.h"

void CRMController::displayMenu() {
  terminalView.printMenu("Warrior Stuff", CRM_OPTIONS);
  int menuItemIndex = terminalView.getNumberInput("Please select a menu item!");
  switch(menuItemIndex) {
    case 1: {
      this->getWarriors();
    }
    break;
    case 2: {
      this->addWarrior();
    }
    break;
    case 3: {
      std::cout<< "Still in development"<<std::endl;
    }
    break;
    case 4: {
      std::cout<<"Still in development"<<std::endl;
    }
    break;
    case 5: {
      std::cout<<"Still in development"<<std::endl;
    }
  }
}

std::string CRMController::createWarrior(std::string &name, std::string &postPigeon, int hp, int dmg) {
  std::string id = util.generateId();
  Warrior warrior = Warrior(id, name, postPigeon, hp, dmg);
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
void CRMController::addWarrior() {
  std::string name;
  std::string postPigeon;
  terminalView.printMessage("Enter a name");
  name = terminalView.getInput();
  terminalView.printMessage("Enter a pigeon name");
  postPigeon = terminalView.getInput();
  createWarrior(name, postPigeon);
}
void CRMController::updateWarriorsWin(std::string& warriorName) {
    crmdao.updateWarriorWin(warriorName);
}

void CRMController::updateWarriorLose(string &warriorName) {
    crmdao.updateWarriorLose(warriorName);
}
