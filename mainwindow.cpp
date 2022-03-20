#include "mainwindow.h"
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

int N = 3; // N X N sudoku grid

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    {
        QDesktopWidget *temp = new QDesktopWidget();
        this->setFixedSize(temp->width()*0.5, temp->height()*0.5);
        delete temp;
    }

    QWidget *container = new QWidget(this);
    this->setCentralWidget(container);

    QGridLayout *layout = new QGridLayout;

//    QLabel *promptN = new QLabel(QString("Set the grid size"));
//    layout->addWidget(promptN, 0, 0, 1, N, Qt::AlignHCenter);

//    QSpinBox *getN = new QSpinBox;
//    layout->addWidget(getN, 1, 0, 1, N, Qt::AlignHCenter);

    // this is to change the grid value based on N

    N = 9;

    QLabel *mainText = new QLabel(QString("A 3X3 Sudoku Solver"));
    layout->addWidget(mainText, 2, 0, 1, N, Qt::AlignHCenter);

    std::vector<QSpinBox*> sudokuGrid;
    sudokuGrid.reserve(N*N);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            QSpinBox* box = new QSpinBox;
            box->setMinimum(0);
            box->setMaximum(N);
            box->setSpecialValueText(" ");
            sudokuGrid.push_back(box);
            layout->addWidget(box, i+3, j);
        }
    }

    QPushButton *generateSudoku = new QPushButton("Generate Sudoku");
    layout->addWidget(generateSudoku, N+3, 0, 1, N, Qt::AlignHCenter);

    QPushButton *verifySudoku = new QPushButton("Verify Sudoku");
    layout->addWidget(verifySudoku, N+4, 0, 1, N, Qt::AlignHCenter);

    QPushButton *solveSudoku = new QPushButton("Solve Sudoku");
    layout->addWidget(solveSudoku, N+5, 0, 1, N, Qt::AlignHCenter);

    container->setLayout(layout);
}

MainWindow::~MainWindow()
{

}

