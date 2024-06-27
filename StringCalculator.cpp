#include "StringCalculator.h"
#include <sstream>
int StringCalculator::add(string numbers){
if (numbers=="") {
            return 0;
        }

        istringstream stream(numbers);
        string token;
        int sum = 0;
        while (getline(stream, token, ',')) {
            sum += stoi(token);
        }

        return sum;
}
