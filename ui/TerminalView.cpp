#include <map>
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
void TerminalView::printGeneralResults(std::vector<std::map<std::string, std::string>> resultMap, std::string label) {
  std::cout << label << std::endl;
  for(auto value : resultMap.at(0)) {
    std::cout <<" | " << value.first;
    if(value.second.size() > value.first.size()) {
      std::string padding = "";
      for(int pad = 0; pad < value.second.size() - value.first.size(); pad++) {
        padding += " ";
      }
      std::cout << padding;
    }
  }
  std::cout<<" |"<<std::endl;
  for(int i = 0; i < resultMap.size(); i++) {
    for(auto value : resultMap.at(i)) {
      std::cout<<" | " << value.second;
      if(value.second.size() < value.first.size()) {
        std::string padding = "";
        for(int pad = 0; pad < value.first.size() - value.second.size(); pad++) {
          padding += " ";
        }
        std::cout << padding;
      }
    }
    std::cout<<std::endl;
  }
}

void TerminalView::printTable(vector<vector<string_view>> table) {
  //throw exception();
}

int TerminalView::getNumberInput(string_view label) const {
  std::cout << label << std::endl;
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
