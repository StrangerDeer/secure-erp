#pragma once
#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

class TerminalView {
 public:
  /**
   * Prints a single message to the terminal
   *
   * @param message information to be printed
   */
  void printMessage(string_view message);

  /**
   * Prints options in standard menu format like this:
   * Main Menu:
   * (1) Store manager
   * (2) Human resources manager
   * (3) Inventory manager
   * (0) Exit program
   *
   * @param title   the title of the menu (first row)
   * @param options array of all available options in menu as Strings
   */
  void printMenu(string_view title, const string_view options[]) const;

  /**
   * Prints out any type of non-tabular data
   *
   * @param result String with result to be printed
   * @param label  label String
   */
  void printGeneralResults(string_view result, string_view label);

  /*
   /--------------------------------\
   |   id   |   product  |   type   |
   |--------|------------|----------|
   |   0    |  Bazooka   | portable |
   |--------|------------|----------|
   |   1    | Sidewinder | missile  |
   \--------------------------------/
  */

  /**
   * Prints tabular data like above example
   *
   * @param table 2 dimensional array to be printed as table
   */
  void printTable(vector<vector<string_view>> table);

  /**
   * Gets single number input from the user
   *
   * @param label the label before the user prompt
   * @return user input as integer
   */
  int getNumberInput(string_view label) const;

  /**
   * Gets a list of String inputs from the user
   *
   * @param labels array of Strings with the labels to be displayed before each prompt
   * @return array of user inputs
   */
  vector<string_view> getInputs(vector<string_view> labels);

  /**
   * Prints out error messages to terminal
   *
   * @param message String with error details
   */
  void printErrorMessage(string_view message) const;
};
