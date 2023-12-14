//
// Created by Deer on 13/12/2023.
//

#include "BattleController.h"

void BattleController::displayMenu()  {
  terminalView.printMenu("Battle stuff", BATTLE_OPTIONS);
  int menuItemIndex = terminalView.getNumberInput("Please select a menu item!");
  switch(menuItemIndex) {
    case 1: {
      this->setupBattle();
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

void BattleController::battle(std::string warrior1name, std::string warrior2name) {
    battleDao.battle(warrior1name, warrior2name);
}
void BattleController::cure(std::string name) {
  battleDao.cure(name);
}
