//
// Created by User on 2023. 12. 14..
//

#include "MedicalController.h"
void MedicalController::displayMenu() {
  terminalView.printMenu("Medical Center", MEDICAL_OPTIONS);
  int menuItemIndex = terminalView.getNumberInput("Please select a menu item!");
  switch(menuItemIndex) {
    case 0: {
      return;
    }
      break;
    case 1: {
      this->showMedicalHistory();
    }
      break;
    case 2: {
      this->healWarrior();
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
void MedicalController::showMedicalHistory() {

}
void MedicalController::healWarrior() {
  std::string name;
  terminalView.printMessage("Whomst thy wish to heal?");
  name = terminalView.getInput();
  battleDao.cure(name);
}
