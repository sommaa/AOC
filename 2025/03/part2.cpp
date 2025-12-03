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

std::pair<char, std::pair<int, int>> find_largest_in_buffer(const std::string& num, int buffer) {
    char largest = '0';
    int pos = -1;

    for (int i = 0; i <= buffer; ++i) {
        if (num[i] == '9') {
            return {'9', {buffer - i, i} };
        }

        if (num[i] > largest) {
            largest = num[i];
            pos = i;
        }
    }
    return {largest, {buffer - pos, pos}};
}

int main() {
    auto numbers = read_numbers();
    long long sum = 0;
    int length_largest = 12;
    std::string result;

    // loop on each number
    for (const auto& num : numbers) {
        int buffer = num.size() - length_largest;
        int i = 0;
        for (int j = 0; j < length_largest; ++j) {
            // find the largest digit in the buffer and concatenate it to the result
            auto [largest, shift] = find_largest_in_buffer(num.substr(i, buffer + 1), buffer);
            result.push_back(largest);
            // update the buffer size
            buffer = shift.first;
            // move the index to the position of the found largest digit
            i += shift.second + 1;
        }
        if (!result.empty()) {
            sum += std::stoll(result);
            result.clear();
        } else {
            std::cerr << "Error: result is empty for number " << num << std::endl;
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
