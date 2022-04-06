#include <vector>
#include <set>
#include <chrono>
#include <random>
using namespace std;

constexpr int sqrt_N = 2;
constexpr int N = sqrt_N*sqrt_N; // N X N sudoku grid

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
        set<int> cur;
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
        set<int> cur;
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
            set<int> cur;
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
    vector<vector<int>> grid, gridCheck;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    do {
        grid = vector<vector<int>>(N, vector<int>(N));
        const int fill_count = rng() % N + N;

        for (int i = 0; i < fill_count; ++i) {

            int coords = uniform_int_distribution<int>(0, N * N - 1)(rng);
            int x_coord = coords / N;
            int y_coord = coords % N;
            if (grid[x_coord][y_coord] == 0) {
                for (int value = 1; value <= N; ++value) {
                    grid[x_coord][y_coord] = value;

                    if (getSudokuStatus(grid) == INVALID) {
                        grid[x_coord][y_coord] = 0;
                    }
                    else {
                        goto AC;
                    }
                }
            }
            else i--;
            AC:;
        }
        gridCheck = grid;

    } while (!solveSudokuGrid(gridCheck));

    return grid;
}
