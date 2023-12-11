#pragma once
#include <vector>
#include <string_view>
#include "CRMController.h"
#include "../ui/TerminalView.h"

using namespace std;

static string_view MAIN_OPTIONS[]{
    "Exit program",
    "Customer Relationship Management (CRM)",
    "Sales",
    "Human Resources"
};

class MainController {
 private:
  const CRMController crmController;
  const TerminalView terminalView;
 public:
  MainController(const CRMController &crmController,
                 const TerminalView &terminalView)
      : crmController(crmController),
        terminalView(terminalView) {};

  void menu();

  bool invokeMenuItem(int selectedMenu);
};
