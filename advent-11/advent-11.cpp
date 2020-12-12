#include <iostream>
#include <string>
#include <vector>

using namespace std;
// initial thoughts
// this is like conway's game of life

int simulate_round(vector<string>& grid) {
    vector<string> grid_copy(grid.begin(), grid.end());
    int m = grid.size();
    int n = grid[0].size();
    int occupied = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '.') {
                continue;
            }
            int adjacents = 0;
            for (int di = -1; di <= 1; di++) {
                if (i + di < 0 || i + di > m) {
                    continue;
                }
                for (int dj = -1; dj <= 1; dj++) {
                    if (j + dj < 0 || j + dj > n || (di == 0 && dj == 0)) {
                        continue;
                    }
                    adjacents += grid[i+di][j+dj] == '#';
                }
            }
            if (adjacents == 0 && grid[i][j] == 'L') {
                grid_copy[i][j] = '#';
            }
            else if (adjacents >= 4 && grid[i][j] == '#') {
                grid_copy[i][j] = 'L';
            }
            occupied += grid_copy[i][j] == '#';
        }
    }
    grid = grid_copy;
    return occupied;
}

void expand_out(vector<string>& grid, vector<vector<int>>& occ_mat, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) {
                continue;
            }
            int x = i + di;
            int y = j + dj;
            while (0 <= x && x < m && 0 <= y && y < n) {
                if (grid[x][y] == '#' || grid[x][y] == 'L') {
                    occ_mat[i][j] += grid[x][y] == '#';
                    break;
                }
                x += di;
                y += dj;
            }
        }
    }
}

vector<vector<int>> gen_occ_mat(vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> occ_mat(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            expand_out(grid, occ_mat, i, j);
        }
    }
    return occ_mat;
}

void look_left_and_right(vector<string>& grid, vector<vector<int>>& occ_mat) {
    int m = grid.size();
    int n = grid[0].size();
    for (int i = 0; i < m; i++) {
        bool left_occ = false;
        for (int j = 0; j < n; j++) {
            occ_mat[i][j] += left_occ;
            if (grid[i][j] == 'L') {
                left_occ = false;
            }
            else if (grid[i][j] == '#') {
                left_occ = true;
            }
        }
        bool right_occ = false;
        for (int j = n-1; j >= 0; j--) {
            occ_mat[i][j] += right_occ;
            if (grid[i][j] == 'L') {
                right_occ = false;
            }
            else if (grid[i][j] == '#') {
                right_occ = true;
            }
        }
    }
}

void look_up_and_down(vector<string>& grid, vector<vector<int>>& occ_mat) {
    int m = grid.size();
    int n = grid[0].size();
    for (int j = 0; j < n; j++) {
        bool up_occ = false;
        for (int i = 0; i < m; i++) {
            occ_mat[i][j] += up_occ;
            if (grid[i][j] == 'L') {
                up_occ = false;
            }
            else if (grid[i][j] == '#') {
                up_occ = true;
            }
        }
        bool down_occ = false;
        for (int i = m-1; i >= 0; i--) {
            occ_mat[i][j] += down_occ;
            if (grid[i][j] == 'L') {
                down_occ = false;
            }
            else if (grid[i][j] == '#') {
                down_occ = true;
            }
        }
    }
}

void look_dr_and_ul(vector<string>& grid, vector<vector<int>>& occ_mat) {
    int m = grid.size();
    int n = grid[0].size();
    for (int start = m-2; start >= 0; start--) {
        int i = start;
        int j = 0;
        bool dr_occ = false;
        while (i < m && j < n) {
            occ_mat[i][j] += dr_occ;
            if (grid[i][j] == 'L') {
                dr_occ = false;
            }
            else if (grid[i][j] == '#') {
                dr_occ = true;
            }
            i++;
            j++;
        }
        i--;
        j--;
        bool ul_occ = false;
        while (i >= start && j >= 0) {
            occ_mat[i][j] += ul_occ;
            if (grid[i][j] == 'L') {
                ul_occ = false;
            }
            else if (grid[i][j] == '#') {
                ul_occ = true;
            }
            i--;
            j--;
        }
    }
    for (int start = 1; start < n; start++) {
        int j = start;
        int i = 0;
        bool dr_occ = false;
        while (i < m && j < n) {
            occ_mat[i][j] += dr_occ;
            if (grid[i][j] == 'L') {
                dr_occ = false;
            }
            else if (grid[i][j] == '#') {
                dr_occ = true;
            }
            i++;
            j++;
        }
        i--;
        j--;
        bool ul_occ = false;
        while (i >= 0 && j >= start) {
            occ_mat[i][j] += ul_occ;
            if (grid[i][j] == 'L') {
                ul_occ = false;
            }
            else if (grid[i][j] == '#') {
                ul_occ = true;
            }
            i--;
            j--;
        }
    }
}

void look_dl_and_ur(vector<string>& grid, vector<vector<int>>& occ_mat) {
    int m = grid.size();
    int n = grid[0].size();
    for (int start = m-2; start >= 0; start--) {
        int i = start;
        int j = n-1;
        bool dl_occ = false;
        while (i < m && j >= 0) {
            occ_mat[i][j] += dl_occ;
            if (grid[i][j] == 'L') {
                dl_occ = false;
            }
            else if (grid[i][j] == '#') {
                dl_occ = true;
            }
            i++;
            j--;
        }
        i--;
        j++;
        bool ur_occ = false;
        while (i >= start && j < n) {
            occ_mat[i][j] += ur_occ;
            if (grid[i][j] == 'L') {
                ur_occ = false;
            }
            else if (grid[i][j] == '#') {
                ur_occ = true;
            }
            i--;
            j++;
        }
    }
    for (int start = n-2; start >= 0; start--) {
        int j = start;
        int i = 0;
        bool dl_occ = false;
        while (i < m && j >= 0) {
            occ_mat[i][j] += dl_occ;
            if (grid[i][j] == 'L') {
                dl_occ = false;
            }
            else if (grid[i][j] == '#') {
                dl_occ = true;
            }
            i++;
            j--;
        }
        i--;
        j++;
        bool ur_occ = false;
        while (i >= 0 && j <= start) {
            occ_mat[i][j] += ur_occ;
            if (grid[i][j] == 'L') {
                ur_occ = false;
            }
            else if (grid[i][j] == '#') {
                ur_occ = true;
            }
            i--;
            j++;
        }
    }
}

void print_occ_mat(vector<vector<int>>& occ_mat) {
    for (int i = 0; i < occ_mat.size(); i++) {
        for (int j = 0; j < occ_mat[0].size(); j++) {
            cout << occ_mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> gen_occ_mat2(vector<string>& grid) {
    vector<vector<int>> occ_mat(grid.size(), vector<int>(grid[0].size(), 0));
    look_up_and_down(grid, occ_mat);
    look_left_and_right(grid, occ_mat);
    look_dl_and_ur(grid, occ_mat);
    look_dr_and_ul(grid, occ_mat);
    return occ_mat;
}

int simulate_round2(vector<string>& grid) {
    vector<string> grid_copy(grid.begin(), grid.end());
    int m = grid.size();
    int n = grid[0].size();
    int occupied = 0;
    vector<vector<int>> occ_mat = gen_occ_mat2(grid);
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '.') {
                continue;
            }
            if (occ_mat[i][j] == 0 && grid[i][j] == 'L') {
                grid_copy[i][j] = '#';
            }
            else if (occ_mat[i][j] >= 5 && grid[i][j] == '#') {
                grid_copy[i][j] = 'L';
            }
            occupied += grid_copy[i][j] == '#';
        }
    }
    grid = grid_copy;
    return occupied;
}

void print_grid(vector<string>& grid) {
    cout << endl;
    for (int i = 0; i < grid.size(); i++) {
        cout << grid[i] << endl;
    }
}

void part1(vector<string> grid) {
    int prev_occupied = -1;
    int curr_occupied = 0; 
    while (prev_occupied != curr_occupied) {
        prev_occupied = curr_occupied;
        curr_occupied = simulate_round(grid);
    }
    cout << "Occupied seats: " << curr_occupied << endl;
}

void part2(vector<string> grid) {
    int prev_occupied = -1;
    int curr_occupied = 0;
    while (prev_occupied != curr_occupied) {
        prev_occupied = curr_occupied;
        curr_occupied = simulate_round2(grid);
    }
    cout << "Occupied seats: " << curr_occupied << endl;
}

int main() {
    string s;
    vector<string> grid;
    while (cin >> s) {
        grid.push_back(s);
    }
    part1(grid);
    part2(grid);
    return 0;
}
