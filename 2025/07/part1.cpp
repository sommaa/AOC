#include <iostream>
#include <vector>
#include <string>
#include <set>

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
    
    set<int> active_beams;
    active_beams.insert(start_col);
    
    int split_count = 0;
    set<pair<int,int>> used_splitters;
    
    for (int row = start_row + 1; row < rows && !active_beams.empty(); row++) {
        set<int> new_beams;
        
        for (int col : active_beams) {
            if (col < 0 || col >= cols) continue;
            
            if (grid[row][col] == '^') {
                pair<int,int> pos = {row, col};
                if (used_splitters.find(pos) == used_splitters.end()) {
                    used_splitters.insert(pos);
                    split_count++;
                    int left_col = col - 1;
                    int right_col = col + 1;
                    if (left_col >= 0) new_beams.insert(left_col);
                    if (right_col < cols) new_beams.insert(right_col);
                }
            } else {
                new_beams.insert(col);
            }
        }
        
        active_beams = new_beams;
    }
    
    cout << split_count << endl;
    
    return 0;
}