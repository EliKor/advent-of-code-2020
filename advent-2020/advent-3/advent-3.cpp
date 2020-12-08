#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int count_trees(vector<string>& grid, int x, int y) {
    int i = 0;
    int j = 0;
    int trees = 0;
    int m = grid.size();
    int n = grid[0].size();
    while (i < m) {
        j = (j + x) % n;
        i += y;
        trees += grid[i][j] == '#';
    }
    return trees;
}

int main() {
    int N = 323;
    vector<string> grid;
    for (int i = 0; i < N; i++) {
        string row;
        cin >> row;
        grid.push_back(row);
    }
    cout << "grid size: " << grid.size() << endl;
    cout << "Num trees: " << count_trees(grid, 3, 1) << endl;
    long long mult_trees = 0;
    vector<pair<int,int>> slopes = {{1,1}, {3,1}, {5,1}, {7, 1}, {1,2}};
    for (auto slope : slopes) {
        if (mult_trees == 0) {
            mult_trees = count_trees(grid, slope.first, slope.second);
        }
        else {
            mult_trees *= count_trees(grid, slope.first, slope.second);
        }
    }
    cout << "Mult trees: " << mult_trees << endl;
    return 0;
}
