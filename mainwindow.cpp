#include "mainwindow.h"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>

#include "sudoku.cpp"

using namespace std;

// Constant to denote the length of the window
constexpr int WINDOW_L = sqrt_N * 150;

// Constant to denote the width of the window
constexpr int WINDOW_W = sqrt_N * 300;

// GUI Sudoku Grid Object that is displayed on the Qt window
vector<vector<QSpinBox *>> sudokuGrid;

/**
    Function that fills the GUI Sudoku Grid Object with N X N QSpinBoxes
*/
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

/**
    Reads the current state of the GUI Sudoku Grid Object and returns it in the form
    of an N X N vector<vector<int>>
*/
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

/**
    Populates the GUI Sudoku Grid Object using the input parameter of an N X N
    vector<vector<int>> grid
*/
void setSudokuGrid(const vector<vector<int>> &grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sudokuGrid[i][j]->setValue(grid[i][j]);
        }
    }
}

/**
    Resets all the GUI Sudoku Grid Object boxes to value 0
*/
void clearSudokuGrid() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sudokuGrid[i][j]->setValue(0);
        }
    }
}

/**
    Qt constructor function for MainWindow class
*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Set the GUI Window to have size determined from global constantss
    this->setFixedSize(WINDOW_L * 0.75, WINDOW_W * 0.75);

    // Set the appropriate title for the GUI Window
    this->setWindowTitle(QString::fromStdString("A " + to_string(N) + " X " + to_string(N) + " Sudoku Solver"));

    QWidget *container = new QWidget(this);
    this->setCentralWidget(container);
    QGridLayout *layout = new QGridLayout;
    layout->setVerticalSpacing(-1);
    layout->setHorizontalSpacing(-1);

    // Build the GUI Sudoku Grid Object into the QGridLayout object
    initializeSudokuGrid(layout);

    // Button to handle the verification of the GUI Sudoku Grid Object
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

    // Button to handle solving the GUI Sudoku Grid Object
    QPushButton *solveSudoku = new QPushButton("Solve Sudoku");
    layout->addWidget(solveSudoku, N + 2, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(solveSudoku, &QPushButton::clicked, [&]() {
        vector<vector<int>> grid = getSudokuGrid();

        if (solveSudokuGrid(grid))
            setSudokuGrid(grid);
        else
            qDebug() << QString("LMAO DED");
    });

    // Button to handle the generation of the GUI Sudoku Grid Object
    QPushButton *generateSudoku = new QPushButton("Generate Sudoku");
    layout->addWidget(generateSudoku, N + 3, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(generateSudoku, &QPushButton::clicked, [&]() {
        clearSudokuGrid();
        setSudokuGrid(generateRandomSudoku());
    });

    // Button to handle clearing of the GUI Sudoku Grid Object
    QPushButton *clearSudoku = new QPushButton("Clear Sudoku");
    layout->addWidget(clearSudoku, N + 4, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(clearSudoku, &QPushButton::clicked, [&]() {
        clearSudokuGrid();
    });

    container->setLayout(layout);
}

MainWindow::~MainWindow() {}
