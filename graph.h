#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

class Graph{
    size_t rows_ = 0;
    size_t columns_ = 0;
    size_t vertices_ = 0;
    //Storing all vertices
    QVector <Node*> nodeVector_;
public:

    Graph(size_t rows, size_t columns);


    void addNode(Node* someNode);

    void showGraph();

    Node* getNode(const int i);

    void connectNodes(int src, int dest);

    void makeGrid();

    void BFS(int startingNode, int targetNode);

    QList<int> pathfinding(int targetNode);
    void showpath(QList<int> path);

    void disableNode(int node);

};

#endif // GRAPH_H
