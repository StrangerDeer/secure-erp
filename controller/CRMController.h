#pragma once

#include <string_view>
#include "../ui/TerminalView.h"

using namespace std;

const static string_view CRM_OPTIONS[]{
    "Back to main menu",
    "List customers",
    "Add new customer",
    "Update customer",
    "Remove customer",
    "Subscribed customer emails"
};

class CRMController {
 public:
  CRMController(const TerminalView &terminalView) : terminalView(terminalView) {};
  void displayMenu() const;
 private:
  const TerminalView terminalView;
};
