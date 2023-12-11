#include "CRMController.h"

void CRMController::displayMenu() const {
  terminalView.printMenu("Customer Relationship", CRM_OPTIONS);
}

