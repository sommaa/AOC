#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// read from cin the numbers in a vector 1\n2\n3\n...
std::vector<std::string> read_numbers() {
    std::vector<std::string> numbers;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        numbers.push_back(line);
    }
    return numbers;
}

int main() {
    auto numbers = read_numbers();
    long long sum = 0;

    for (const auto& num : numbers) {
        if (num.empty())
            continue;

        std::string result;

        // find iterator to the first largest digit (global max)
        auto it_max = std::max_element(num.begin(), num.end());

        // case 1: largest digit is NOT the last char
        if (it_max + 1 != num.end()) {
            // second largest is the maximum digit AFTER the first largest
            auto it_second = std::max_element(it_max + 1, num.end());
            result.push_back(*it_max);
            result.push_back(*it_second);
        }
        // case 2: largest digit IS the last char
        else {
            if (num.size() == 1) {
                // only one digit: result is that digit
                result.push_back(*it_max);
            } else {
                // second largest is the last digit (global max),
                // first largest is the max BEFORE the last digit
                auto it_first = std::max_element(num.begin(), num.end() - 1);
                result.push_back(*it_first);
                result.push_back(*it_max);
            }
        }

        if (!result.empty()) {
            sum += std::stoll(result);
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
