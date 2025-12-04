#include <iostream>
#include <vector>
#include <string>

using Maze = std::vector<std::string>;

Maze read_maze() {
    Maze maze;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') { // handle possible CRLF
            line.pop_back();
        }
        maze.push_back(line);
    }
    return maze;
}

bool is_in_bounds(int row, int col, const Maze& maze) {
    return row >= 0 && row < static_cast<int>(maze.size()) &&
           col >= 0 && col < static_cast<int>(maze[row].size());
}

bool check_less_than_four_adjacent_ats(int r, int c, const Maze& maze, const std::vector<std::pair<int, int>>& directions) {
    int num_adjacent_ats = 0;
    for (const auto& [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;
        if (is_in_bounds(nr, nc, maze) && maze[nr][nc] == '@') {
            ++num_adjacent_ats;
        }
    }
    return num_adjacent_ats < 4;
}

int main() {
    Maze maze = read_maze();

    // adjacent movements: up, down, left, right, and diagonals
    const std::vector<std::pair<int, int>> directions = {
        {-1,  0}, {1,  0}, {0, -1}, {0,  1},
        {-1, -1}, {-1, 1}, {1, -1}, {1,  1}
    };

    int num_with_four_adjacent_ats = 0;
    int removed_ats = 0;
    Maze output_maze = maze; // to store the output maze

    while (true) {
        bool any_changes = false;

        for (int r = 0; r < static_cast<int>(maze.size()); ++r) {
            for (int c = 0; c < static_cast<int>(maze[r].size()); ++c) {
                if (maze[r][c] != '@') {
                    continue;
                }

                if (check_less_than_four_adjacent_ats(r, c, maze, directions)) {
                    output_maze[r][c] = '.';
                    ++removed_ats;
                    any_changes = true;
                } 
            }
        }

        if (!any_changes) {
            break;
        }

        maze = output_maze;
    }

    std::cout << removed_ats << '\n';

    return 0;
}
