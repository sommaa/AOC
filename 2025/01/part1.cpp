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
    int counted_zeroes = 0;

    for (const auto& line : inputLines) {
        //get first character and following numbers
        char rotation = line[0];
        int number = std::stoi(line.substr(1));
        if (rotation == 'L') {
            dial = (dial - number) % 100;
        } else if (rotation == 'R') {
            dial = (dial + number) % 100;
        } 
        if (dial == 0) {
            counted_zeroes++;
        }
    }

    std::cout << "Total counted zeroes: " << counted_zeroes << std::endl;
    
    return 0;
}
