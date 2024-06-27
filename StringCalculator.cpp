#include "StringCalculator.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <vector>

// Extracts delimiter and updates numbers string
std::pair<std::string, std::string> extractDelimiterAndNumbers(const std::string& numbers)
{
    std::string delimiter = ",";
    std::string numbersPart = numbers;
    if (numbers.substr(0, 2) == "//")
    {
        size_t delimiterEndPos = numbers.find('\n');
        delimiter = numbers.substr(2, delimiterEndPos - 2);
        numbersPart = numbers.substr(delimiterEndPos + 1);
    }
    return {delimiter, numbersPart};
}

// Replaces all occurrences of the custom delimiter in the numbers string with a common delimiter
std::string replaceDelimiter(const std::string& numbersPart, const std::string& delimiter)
{
    std::string modifiedNumbers = numbersPart;
    size_t pos = 0;
    while ((pos = modifiedNumbers.find(delimiter, pos)) != std::string::npos)
    {
        modifiedNumbers.replace(pos, delimiter.length(), ",");
        pos += delimiter.length(); // Adjust for the length of the delimiter
    }
    return modifiedNumbers;
}

int StringCalculator::add(const std::string& numbers)
{
    if (numbers.empty())
    {
        return 0;
    }

    auto [delimiter, numbersPart] = extractDelimiterAndNumbers(numbers);
    numbersPart = replaceDelimiter(numbersPart, delimiter);

    validateInputFormat(numbersPart);

    std::vector<int> negatives;
    int sum = parseAndSum(numbersPart, negatives);
    throwErrorIfNegatives(negatives);

    return sum;
}

// Other methods remain unchanged

void StringCalculator::validateInputFormat(const std::string& numbers)
{
    if (numbers.back() == ',' || numbers.back() == '\n')
    {
        throw std::invalid_argument("Invalid input format");
    }
}

std::vector<int> StringCalculator::parseNumbers(const std::string& numbers)
{
    std::string modifiedNumbers = numbers;
    std::replace(modifiedNumbers.begin(), modifiedNumbers.end(), '\n', ','); // Replace newlines with commas
    std::istringstream stream(modifiedNumbers);
    std::string token;
    std::vector<int> parsedNumbers;

    while (std::getline(stream, token, ','))
    {
        if (!token.empty())
        { // Skip empty tokens
            int number = std::stoi(token);
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
        if (number > 1000)
        {
            continue; // Skip numbers greater than 1000
        }
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
