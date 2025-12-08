#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main() {
    vector<string> grid;
    string line;
    int start_col = -1;
    int start_row = -1;
    
    while (getline(cin, line)) {
        if (!line.empty()) {
            if (start_col == -1) {
                for (int i = 0; i < (int)line.size(); i++) {
                    if (line[i] == 'S') {
                        start_col = i;
                        start_row = grid.size();
                        break;
                    }
                }
            }
            grid.push_back(line);
        }
    }
    
    int rows = grid.size();
    int cols = grid[0].size();
    
    map<int, long long> timelines;
    timelines[start_col] = 1;
    
    for (int row = start_row + 1; row < rows && !timelines.empty(); row++) {
        map<int, long long> new_timelines;
        
        for (auto& p : timelines) {
            int col = p.first;
            long long count = p.second;
            
            if (col < 0 || col >= cols) continue;
            
            if (grid[row][col] == '^') {
                int left_col = col - 1;
                int right_col = col + 1;
                if (left_col >= 0) new_timelines[left_col] += count;
                if (right_col < cols) new_timelines[right_col] += count;
            } else {
                new_timelines[col] += count;
            }
        }
        
        timelines = new_timelines;
    }
    
    long long total = 0;
    for (auto& p : timelines) {
        total += p.second;
    }
    
    cout << total << endl;
    
    return 0;
}