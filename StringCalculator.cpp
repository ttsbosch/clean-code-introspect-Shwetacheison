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
    // Check for disallowed input pattern "1,\n"
    if (std::regex_search(numbers, std::regex(",\\n$")))
    {
        throw std::invalid_argument("Input ending with ',\\n' is not allowed.");
    }

    std::vector<int> parsedNumbers;
    std::regex re("[\\n,]"); // Split on newline or comma
    std::sregex_token_iterator it(numbers.begin(), numbers.end(), re, -1);
    std::sregex_token_iterator reg_end;

    for (; it != reg_end; ++it)
    {
        if (!it->str().empty()) // Ignore empty tokens
        {
            parsedNumbers.push_back(std::stoi(it->str()));
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
