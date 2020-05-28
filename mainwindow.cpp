#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(650,650);
    this->setFixedSize(650,650);

    int rectSize = 25;
    int rows = 20;
    int columns = 20;

    QPushButton* clearBtn = new QPushButton("Очистить поле");
    QPushButton* bfsBtn = new QPushButton("BFS");
    QPushButton* saveBtn = new QPushButton("Save to file");
    QPushButton* loadBtn = new QPushButton("Load from file");

    myGraph = new Graph(rectSize,rows,columns);

    view = new QGraphicsView(this);
    view->setScene(myGraph);

    connect(clearBtn, SIGNAL(clicked()), myGraph, SLOT(slotClearAll()));
    connect(bfsBtn, SIGNAL(clicked()), myGraph, SLOT(slotBFS()));

    connect(saveBtn, SIGNAL(clicked()), myGraph, SLOT(slotSaveGraph()));

    connect(loadBtn, SIGNAL(clicked()), myGraph, SLOT(slotLoadGraph()));
    connect(myGraph,&Graph::signalWarningBfs, this, &MainWindow::slotWarningMsg);

    QLabel *label1 = new QLabel(this);
    label1->setText("Press 'S' and click to select START. Press 'E' and click to select END. (English keyboard layout!!) ");
    QVBoxLayout* vboxlayout = new QVBoxLayout();
    vboxlayout->addWidget(label1);
    vboxlayout->addWidget(view);
    vboxlayout->addWidget(clearBtn);
    vboxlayout->addWidget(bfsBtn);
    vboxlayout->addWidget(saveBtn);
    vboxlayout->addWidget(loadBtn);


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






