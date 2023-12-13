//
// Created by Deer on 13/12/2023.
//

#include "BattleDAO.h"

void battle::BattleDAO::battle(std::string warrior1name, std::string warrior2name) {
    Warrior warrior1 = findWarriorByName(warrior1name);
    Warrior warrior2 = findWarriorByName(warrior2name);

    while(warrior1.maxHp > 0 && warrior2.maxHp > 0){
        warrior1.fight(warrior2);

        if(warrior2.maxHp > 0){
            warrior2.fight(warrior1);
        }
    }

    if(warrior1.maxHp > 0){
        updateWarriorWin(warrior1.name);
        updateWarriorLose(warrior2.name);
    }else{
        updateWarriorWin(warrior2.name);
        updateWarriorLose(warrior1.name);
    }
}

Warrior battle::BattleDAO::findWarriorByName(std::string name) {
    for(const auto& warrior : getWarriors()){
        if(warrior.name == name){
            return warrior;
        }
    }
}
