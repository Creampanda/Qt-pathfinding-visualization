#include "graph.h"
#include <QQueue>
#define DEBUG
//Getting our grid size [N*N]
Graph::Graph(size_t rectSize, size_t rows, size_t columns, QWidget* parent)
    :  QGraphicsView(parent), rectSize_(rectSize), rows_(rows), columns_(columns)
{
    vertices_ = rows_ * columns_;

    int width = rectSize * columns;
    int height = rectSize * rows;

    scene = new QGraphicsScene();
    this->setScene(scene);


    for (int i=0; i < height; i+=rectSize)
    {
        for (int j=0; j < width; j+=rectSize)
        {
            Node *item = new Node(j,i);
            this->addNode(item);
            scene->addItem(item);
        }
    }

    makeGrid();
}

Graph::~Graph()
{

}

void Graph::addNode(Node* someNode)
{
    nodeVector_.push_back(someNode);
}

void Graph::showGraph()
{
    for (auto x : nodeVector_) x->showNode();
}

Node* Graph::getNode(const int i) { return nodeVector_[i]; }

void Graph::connectNodes(int src, int dest)
{
    nodeVector_[src]->adjustNode(nodeVector_[dest]);
}

//Creating grid by connectin vertices (like matrix N*N)
void Graph::makeGrid()
{
    for (size_t i = 0; i < columns_; ++i)
    {
        size_t node1 = i;
        size_t node2 = i + columns_;
        while(node2 < columns_ * rows_)
        {
            connectNodes(node1,node2);
            node1 = node2;
            node2 += columns_;
        }
    }
    for (size_t i = 0; i < rows_ * columns_; i+= columns_)
    {
        size_t node1 = i;
        size_t node2 = i + 1;
        while(node2 < (columns_ + i))
        {
            connectNodes(node1,node2);
            node1 = node2;
            ++node2;
        }
    }

}


// breadth-first search
void Graph::BFS()
{
    int startingNode = startingNode_;
    int targetNode = targetNode_;
    nodeVector_.at(startingNode)->setAsStart();
    nodeVector_.at(targetNode)->setAsEnd();
    nodeVector_.at(startingNode)->setStep(0);
    //Bool array for visited vertices
    bool* visited = new bool[vertices_];
    for (size_t i = 0; i < vertices_; i++)
    {
        visited[i] = false;
    }

    QQueue <int> queue;
    visited[startingNode] = true;
    queue.enqueue(startingNode);

    //While there are still not visited vertices in the graph
    while (!queue.isEmpty())
    {
        int current = queue.dequeue();

        //Getting current vertex adjacent list
        QList<int> currentNodeAdjList = nodeVector_.at(current)->getAdjList();
#ifdef DEBUG
        cout << "Checking adj list for vertex " << current << endl;
#endif
        for (auto i = currentNodeAdjList.begin(); i!= currentNodeAdjList.end(); ++i )
        {

            if (*i == targetNode)
            {
                #ifdef DEBUG
                cout << "We found target Node!! It's connected with " << current << endl;
                #endif
                nodeVector_.at(*i)->setStep(nodeVector_.at(current)->getStep() + 1);
                #ifdef DEBUG
                cout << "Can get here by " << nodeVector_.at(*i)->getStep() << " steps!" << endl;
                #endif
                QList <int> path = this->pathfinding();
                #ifdef DEBUG
                this->showpath(path);
                #endif
                return;
            }
            if (!visited[*i])
            {
                // Setting how many step it takes to get to that node
                nodeVector_.at(*i)->setStep(nodeVector_.at(current)->getStep() + 1);
                #ifdef DEBUG
                cout << "Amount steps to " << nodeVector_.at(*i)->getId() << " : " << nodeVector_.at(*i)->getStep() << endl;
                cout << "Visit and enqueue " << *i << endl;
                #endif
                visited[*i] = true;
                nodeVector_.at(*i)->setVisited();
                queue.enqueue(*i);
            }
        }
    }
    #ifdef DEBUG
    cout << "Sorry! Can't find a path to node!" << endl;
    #endif
}


QList<int> Graph::pathfinding()
{
    int currentNode = targetNode_;
    QList<int> path;
    while (nodeVector_.at(currentNode)->getStep() != 0)
    {
        QList<int> currentNodeAdjList = nodeVector_.at(currentNode)->getAdjList();

        int nextstep;
        for (auto i = currentNodeAdjList.begin(); i != currentNodeAdjList.end(); ++i)
        {
            if (nodeVector_.at(*i)->getStep() >= 0)
            {
                nextstep = *i;
                break;
            }
        }
        for (auto i = currentNodeAdjList.begin(); i != currentNodeAdjList.end(); ++i)
        {
            if (nodeVector_.at(*i)->getStep() >= 0)
            {
                if (nodeVector_.at(*i)->getStep() < nodeVector_.at(nextstep)->getStep())
                {
                    nextstep = *i;
                }
            }

        }

        currentNode = nextstep;
        path.push_front(nextstep);
        this->nodeVector_.at(nextstep)->setAsPath();
    }

    path.push_back(targetNode_);

    return path;
}

void Graph::showpath(QList<int> path)
{
    auto i = path.begin();
    cout << *(i++);
    while (i != path.end())
    {
        cout << " -> " << *i++;
    }

    cout << endl;
}

void Graph::disableNode(int nodeId)
{
    for (auto i = nodeVector_.at(nodeId)->getAdjListRef().begin(); i != nodeVector_.at(nodeId)->getAdjListRef().end(); i++)
    {
        nodeVector_.at(*i)->getAdjListRef().removeOne(nodeId);
    }

    nodeVector_.at(nodeId)->getAdjListRef().clear();
}

void Graph::slotClearAll()
{
    for(auto node : nodeVector_)
    {
        node->Pressed = false;
        node->startingNode = false;
        node->targetNode = false;
        node->Visited = false;
        node->pathNode = false;
    }
    makeGrid();
    update();
}

#include <QMessageBox>
void Graph::slotBFS()
{
    QMessageBox::information(this,"Title","sfasfA");
    BFS();
}
