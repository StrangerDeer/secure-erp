//
// Created by Deer on 13/12/2023.
//

#include "BattleController.h"

void BattleController::displayMenu() const {

}

void BattleController::battle(std::string warrior1name, std::string warrior2name) {
    battleDao.battle(warrior1name, warrior2name);
}
