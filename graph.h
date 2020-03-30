#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class Graph : public QGraphicsView{
    Q_OBJECT
private:
    size_t rectSize_;
    size_t rows_ = 0;
    size_t columns_ = 0;
    size_t vertices_ = 0;
    //Storing all vertices
    QVector <Node*> nodeVector_;
    QGraphicsScene *scene;
public:

    Graph(size_t rectSize,size_t rows, size_t columns, QWidget* parent = 0);
    ~Graph();

    void addNode(Node* someNode);

    void showGraph();

    Node* getNode(const int i);

    void connectNodes(int src, int dest);

    void makeGrid();

    int startingNode_ = 0;
    int targetNode_ = 0;


    void BFS();

    QList<int> pathfinding();
    void showpath(QList<int> path);

    void disableNode(int node);

private slots:

    void slotClearAll();

    void slotBFS();


};

#endif // GRAPH_H
