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
    const static int ID_TABLE_INDEX{0};
    const static int NAME_TABLE_INDEX{1};
    const static int POST_PIGEON_TABLE_INDEX{2};
    const static int BATTLES_WON_TABLE_INDEX{3};
    const static int BATTLES_LOST_TABLE_INDEX{4};
    constexpr string_view DATA_FILE{"../resource/battle.csv"};
    static vector<string_view> headers = {"Id", "Name", "PostPigeon", "BattlesWon", "BattlesLost"};

class BattleDAO : private crm::CRMDAO{
  public:
        void battle(std::string warrior1name, std::string warrior2name);
        void cure(std::string name);

  private:
    Warrior findWarriorByName(const std::string& name);
    void writeBattleEnd(std::string name1, std::string name2, std::string round);
    };
};


#endif //SECURE_ERP_CPP_BATTLEDAO_H
