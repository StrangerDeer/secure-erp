//
// Created by Deer on 13/12/2023.
//

#ifndef SECURE_ERP_CPP_BATTLECONTROLLER_H
#define SECURE_ERP_CPP_BATTLECONTROLLER_H


#include "TerminalView.h"
#include "Util.h"
#include "../DAO/BattleDAO.h"
static string_view BATTLE_OPTIONS[]{
    "Back to main menu",
    "Battle",
    ""
};
class BattleController {
public:
    BattleController(const TerminalView &terminalView, battle::BattleDAO battleDao, Util util) : terminalView(terminalView), battleDao(battleDao), util(util) {
    };
    void displayMenu();
    void battle(std::string warrior1name, std::string warrior2name) ;
private:
    const TerminalView terminalView;
    void setupBattle();
    battle::BattleDAO battleDao;
    Util util;
};


#endif //SECURE_ERP_CPP_BATTLECONTROLLER_H
