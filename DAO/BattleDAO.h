//
// Created by Deer on 13/12/2023.
//

#ifndef SECURE_ERP_CPP_BATTLEDAO_H
#define SECURE_ERP_CPP_BATTLEDAO_H

#include <string_view>
#include <vector>
#include "CRMDAO.h"

using namespace std;
using crm::CRMDAO;

namespace battle {
    constexpr string_view DATA_FILE{"../resource/battle.csv"};

class BattleDAO : private crm::CRMDAO {
  public:
        void battle(std::string warrior1name, std::string warrior2name);
        void cure(std::string name);

  private:
    Warrior findWarriorByName(const std::string& name);
    void writeBattleEnd(std::string name1, std::string name2, std::string round);
    };
};


#endif //SECURE_ERP_CPP_BATTLEDAO_H
