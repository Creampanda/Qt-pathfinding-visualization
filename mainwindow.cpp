#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QMessageBox>

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

    view = new QGraphicsView(this);
    view->setScene(myGraph);

    connect(clearBtn, SIGNAL(clicked()), myGraph, SLOT(slotClearAll()));
    connect(bfsBtn, SIGNAL(clicked()), myGraph, SLOT(slotBFS()));
    connect(myGraph,&Graph::signalWarningBfs, this, &MainWindow::slotWarningMsg);

    QVBoxLayout* vboxlayout = new QVBoxLayout();
    vboxlayout->addWidget(view);
    vboxlayout->addWidget(clearBtn);
    vboxlayout->addWidget(bfsBtn);


    this->centralWidget()->setLayout(vboxlayout);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotWarningMsg(QString text)
{
    QMessageBox::warning(this,"Warning!", text);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S)
        myGraph->setStartFlag(true);
    if (event->key() == Qt::Key_E)
        myGraph->setTargetFlag(true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S)
        myGraph->setStartFlag(false);
    if (event->key() == Qt::Key_E)
        myGraph->setTargetFlag(false);
}






