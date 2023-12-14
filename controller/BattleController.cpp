//
// Created by Deer on 13/12/2023.
//

#include "BattleController.h"

void BattleController::displayMenu() {
  terminalView.printMenu("Battle stuff", BATTLE_OPTIONS);
  int menuItemIndex = terminalView.getNumberInput("Please select a menu item!");
  switch(menuItemIndex) {
    case 0: {
      return;
    }
    break;
    case 1: {
      this->setupBattle();
    }
      break;
    case 2: {
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

void BattleController::battle(std::string warrior1name, std::string warrior2name) {
    battleDao.battle(warrior1name, warrior2name);
}
void BattleController::cure(std::string name) {
  battleDao.cure(name);
}
void BattleController::setupBattle() {
  std::string name1;
  std::string name2;
  terminalView.printMessage("Enter the name of the first warrior");
  name1 = terminalView.getInput();
  terminalView.printMessage("Enter the name of the second warrior");
  name2 = terminalView.getInput();
  battle(name1, name2);
}