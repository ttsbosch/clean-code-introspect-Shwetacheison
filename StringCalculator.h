#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class StringCalculator {
private:
    int parseAndSum(const std::string& numbers, std::vector<int>& negatives);
    void collectNegatives(int number, std::vector<int>& negatives);
    void throwErrorIfNegatives(const std::vector<int>& negatives);

public:
    int add(const std::string& numbers);
};

