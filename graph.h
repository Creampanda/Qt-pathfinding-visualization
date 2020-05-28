#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class Graph : public QGraphicsScene{
    Q_OBJECT
private:
    size_t rectSize_;
    size_t rows_ = 0;
    size_t columns_ = 0;
    size_t vertices_ = 0;
    //Storing all vertices
    QVector <Node*> nodeVector_;
    bool startFlag_ = false;
    bool targetFlag_ = false;

    int startingNode_ = -1;
    int targetNode_ = -1;
    QString saveFile_ = "F:/MyProjects/CPP/BFS/BFS/testfile.txt";
    QString loadFile_ = "F:/MyProjects/CPP/BFS/BFS/testfile.txt";
public:

    Graph(size_t rectSize,size_t rows, size_t columns, QWidget* parent = 0);
    ~Graph();

    void addNode(Node* someNode);

    void showGraph();

    Node* getNode(const int i);

    void connectNodes(int src, int dest);

    void makeGrid();



    void BFS();

    QList<int> pathfinding();
    void showpath(QList<int> path);

    bool getStartFlag();
    void setStartFlag(bool flag);

    bool getTargetFlag();
    void setTargetFlag(bool flag);

private slots:

    void slotClearAll();

    void slotClearBeforeBFS();

    void slotBFS();

    void slotDisableNode(int node);

    void slotEnableNode(int node);

    void slotSetStart(int node);

    void slotSetTarget(int node);

    void slotClickHandler(int node);

    void slotSaveGraph();
    void slotLoadGraph();

signals:
    void signalWarningBfs(QString text);

};

#endif // GRAPH_H
