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
    std::istringstream stream(numbers);
    std::string token;
    std::vector<int> parsedNumbers;
    while (std::getline(stream, token, ','))
    {
        int number = std::stoi(token);
        if (number <= 1000) // Ignore numbers greater than 1000
        {
            parsedNumbers.push_back(number);
        }
    }
    return parsedNumbers;
}

int StringCalculator::parseAndSum(const std::string& numbers, std::vector<int>& negatives)
{
    std::vector<int> parsedNumbers = parseNumbers(numbers);
    int sum = 0;
    for (int number : parsedNumbers)
    {
        if (number < 0)
        {
            negatives.push_back(number);
        }
        else
        {
            sum += number; // Numbers greater than 1000 are already filtered out
        }
    }
    throwErrorIfNegatives(negatives);
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
