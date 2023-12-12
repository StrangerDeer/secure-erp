#include "TerminalView.h"

void TerminalView::printMessage(string_view message) {
  std::cout<<message<<std::endl;
}

void TerminalView::printMenu(string_view title, string_view* options) const {
  std::cout<<title<<std::endl;
  for(int i = 0; options[i].length(); i++) {
    std::string_view option = options[i];
    std::cout<< "(" + to_string(i) + ")" << option << std::endl;
  }
}

void TerminalView::printGeneralResults(string_view result, string_view label) {
  //throw exception();
}

void TerminalView::printTable(vector<vector<string_view>> table) {
  //throw exception();
}

int TerminalView::getNumberInput(string_view label) const {
  int input = 0;
  std::cin >> input;
  return input;
}

vector<string_view> TerminalView::getInputs(vector<string_view> labels) {
  return vector<string_view>();
}

void TerminalView::printErrorMessage(string_view message) const {
  //throw exception();
}
