#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <vector>
int StringCalculator::add(string numbers)
{
  if (numbers.empty())
  {
     return 0;
  }

  std::istringstream stream(numbers);
  std::string token;
  int sum = 0;
  std::vector<int> negatives;
  while (std::getline(stream, token, ','))
  {
    int number = std::stoi(token);
    if (number < 0) 
    {
      negatives.push_back(number);
    } 
    else 
    {
      sum += number;
    }
  }

  if (!negatives.empty())
  {
    std::ostringstream msg;
    msg << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) 
    {
      if (i > 0) 
      {
        msg << ", ";
      }
      msg << negatives[i];
    }
    throw std::invalid_argument(msg.str());
  }
return sum;
}
