#include "StringCalculator.h"
#include <algorithm>
#include <numeric>
#include <regex>

int StringCalculator::add(const std::string& numbers)
{
    if (numbers.empty())
    {
        return 0;
    }

    std::vector<int> negatives;
    int sum = parseAndSum(numbers, negatives);
    throwErrorIfNegatives(negatives);

    return sum;
}

std::vector<int> StringCalculator::parseNumbers(const std::string& numbers)
{
    std::vector<int> parsedNumbers;
    std::regex numberPattern("(-?\\d+)");
    auto numbersBegin = std::sregex_iterator(numbers.begin(), numbers.end(), numberPattern);
    auto numbersEnd = std::sregex_iterator();

    for (std::sregex_iterator i = numbersBegin; i != numbersEnd; ++i)
    {
        std::smatch match = *i;
        parsedNumbers.push_back(std::stoi(match.str()));
    }

    return parsedNumbers;
}

int StringCalculator::parseAndSum(const std::string& numbers, std::vector<int>& negatives)
{
    std::vector<int> parsedNumbers = parseNumbers(numbers);
    int sum = 0;
    for (int number : parsedNumbers)
    {
        collectNegatives(number, negatives);
        sum += std::max(number, 0); // Only add non-negative numbers
    }
    return sum;
}

void StringCalculator::collectNegatives(int number, std::vector<int>& negatives)
{
    if (number < 0)
    {
        negatives.push_back(number);
    }
}

void StringCalculator::throwErrorIfNegatives(const std::vector<int>& negatives)
{
    if (!negatives.empty())
    {
        auto errorMessage = std::accumulate(
            std::next(negatives.begin()),
            negatives.end(),
            "negatives not allowed: " + std::to_string(negatives[0]), // Initial value
            [](const std::string& acc, int n) { return acc + ", " + std::to_string(n); });
        throw std::runtime_error(errorMessage);
    }
}
