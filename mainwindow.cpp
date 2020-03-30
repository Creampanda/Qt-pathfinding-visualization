#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(600,600);
    this->setFixedSize(600,600);

    int rectSize = 25;
    int rows = 20;
    int columns = 20;

    QPushButton* clearBtn = new QPushButton("Очистить поле");
    QPushButton* bfsBtn = new QPushButton("BFS");

    myGraph = new Graph(rectSize,rows,columns);

    connect(clearBtn, SIGNAL(clicked()), this, SLOT(newGraph));
    connect(bfsBtn, SIGNAL(clicked()), myGraph, SLOT(slotBFS()));

    QVBoxLayout* vboxlayout = new QVBoxLayout();
    vboxlayout->addWidget(myGraph);
    vboxlayout->addWidget(clearBtn);
    vboxlayout->addWidget(bfsBtn);

    myGraph->startingNode_ = 30;
    myGraph->targetNode_ = 195;

    this->centralWidget()->setLayout(vboxlayout);
}
MainWindow::~MainWindow()
{
    delete ui;
}





