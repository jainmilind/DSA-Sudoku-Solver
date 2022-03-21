#include "mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QDebug>

using namespace std;

constexpr int N = 9; // N X N sudoku grid
constexpr int WINDOW_L = 1920;
constexpr int WINDOW_W = 1080;

vector<vector<QSpinBox*>> sudokuGrid;

void initializeSudokuGrid(QGridLayout* layout) {
    sudokuGrid.resize(N);
    for(int i = 0; i < N; ++i) {
        sudokuGrid[i].resize(N);
        for(int j = 0; j < N; ++j) {
            QSpinBox* box = new QSpinBox;
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
    for(int i = 0; i < N; ++i) {
        res[i].resize(N);
        for(int j = 0; j < N; ++j) {
            res[i][j] = sudokuGrid[i][j]->value();
        }
    }
    return res;
}

void generateRandomSudoku() {
    qDebug() << QString("Generating random sudoku!");
}

bool isSudokuGridValid(const vector<vector<int>> &grid) {
    return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(WINDOW_L*0.5, WINDOW_W*0.5);
    this->setWindowTitle(QString::fromStdString("A " + to_string(N) + " X " + to_string(N) + " Sudoku Solver"));

    QWidget *container = new QWidget(this);
    this->setCentralWidget(container);

    QGridLayout *layout = new QGridLayout;

    initializeSudokuGrid(layout);

    QPushButton *generateSudoku = new QPushButton("Generate Sudoku");
    layout->addWidget(generateSudoku, N+1, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(generateSudoku, &QPushButton::clicked, [&](){
        generateRandomSudoku();
    });

    QPushButton *verifySudoku = new QPushButton("Verify Sudoku");
    layout->addWidget(verifySudoku, N+2, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(verifySudoku, &QPushButton::clicked, [&](){
        vector<vector<int>> grid = getSudokuGrid();
        qDebug() << isSudokuGridValid(grid);
    });

    QPushButton *solveSudoku = new QPushButton("Solve Sudoku");
    layout->addWidget(solveSudoku, N+3, 0, 1, N, Qt::AlignHCenter);
    QObject::connect(solveSudoku, &QPushButton::clicked, [&](){
        qDebug() << QString("Solve the sudoku!");
    });

    container->setLayout(layout);
}

MainWindow::~MainWindow()
{

}

