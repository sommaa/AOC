#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> lines;
    std::string line;
    std::string symbol_line;
    
    // Read all lines, find the symbol line (last non-empty line with * or +)
    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }
    
    // Find and remove the symbol line
    for (int i = lines.size() - 1; i >= 0; --i) {
        if (lines[i].find('*') != std::string::npos || lines[i].find('+') != std::string::npos) {
            symbol_line = lines[i];
            lines.erase(lines.begin() + i);
            break;
        }
    }
    
    // Find max width
    size_t max_width = 0;
    for (const auto& l : lines) {
        max_width = std::max(max_width, l.size());
    }
    max_width = std::max(max_width, symbol_line.size());
    
    // Pad all lines to max_width
    for (auto& l : lines) {
        if (l.size() < max_width) {
            l.resize(max_width, ' ');
        }
    }
    if (symbol_line.size() < max_width) {
        symbol_line.resize(max_width, ' ');
    }
    
    long long grand_total = 0;
    int col = max_width - 1;
    
    while (col >= 0) {
        // Skip any space columns at the right
        while (col >= 0) {
            bool all_space = true;
            for (const auto& l : lines) {
                if (l[col] != ' ') {
                    all_space = false;
                    break;
                }
            }
            if (all_space && symbol_line[col] == ' ') {
                --col;
            } else {
                break;
            }
        }
        if (col < 0) break;
        
        std::vector<int> problem_cols;
        char op = ' ';
        
        while (col >= 0) {
            // Check if this is a separator column
            bool all_space = true;
            for (const auto& l : lines) {
                if (l[col] != ' ') {
                    all_space = false;
                    break;
                }
            }
            
            if (all_space && symbol_line[col] == ' ') {
                // This is a separator, we're done with this problem
                break;
            }
            
            // Part of the problem
            problem_cols.push_back(col);
            if (symbol_line[col] == '*' || symbol_line[col] == '+') {
                op = symbol_line[col];
            }
            --col;
        }
        
        if (problem_cols.empty()) continue;
        
        // Each column in problem_cols is one number
        // Read digits top-to-bottom in each column
        std::vector<long long> numbers;
        for (int c : problem_cols) {
            std::string num_str;
            for (const auto& l : lines) {
                if (l[c] != ' ' && std::isdigit(l[c])) {
                    num_str += l[c];
                }
            }
            if (!num_str.empty()) {
                numbers.push_back(std::stoll(num_str));
            }
        }
        
        // Calculate result for this problem
        if (!numbers.empty()) {
            long long result = numbers[0];
            for (size_t i = 1; i < numbers.size(); ++i) {
                if (op == '+') result += numbers[i];
                else if (op == '*') result *= numbers[i];
            }
            grand_total += result;
        }
    }
    
    std::cout << grand_total << std::endl;
    return 0;
}