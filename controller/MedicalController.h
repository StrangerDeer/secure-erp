//
// Created by User on 2023. 12. 14..
//

#ifndef SECURE_ERP_CPP_CONTROLLER_MEDICALCONTROLLER_H_
#define SECURE_ERP_CPP_CONTROLLER_MEDICALCONTROLLER_H_
#include <string_view>
#include "../ui/TerminalView.h"
#include "../model/Warrior.h"
#include "../DAO/CRMDAO.h"
#include "../DAO/BattleDAO.h"
static std::string_view MEDICAL_OPTIONS[]{
    "Back to main menu",
    "Show medical history",
    "Heal warrior",
    ""
};
class MedicalController {
 public:
  MedicalController(const TerminalView &terminalView, const battle::BattleDAO &battle_dao, const CRMDAO &crm_dao)
      : battleDao(battle_dao), crmDao(crm_dao) {}
  void displayMenu();
 private:
  battle::BattleDAO battleDao;
  crm::CRMDAO crmDao;
  TerminalView terminalView;
  void showMedicalHistory();
  void healWarrior();
};

#endif //SECURE_ERP_CPP_CONTROLLER_MEDICALCONTROLLER_H_
