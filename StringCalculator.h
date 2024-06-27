#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <regex>

class StringCalculator
{
  public:
    int add(const std::string& numbers);

  private:
    std::vector<int> parseNumbers(const std::string& numbers);
    int parseAndSum(const std::string& numbers, std::vector<int>& negatives);
    void collectNegatives(int number, std::vector<int>& negatives);
    void throwErrorIfNegatives(const std::vector<int>& negatives);
};

#endif // STRINGCALCULATOR_H
