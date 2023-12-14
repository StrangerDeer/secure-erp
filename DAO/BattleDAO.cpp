//
// Created by Deer on 13/12/2023.
//

#include <fstream>
#include "BattleDAO.h"

void battle::BattleDAO::battle(std::string warrior1name, std::string warrior2name) {
    Warrior warrior1 = findWarriorByName(warrior1name);
    Warrior warrior2 = findWarriorByName(warrior2name);
    int round = 1;

    while(warrior1.currentHP > 0 && warrior2.currentHP > 0){
        std::cout << "ROUND: " << to_string(round) << endl;
        warrior1.fight(warrior2);
        std::cout << warrior1.name << " hits " << warrior2.name << endl;

        if(warrior2.currentHP > 0){
            warrior2.fight(warrior1);
            std::cout << warrior2.name << " hits " << warrior1.name << endl;
        }
        round++;
    }

    decreaseWarriorHp(warrior1);
    decreaseWarriorHp(warrior2);

    if(warrior1.currentHP > 0){
        updateWarriorWin(warrior1.name);
        updateWarriorLose(warrior2.name);
        writeBattleEnd(warrior1.name, warrior2.name, to_string(round));
        cout << "WIN: " << warrior1.name << endl;
        cout << "Lose: " << warrior2.name << endl;
    }else{
        updateWarriorWin(warrior2.name);
        updateWarriorLose(warrior1.name);
        writeBattleEnd(warrior2.name, warrior1.name, to_string(round - 1));
        cout << "WIN: " << warrior2.name << endl;
        cout << "Lose: " << warrior1.name << endl;
    }
}

Warrior battle::BattleDAO::findWarriorByName(const std::string& name) {
    for(const auto& warrior : getWarriors()){
        if(warrior.name == name){
            return warrior;
        }
    }
}

void battle::BattleDAO::writeBattleEnd(std::string name1, std::string name2, std::string round) {
    std::string messageTemplate = "MATCH:" + name1 + "vs" + name2 + ";" + "WIN:" + name1 + "LOST:" + name2 + "ROUNDS:" + round;
    std::ofstream file(DATA_FILE.data(), ios::app);
    if(file.is_open()) {

        file << messageTemplate;
        file << std::endl;
    }
        file.close();
}

void battle::BattleDAO::cure(std::string name) {
  Warrior warrior = findWarriorByName(name);
  makeWarriorHpMax(warrior);
}
