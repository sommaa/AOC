#include <iostream>
#include <vector>
#include <string>

// read from cin the number ranges patterns num1-num2,num3-num4,...
std::vector<std::pair<long long, long long>> read_ranges() {
    std::vector<std::pair<long long, long long>> ranges;
    std::string line;
    std::getline(std::cin, line);
    size_t pos = 0;
    while (pos < line.size()) {
        size_t dash_pos = line.find('-', pos);
        size_t comma_pos = line.find(',', pos);
        if (dash_pos == std::string::npos) break;

        long long start = std::stoll(line.substr(pos, dash_pos - pos));
        long long end = std::stoll(line.substr(dash_pos + 1, (comma_pos == std::string::npos ? line.size() : comma_pos) - dash_pos - 1));
        ranges.emplace_back(start, end);

        if (comma_pos == std::string::npos) break;
        pos = comma_pos + 1;
    }
    return ranges;
}

// count repeated number in the ranges like 6464 or 123123 and add them up
long long count_repeated_numbers(const std::vector<std::pair<long long, long long>>& ranges) {
    long long total_count = 0;
    for (const auto& range : ranges) {
        for (long long num = range.first; num <= range.second; ++num) {
            std::string num_str = std::to_string(num);
            size_t len = num_str.size();
            if (len % 2 == 0) {
                std::string first_half = num_str.substr(0, len / 2);
                std::string second_half = num_str.substr(len / 2);
                if (first_half == second_half) {
                    total_count += num;
                }
            }
        }
    }
    return total_count;
}

int main() {
    auto ranges = read_ranges();
    long long result = count_repeated_numbers(ranges);
    std::cout << result << std::endl;
    return 0;
}
