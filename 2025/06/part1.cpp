#include <iostream>
#include <vector>
#include <string>

std::pair<std::vector<std::vector<long long>>, std::vector<char>> read_input() {
    std::vector<std::vector<long long>> grid;
    std::vector<char> symbols;
    std::string line;
    
    // Read grid
    while (std::getline(std::cin, line) && !line.empty()) {
        if (line.find('*') != std::string::npos || line.find('+') != std::string::npos) {
            // This line contains symbols, parse them
            size_t pos = 0;
            while (pos < line.size()) {
                // Skip spaces
                while (pos < line.size() && line[pos] == ' ') ++pos;
                if (pos >= line.size()) break;
                
                // Check if it's a symbol (not a digit)
                if (!isdigit(line[pos]) && line[pos] != '-') {
                    symbols.push_back(line[pos]);
                }
                ++pos;
            }
            break; // Stop reading after symbols line
        }
        
        // Parse numbers
        std::vector<long long> row;
        size_t pos = 0;
        while (pos < line.size()) {
            // Skip spaces
            while (pos < line.size() && line[pos] == ' ') ++pos;
            if (pos >= line.size()) break;
            
            // Read number
            size_t start = pos;
            while (pos < line.size() && line[pos] != ' ') ++pos;
            row.push_back(std::stoll(line.substr(start, pos - start)));
        }
        grid.push_back(row);
    }
    
    return {grid, symbols};
}

int main() {
    auto [grid, symbols] = read_input();
    
    long long final_result = 0;
    // loop on grid columns and symbols they have same length
    // sum if symbol is '+' muliply if symbol is '*'
    for (size_t col = 0; col < grid[0].size(); ++col) {
        long long result_col = (symbols[col] == '+') ? 0 : 1;
        for (size_t row = 0; row < grid.size(); ++row) {
            if (symbols[col] == '+') {
                result_col += grid[row][col];
            } else if (symbols[col] == '*') {
                result_col *= grid[row][col];
            }
        }
        final_result += result_col;
    }
    
    std::cout << "Final result: " << final_result << std::endl;
    return 0;
}