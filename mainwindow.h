#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void createNewGraph();
    void slotWarningMsg(QString text);

private:
    Ui::MainWindow *ui;
    QGraphicsView* view;
    Graph *myGraph;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);


    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
