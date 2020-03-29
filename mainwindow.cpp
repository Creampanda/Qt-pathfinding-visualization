#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int rectSize = 25;
    int rows = 20;
    int columns = 20;


    Graph* view = new Graph(rectSize,rows,columns);

    this->setCentralWidget(view);


}
MainWindow::~MainWindow()
{
    delete ui;
}



