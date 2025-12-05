#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

// read from cin the ranges and the numbers divided by a \n 
// ranges: range1-range2\n
// numbers: num\n
std::pair<std::vector<std::pair<long long, long long>>, std::vector<long long>> read_input() {
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> numbers;
    std::string line;

    // Read ranges
    while (std::getline(std::cin, line) && !line.empty()) {
        size_t dash_pos = line.find('-');
        if (dash_pos != std::string::npos) {
            long long start = std::stoll(line.substr(0, dash_pos));
            long long end = std::stoll(line.substr(dash_pos + 1));
            ranges.emplace_back(start, end);
        }
    }

    // Read numbers
    while (std::getline(std::cin, line) && !line.empty()) {
        numbers.push_back(std::stoll(line));
    }

    return {ranges, numbers};
}

// merge overlapping ranges
std::vector<std::pair<long long, long long>> merge_ranges(const std::vector<std::pair<long long, long long>>& ranges) {
    if (ranges.empty()) return {};
    std::vector<std::pair<long long, long long>> merged;
    auto sorted_ranges = ranges;
    std::sort(sorted_ranges.begin(), sorted_ranges.end());
    merged.push_back(sorted_ranges[0]);
    for (size_t i = 1; i < sorted_ranges.size(); ++i) {
        if (sorted_ranges[i].first <= merged.back().second) {
            merged.back().second = std::max(merged.back().second, sorted_ranges[i].second);
        } else {
            merged.push_back(sorted_ranges[i]);
        }
    }
    return merged;
}

// check how many numbers are in the ranges
 long long count_numbers_in_ranges(const std::vector<std::pair<long long, long long>>& ranges) {
    auto merged_ranges = merge_ranges(ranges);
    long long count = 0;
    for (const auto& range : merged_ranges) {
        count += (range.second - range.first + 1);
    }
    return count;
}

int main() {
    auto [ranges, numbers] = read_input();
    long long total_count = count_numbers_in_ranges(ranges);
    std::cout << "Total numbers in ranges: " << total_count << "\n";
    return 0;
}