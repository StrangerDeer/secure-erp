#include "TerminalView.h"

void TerminalView::printMessage(string_view message) {
  throw exception();
}

void TerminalView::printMenu(string_view title, const string_view options[]) const {
  throw exception();
}

void TerminalView::printGeneralResults(string_view result, string_view label) {
  throw exception();
}

void TerminalView::printTable(vector<vector<string_view>> table) {
  throw exception();
}

int TerminalView::getNumberInput(string_view label) const {
  return 0;
}

vector<string_view> TerminalView::getInputs(vector<string_view> labels) {
  return vector<string_view>();
}

void TerminalView::printErrorMessage(string_view message) const {
  throw exception();
}
