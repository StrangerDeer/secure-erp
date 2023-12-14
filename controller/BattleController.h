//
// Created by Deer on 13/12/2023.
//

#ifndef SECURE_ERP_CPP_BATTLECONTROLLER_H
#define SECURE_ERP_CPP_BATTLECONTROLLER_H


#include "TerminalView.h"
#include "Util.h"
#include "../DAO/BattleDAO.h"

class BattleController {
public:
    BattleController(const TerminalView &terminalView, battle::BattleDAO battleDao, Util util) : terminalView(terminalView), battleDao(battleDao), util(util) {
    };
    void displayMenu() const;
    void battle(std::string warrior1name, std::string warrior2name);
    void cure(std::string name);
private:
    const TerminalView terminalView;
    battle::BattleDAO battleDao;
    Util util;
};


#endif //SECURE_ERP_CPP_BATTLECONTROLLER_H
