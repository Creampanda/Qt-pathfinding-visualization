#include "graph.h"
#include <QQueue>
#include <QFile>
#include <QTextStream>
#include <string>
#include <QFileDialog>
#define DEBUG
//Getting our grid size [N*N]
Graph::Graph(size_t rectSize, size_t rows, size_t columns, QWidget* parent)
    :  QGraphicsScene(parent), rectSize_(rectSize), rows_(rows), columns_(columns)
{
    vertices_ = rows_ * columns_;

    int width = rectSize * columns;
    int height = rectSize * rows;

    for (int i=0; i < height; i+=rectSize)
    {
        for (int j=0; j < width; j+=rectSize)
        {
            Node *item = new Node(j,i);
            this->addNode(item);
            this->addItem(item);
            connect(item,&Node::signalWasClicked,this,&Graph::slotClickHandler);
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
    slotClearBeforeBFS();
    int startingNode = startingNode_;
    int targetNode = targetNode_;
    update();
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

                this->advance();
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

bool Graph::getStartFlag()
{
    return startFlag_;
}

void Graph::setStartFlag(bool flag)
{
    startFlag_ = flag;
}
bool Graph::getTargetFlag()
{
    return targetFlag_;
}

void Graph::setTargetFlag(bool flag)
{
    targetFlag_ = flag;
}

void Graph::slotDisableNode(int nodeId)
{
    for (auto i = nodeVector_.at(nodeId)->getAdjListRef().begin(); i != nodeVector_.at(nodeId)->getAdjListRef().end(); i++)
    {
        nodeVector_.at(*i)->getAdjListRef().removeOne(nodeId);
    }

    nodeVector_.at(nodeId)->getAdjListRef().clear();
}

void Graph::slotEnableNode(int node)
{
    if (node % columns_ == 0)
    {
        connectNodes(node, node + 1);
    } else if (node % columns_ == columns_ - 1)
    {
        connectNodes(node, node - 1);
    } else
    {
        connectNodes(node, node + 1);
        connectNodes(node, node - 1);
    }
    if (node < (int) columns_)
    {
        connectNodes(node, node + columns_);
    } else if (node + columns_ > vertices_)
    {
        connectNodes(node,node - columns_);
    } else
    {
        connectNodes(node, node + columns_);
        connectNodes(node,node - columns_);
    }
}

void Graph::slotSetStart(int node)
{
    startingNode_ = node;
}

void Graph::slotSetTarget(int node)
{
    targetNode_ = node;
}

void Graph::slotClickHandler(int node)
{
    if (startFlag_)
    {
       if(startingNode_ >= 0) nodeVector_.at(startingNode_)->startingNode = false;
       startingNode_ = node;
       nodeVector_.at(node)->setAsStart();
       update();
    }
    else if (targetFlag_)
    {
        if(targetNode_ >= 0)nodeVector_.at(targetNode_)->targetNode = false;
        targetNode_ = node;
        nodeVector_.at(node)->setAsEnd();
        update();
    } else if(nodeVector_.at(node)->Pressed)
    {
        slotEnableNode(node);
        nodeVector_.at(node)->Pressed = 0;
    } else if (!nodeVector_.at(node)->Pressed)
    {
        slotDisableNode(node);
        nodeVector_.at(node)->Pressed = 1;
    }
}

void Graph::slotSaveGraph()
{
    QString strFilter;
    QString str =
            QFileDialog::getSaveFileName(0,tr("Save graph"),"*.txt",strFilter);


    QFile file(str);

    file.open(QFile::WriteOnly);
   /* if (!str.isEmpty())
    {
        if (strFilter.contains("txt"))
        {
        }
    }*/


    QTextStream out(&file);

    out << 777 << endl;

    for (auto x : nodeVector_)
    {
        int id = x->getId();
        if (x->targetNode) out << 2 << " " << id << endl;
        else if (x->Pressed) out << 0 << " " << id << endl;
        else if (x->startingNode) out << 1 << " " << id << endl;
    }
    out << 777 << " " << 777 << endl;
    file.close();
}

void Graph::slotLoadGraph()
{
    QString strFilter;
    QString str =
            QFileDialog::getOpenFileName(0,tr("Save graph"),"*.txt",strFilter);


    QFile file(str);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    int a,b;
    in >> a;
    if (a != 777)
    {
        file.close();
        return;
    }

    this->slotClearAll();
    while(1) {
        in >> a >> b;
        if (a == 777 && b == 777) break;
        if(in.status() != QTextStream::Ok) break;
        switch (a)
        {
            case 0:
                nodeVector_[b]->Pressed = 1;
                slotDisableNode(b);
                break;
            case 1:
                nodeVector_[b]->setAsStart();
                slotSetStart(b);
                break;
            case 2:
                nodeVector_[b]->setAsEnd();
                slotSetTarget(b);
                break;
        }
    }
    update();
    file.close();
}

void Graph::slotClearAll()
{
    for(auto node : nodeVector_)
    {
        node->resetAll();
    }
    makeGrid();
    startingNode_ = -1;
    targetNode_ = -1;
    update();
}

void Graph::slotClearBeforeBFS()
{
    for(auto node : nodeVector_)
    {
        node->resetBeforeBFS();
    }

    update();
}

#include <QMessageBox>
void Graph::slotBFS()
{
    if (startingNode_ >= 0 && targetNode_ >= 0)
        BFS();
    else
        emit signalWarningBfs("You should select start and end!");
}
