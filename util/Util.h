#pragma once
#include <cstring>
#include <string_view>
#include <random>

using namespace std;

namespace {
constexpr string_view lettersUppercase{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
constexpr string_view lettersLowercase = "abcdefghijklmnopqrstuvwxyz";
constexpr string_view digits = "0123456789";
}

class Util {

 public:
  Util() {
    std::uniform_real_distribution<double> dist_c(0.0, 1.0);
    this->dist = dist_c;
  }


  int getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    double random_value = dist(mt);
    return (random_value * (max - min)) + min;
  }

  string randomChars(string_view chars, int amount) {
    string randomChars{""};
    for (int i = 0; i < amount; i++) {
      int randomIndex = getRandomInt(0, chars.length());
      randomChars.push_back(chars.at(randomIndex));
    }
    return randomChars;
  }

  string shuffle(string original) {
    char *chars = new char[original.length() + 1];
    strcpy(chars, string(original).c_str());
    for (int i = 0; i < original.length() - 1; i++) {
      int j = getRandomInt(i, original.length());
      char temp = chars[i];
      chars[i] = chars[j];
      chars[j] = temp;
    }
    return {chars};
  }

  string generateId() {
    int smallLettersAmount = 4;
    int capitalLettersAmount = 2;
    int digitsAmount = 2;
    int specialCharsAmount = 2;
    string allowedSpecialChars = "_+-!";
    string pool = {randomChars(lettersUppercase, capitalLettersAmount)
        + randomChars(lettersLowercase, smallLettersAmount)
        + randomChars(digits, digitsAmount) + randomChars(allowedSpecialChars, specialCharsAmount)};
    return shuffle(pool);
  }

  string generateUniqueId(vector<string> ids) {
    while (true) {
      bool foundIdentical = false;
      string newId = generateId();
      for (string id : ids) {
        if (std::equal(newId.begin(), newId.end(),id.begin(), id.end())) {
          foundIdentical = true;
          break;
        }
      }
      if (!foundIdentical)
        return newId;
    }
  }

 private:

  std::uniform_real_distribution<double> dist;
};
