#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <algorithm>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

class StringCalculator
{
  public:
    int add(const std::string& numbers);

  private:
    std::pair<std::string, std::string> extractDelimiterAndNumbers(const std::string& numbers);
    std::string replaceDelimiter(const std::string& numbersPart, const std::string& delimiter);
    void validateInputFormat(const std::string& numbers);
    std::vector<int> parseNumbers(const std::string& numbers);
    int parseAndSum(const std::string& numbers, std::vector<int>& negatives);
    bool isValidNumber(int number, std::vector<int>& negatives);
    void collectNegatives(int number, std::vector<int>& negatives);
    void throwErrorIfNegatives(const std::vector<int>& negatives);
};

#endif // STRINGCALCULATOR_H
