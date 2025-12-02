#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> readInput() {
    std::vector<std::string> inputLines;
    std::string line;
    while (std::getline(std::cin, line)) {
            inputLines.push_back(line);
    }
    return inputLines;
}

int main() {
    std::vector<std::string> inputLines = readInput();
    int dial = 50;
    long long counted_zeroes = 0;

    for (const auto& line : inputLines) {
        char rotation = line[0];
        int distance = std::stoi(line.substr(1));

        int step = (rotation == 'L') ? -1 : +1;

        for (int i = 0; i < distance; ++i) {
            dial += step;

            // wrap around 0..99
            if (dial == 100) dial = 0;
            else if (dial == -1) dial = 99;

            if (dial == 0) {
                counted_zeroes++;
            }
        }
    }

    std::cout << "Total counted zeroes: " << counted_zeroes << std::endl;
    return 0;
}
