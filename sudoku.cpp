#include <vector>
#include <set>
#include <chrono>
#include <random>
using namespace std;

constexpr int N = 9; // N X N sudoku grid
constexpr int sqrt_N = 3;

enum SUDOKU_STATUS {INVALID, PARTIALLY_FILLED, COMPLETED};

bool canPlace(const vector<vector<int>> &grid, int val, int x, int y) {
    // iterate over row

    // iterate over column

    // iterate over box

    return true;
}

SUDOKU_STATUS getSudokuStatus(const vector<vector<int>> &grid) {
    // merge partially and fully filled functions
}

bool isPartialSudokuGridValid(const vector<vector<int>> &grid) {
    // for each row
    for (int i = 0; i < N; ++i) {
        set<int> cur;
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0)
                continue;
            if (cur.count(grid[i][j]))
                return false;
            cur.insert(grid[i][j]);
        }
    }

    // for each column
    for (int i = 0; i < N; ++i) {
        set<int> cur;
        for (int j = 0; j < N; j++) {
            if (grid[j][i] == 0)
                continue;
            if (cur.count(grid[j][i]))
                return false;
            cur.insert(grid[j][i]);
        }
    }

    // for each box
    for (int i = 0; i < N; i += sqrt_N) {
        for (int j = 0; j < N; j += sqrt_N) {
            set<int> cur;
            for (int k = j; k < sqrt_N + j; ++k) {
                for (int l = i; l < sqrt_N + i; ++l) {
                    if (grid[k][l] == 0)
                        continue;
                    if (cur.count(grid[k][l]))
                        return false;
                    cur.insert(grid[k][l]);
                }
            }
        }
    }
    return true;
}

bool isSudokuGridValid(const vector<vector<int>> &grid) {
    set<int> target;
    for (int i = 1; i <= N; ++i) {
        target.insert(i);
    }

    // for each row
    for (int i = 0; i < N; ++i) {
        set<int> cur;
        for (int j = 0; j < N; j++) {
            cur.insert(grid[i][j]);
        }
        if (cur != target)
            return false;
    }

    // for each column
    for (int i = 0; i < N; ++i) {
        set<int> cur;
        for (int j = 0; j < N; j++) {
            cur.insert(grid[j][i]);
        }
        if (cur != target)
            return false;
    }

    // for each box
    for (int i = 0; i < N; i += sqrt_N) {
        for (int j = 0; j < N; j += sqrt_N) {
            set<int> cur;
            for (int k = j; k < sqrt_N + j; ++k) {
                for (int l = i; l < sqrt_N + i; ++l) {
                    cur.insert(grid[k][l]);
                }
            }
            if (cur != target)
                return false;
        }
    }

    return true;
}

bool solveSudokuGrid(vector<vector<int>> &grid, int x = 0, int y = 0) {
    if (x == N)
        return isSudokuGridValid(grid);

    if (y == N)
        return solveSudokuGrid(grid, x + 1, 0);

    if (grid[x][y] != 0)
        return solveSudokuGrid(grid, x, y + 1);

    for (int i = 1; i <= N; ++i) {
        grid[x][y] = i;
        if (isPartialSudokuGridValid(grid)) {
            bool res = solveSudokuGrid(grid, x, y + 1);
            if (res)
                return res;
        }
        grid[x][y] = 0;
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

                    if (!isPartialSudokuGridValid(grid)) {
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
