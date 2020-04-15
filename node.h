#ifndef NODE_H
#define NODE_H
#include <QGraphicsItem>
#include <QList>
#include <iostream>
#include <QVector>
#include <QObject>

using std::cout;
using std::endl;


class Node: public QObject, public QGraphicsItem
{
    Q_OBJECT
    int x_ = 0;
    int y_ = 0;
    int size_ = 25;

    //Unique vertex ID generator
    static int idGenerator_;
    //Vertex ID
    int id_;
    // Adjacent list for all connected vertexes
    QList <int> adjList_;
    // Steps from starting node
    int steps_ = -1;


protected:
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem *option,
               QWidget * widget) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


public:    
    Node(int x = 0, int y = 0, QGraphicsItem* parent = NULL);

    // Connect current node with other
    void adjustNode(Node* someNode);

    //Show current node with all connections
    void showNode();

    void setStep(int step);

    int getStep();

    QList<int> getAdjList();

    QList<int> & getAdjListRef();

    int getId();
    bool Pressed = false;
    bool startingNode = false;
    bool targetNode = false;
    bool Visited = false;
    bool pathNode = false;

    void setAsStart();
    void setAsEnd();
    void setVisited();
    void setAsPath();

    void resetAll();
    void resetBeforeBFS();
signals:
    void signalWasClicked(int id);
    void signalDisableNode(int id);
    void signalEnableNode(int id);

    void signalSetStart(int id);
    void signalSetTarget(int id);
};
#endif // NODE_H
