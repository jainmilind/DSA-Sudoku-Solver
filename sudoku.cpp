#include <bits/stdc++.h>
using namespace std;

constexpr int sqrt_N = 3;
constexpr int N = sqrt_N * sqrt_N; // N X N sudoku grid

enum SUDOKU_STATUS {INVALID, PARTIALLY_FILLED, COMPLETED};

bool canPlace(const vector<vector<int>> &grid, int val, int x, int y) {
    if(grid[x][y] != 0) {
        return false;
    }
    // iterate in column
    for(int i = 0; i < N ; ++i) {
        if(grid[i][y] == val)
            return false;
    }
    // iterate in row
    for(int j = 0; j < N ; ++j) {
        if(grid[x][j] == val)
            return false;
    }
    // iterate in box
    int box_top_x = (x/sqrt_N)*sqrt_N;
    int box_top_y = (y/sqrt_N)*sqrt_N;
    for(int i = box_top_x; i < box_top_x + sqrt_N; ++i) {
        for(int j = box_top_y; j < box_top_y + sqrt_N; ++j) {
            if(grid[i][j] == val)
                return false;
        }
    }
    return true;
}

SUDOKU_STATUS getSudokuStatus(const vector<vector<int>> &grid) {
    int empty_cell_cnt = 0;
    for (int i = 0; i < N; ++i) {
        unordered_set<int> cur;
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                ++empty_cell_cnt;
                continue;
            }
            if (cur.count(grid[i][j]))
                return INVALID;
            cur.insert(grid[i][j]);
        }
    }
    // for each column
    for (int i = 0; i < N; ++i) {
        unordered_set<int> cur;
        for (int j = 0; j < N; j++) {
            if (grid[j][i] == 0) {
                ++empty_cell_cnt;
                continue;
            }
            if (cur.count(grid[j][i]))
                return INVALID;
            cur.insert(grid[j][i]);
        }
    }
    // for each box
    for (int i = 0; i < N; i += sqrt_N) {
        for (int j = 0; j < N; j += sqrt_N) {
            unordered_set<int> cur;
            for (int k = j; k < sqrt_N + j; ++k) {
                for (int l = i; l < sqrt_N + i; ++l) {
                    if (grid[k][l] == 0) {
                        ++empty_cell_cnt;
                        continue;
                    }
                    if (cur.count(grid[k][l]))
                        return INVALID;
                    cur.insert(grid[k][l]);
                }
            }
        }
    }
    if(empty_cell_cnt == 0) {
        return COMPLETED;
    }
    else {
        return PARTIALLY_FILLED;
    }
}

bool solveSudokuGrid(vector<vector<int>> &grid, int x = 0, int y = 0) {
    if (x == N)
        return true;
    if (y == N)
        return solveSudokuGrid(grid, x + 1, 0);
    if (grid[x][y] != 0)
        return solveSudokuGrid(grid, x, y + 1);
    for (int i = 1; i <= N; ++i) {
        if(canPlace(grid, i, x, y)) {
            grid[x][y] = i;
            bool nxt = solveSudokuGrid(grid, x, y+1);
            if(nxt) {
                return nxt;
            }
            else {
                grid[x][y] = 0;
            }
        }
    }
    return false;
}

vector<vector<int>> generateRandomSudoku() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<vector<int>> grid(N, vector<int>(N));
    iota(grid.front().begin(), grid.front().end(), 1);
    shuffle(grid.front().begin(), grid.front().end(), rng);
    assert(solveSudokuGrid(grid));
    vector<int> pos(N * N);
    iota(pos.begin(), pos.end(), 0);
    shuffle(pos.begin(), pos.end(), rng);
    for (int i = 0; i < N * (N - 2); i++) {
        int x = pos[i];
        grid[x / N][x % N] = 0;
    }
    return grid;
}
