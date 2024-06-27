#include "StringCalculator.h"

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
        parsedNumbers.push_back(number);
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
        std::ostringstream msg;
        msg << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i)
        {
            msg << (i > 0 ? ", " : "") << negatives[i];
        }
        throw std::invalid_argument(msg.str());
    }
}
