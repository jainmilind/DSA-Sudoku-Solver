#include "mainwindow.h"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>

#include "sudoku.cpp"

using namespace std;

constexpr int WINDOW_L = sqrt_N * 150;
constexpr int WINDOW_W = sqrt_N * 300;

vector<vector<QSpinBox *>> sudokuGrid;

void initializeSudokuGrid(QGridLayout *layout) {
    sudokuGrid.resize(N);
    for (int i = 0; i < N; ++i) {
        sudokuGrid[i].resize(N);
        for (int j = 0; j < N; ++j) {
            QSpinBox *box = new QSpinBox;
            box->setMinimum(0);
            box->setMaximum(N);
            box->setSpecialValueText(" ");
            box->setButtonSymbols(QAbstractSpinBox::NoButtons);
            sudokuGrid[i][j] = box;
            layout->addWidget(box, i, j);
        }
    }
}

vector<vector<int>> getSudokuGrid() {
    vector<vector<int>> res;
    res.resize(N);
    for (int i = 0; i < N; ++i) {
        res[i].resize(N);
        for (int j = 0; j < N; ++j) {
            res[i][j] = sudokuGrid[i][j]->value();
        }
    }
    return res;
}

void setSudokuGrid(const vector<vector<int>> &grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sudokuGrid[i][j]->setValue(grid[i][j]);
        }
    }
}

void clearSudokuGrid() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sudokuGrid[i][j]->setValue(0);
        }
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(WINDOW_L * 0.75, WINDOW_W * 0.75);
    this->setWindowTitle(QString::fromStdString("A " + to_string(N) + " X " + to_string(N) + " Sudoku Solver"));

    QWidget *container = new QWidget(this);
    this->setCentralWidget(container);

    QGridLayout *layout = new QGridLayout;
    layout->setVerticalSpacing(-1);
    layout->setHorizontalSpacing(-1);

    initializeSudokuGrid(layout);

    QPushButton *verifySudoku = new QPushButton("Verify Sudoku");
    layout->addWidget(verifySudoku, N + 1, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(verifySudoku, &QPushButton::clicked, [&]() {
        vector<vector<int>> grid = getSudokuGrid();
        SUDOKU_STATUS valid = getSudokuStatus(grid);
        QMessageBox *Msgbox = new QMessageBox;
        if (valid == INVALID) {
            Msgbox->setText("The Sudoku is invalid!");
        } else if (valid == COMPLETED) {
            Msgbox->setText("Congratulations! The Sudoku is completed!");
        } else {
            Msgbox->setText("The Sudoku is valid!");
        }
        Msgbox->exec();
    });

    QPushButton *solveSudoku = new QPushButton("Solve Sudoku");
    layout->addWidget(solveSudoku, N + 2, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(solveSudoku, &QPushButton::clicked, [&]() {
        vector<vector<int>> grid = getSudokuGrid();

        if (solveSudokuGrid(grid))
            setSudokuGrid(grid);
        else
            qDebug() << QString("LMAO DED");
    });

    QPushButton *generateSudoku = new QPushButton("Generate Sudoku");
    layout->addWidget(generateSudoku, N + 3, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(generateSudoku, &QPushButton::clicked, [&]() {
        clearSudokuGrid();
        setSudokuGrid(generateRandomSudoku());
    });

    QPushButton *clearSudoku = new QPushButton("Clear Sudoku");
    layout->addWidget(clearSudoku, N + 4, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(clearSudoku, &QPushButton::clicked, [&]() {
        clearSudokuGrid();
    });

    container->setLayout(layout);
}

MainWindow::~MainWindow() {}
