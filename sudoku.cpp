#include <bits/stdc++.h>
using namespace std;

// sqrt_N denotes the size of each smaller sub-box of the GUI Sudoku Grid Object
constexpr int sqrt_N = 3;

// N denotes the size of the overall grid: N X N GUI Sudoku Grid Object
constexpr int N = sqrt_N * sqrt_N;

/**
    SUDOKU_STATUS denotes one of the three possible states the sudoku is in:
        1. INVALID: The sudoku has an invalid row, column or box.
        2. PARTIALLY_FILLED: The sudoku has all rows, columns and boxes as valid,
        but is not completely filled.
        3. COMPLETED: The sudoku has all rows, columns and boxes as valid and is
        completely filled.
*/
enum SUDOKU_STATUS { INVALID, PARTIALLY_FILLED, COMPLETED };

/**
    Returns a boolean that indicates if we can place the digit with value
    val at position (x,y) on a sudoku grid represented as a vector<vector<int>>
*/
bool canPlace(const vector<vector<int>> &grid, int val, int x, int y) {
    // If grid[x][y] already has a number, return false
    if (grid[x][y] != 0) {
        return false;
    }

    // Check if column 'y' contains val and if it does, return false
    for (int i = 0; i < N; ++i) {
        if (grid[i][y] == val) return false;
    }

    // Check if rpw 'x' contains val and if it does, return false
    for (int j = 0; j < N; ++j) {
        if (grid[x][j] == val) return false;
    }

    // Check if the box containing (x,y) contains val and if it does, return false
    int box_top_x = (x / sqrt_N) * sqrt_N;
    int box_top_y = (y / sqrt_N) * sqrt_N;
    for (int i = box_top_x; i < box_top_x + sqrt_N; ++i) {
        for (int j = box_top_y; j < box_top_y + sqrt_N; ++j) {
            if (grid[i][j] == val) return false;
        }
    }

    // All conditions satisfied, val can be placed at (x,y)
    return true;
}

/**
    Returns type SUDOKU_STATUS that indicates the status of a
    sudoku grid represented as a vector<vector<int>>
*/
SUDOKU_STATUS getSudokuStatus(const vector<vector<int>> &grid) {
    bool empty_cell = false;
    for (int i = 0; i < N; ++i) {
        unordered_set<int> cur;
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                empty_cell = true;
                continue;
            }
            if (cur.count(grid[i][j])) return INVALID;
            cur.insert(grid[i][j]);
        }
    }
    // for each column
    for (int i = 0; i < N; ++i) {
        unordered_set<int> cur;
        for (int j = 0; j < N; ++j) {
            if (grid[j][i] == 0) {
                empty_cell = true;
                continue;
            }
            if (cur.count(grid[j][i])) return INVALID;
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
                        empty_cell = true;
                        continue;
                    }
                    if (cur.count(grid[k][l])) return INVALID;
                    cur.insert(grid[k][l]);
                }
            }
        }
    }
    if (!empty_cell) {
        return COMPLETED;
    } else {
        return PARTIALLY_FILLED;
    }
}

/**
    Function that returns true if the sudoku grid represented as a vector<vector<int>>
    can be solved assuming it has been filled validly till position (x,y)

    If function returns true, the grid itself will contain the final solved answer.
*/
bool solveSudokuGrid(vector<vector<int>> &grid, int x = 0, int y = 0) {
    if (x == N) return true;
    if (y == N) return solveSudokuGrid(grid, x + 1, 0);
    if (grid[x][y] != 0) return solveSudokuGrid(grid, x, y + 1);
    for (int i = 1; i <= N; ++i) {
        if (canPlace(grid, i, x, y)) {
            grid[x][y] = i;
            bool nxt = solveSudokuGrid(grid, x, y + 1);
            if (nxt) {
                return nxt;
            } else {
                grid[x][y] = 0;
            }
        }
    }
    return false;
}

/**
    Function that generates a random sudoku and returns it in the form
    of a vector<vector<int>>
*/
vector<vector<int>> generateRandomSudoku() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<vector<int>> grid(N, vector<int>(N));
    iota(grid.front().begin(), grid.front().end(), 1);
    shuffle(grid.front().begin(), grid.front().end(), rng);
    assert(solveSudokuGrid(grid));
    vector<int> pos(N * N);
    iota(pos.begin(), pos.end(), 0);
    shuffle(pos.begin(), pos.end(), rng);
    for (int i = 0; i < N * (N - 2); ++i) {
        int x = pos[i];
        grid[x / N][x % N] = 0;
    }
    return grid;
}
