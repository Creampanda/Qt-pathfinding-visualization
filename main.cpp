#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "graph.h"

int Node::idGenerator_ = 0;


int main(int argc, char *argv[])
{
    int rectSize = 25;
    int rows = 20;
    int columns = 20;
    int width = rectSize * columns;
    int height = rectSize * rows;
    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene* scene = new QGraphicsScene(0,0,width,height);
    view.setScene(scene);
    scene->setBackgroundBrush(Qt::white);

    Graph graph(rows,columns);


    for (int i=0; i < height; i+=rectSize)
    {
        for (int j=0; j < width; j+=rectSize)
        {
            Node *item = new Node(j,i);
            graph.addNode(item);
            scene->addItem(item);
        }
    }
    graph.showGraph();
    graph.makeGrid();
    graph.showGraph();
    graph.BFS(46,132);

    view.show();
    return a.exec();
}
