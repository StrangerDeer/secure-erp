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
      this->updateWarrior();
    }
    break;
    case 4: {
      this->deleteWarrior();
    }
    break;
    case 5: {
      this->listTopWarriors();
    }
  }
}

std::string CRMController::createWarrior(std::string &name, std::string &postPigeon, int hp, int dmg) {
  std::string id = util.generateId();
  Warrior warrior = Warrior(id, name, postPigeon, hp, dmg);
  crmdao.registerWarrior(warrior);
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
  int hp;
  int dmg;
  terminalView.printMessage("Enter a name");
  name = terminalView.getInput();
  terminalView.printMessage("Enter a pigeon name");
  postPigeon = terminalView.getInput();
  hp = terminalView.getNumberInput("Enter hp");
  dmg = terminalView.getNumberInput("Enter dmg");
  createWarrior(name, postPigeon, hp, dmg);
}


void CRMController::updateWarriorLose(string &warriorName) {
    crmdao.updateWarriorLose(warriorName);
}

void CRMController::deleteWarrior() {
  std::string name;
  terminalView.printMessage("Whomst thy wish to kill?");
  name = terminalView.getInput();
  crmdao.deleteWarriorByName(name);
}

void CRMController::updateWarrior() {
  //TODO
}

void CRMController::listTopWarriors() {
  int displayedWarriorCount = 0;
  displayedWarriorCount = terminalView.getNumberInput("How many would you like to see?");
  crmdao.listTopWarriors([this](std::vector<std::map<std::string, std::string>> resultMap, std::string label) {
    terminalView.printGeneralResults(resultMap, label);
  }, displayedWarriorCount);
}