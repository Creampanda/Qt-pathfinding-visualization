#include "node.h"
#include <algorithm>
#include <QGraphicsView>
#include <QThread>

Node::Node(int x, int y,QGraphicsItem* parent): QGraphicsItem(parent), x_(x), y_(y)
{
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
    id_ = Node::idGenerator_++;
}

QRectF Node::boundingRect() const
{
    return QRectF(x_,y_,size_,size_);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::white);
    if (Pressed)
    {
        brush.setColor(Qt::yellow);
    } else if (startingNode)
    {
        brush.setColor(Qt::red);
    } else if (targetNode)
    {
        brush.setColor(Qt::green);
    } else if (pathNode)
    {
        brush.setColor(Qt::blue);
    } else if (Visited)
    {
        brush.setColor(Qt::cyan);
    } else
    {
        brush.setColor(Qt::white);
    }
    painter->fillRect(boundingRect(),brush);
    painter->drawRect(boundingRect());
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = !Pressed;
    update();
    QGraphicsItem::mousePressEvent(event);
}

// Connect current node with other
void Node::adjustNode(Node* someNode)
{
    // Cheack if they already connected
    if (std::find(this->adjList_.begin(), this->adjList_.end(), someNode->getId()) == adjList_.end())
    {
        //adding Nodes to each others adjacent list
        this->adjList_.push_back(someNode->getId());
        someNode->adjList_.push_back(this->getId());
        std::sort(adjList_.begin(),adjList_.end());
    }
}

void Node::showNode()
{
    cout << "Node number " << this->id_ << " connected with: [ ";
    for (auto x : adjList_)
    {
        cout << x << " ";
    }
    cout << "]" << endl;

}

void Node::setStep(int step)
{
    this->steps_ = step;
}

int Node::getStep()
{
    return steps_;
}

QList<int> Node::getAdjList() {return	adjList_;}

QList<int>& Node::getAdjListRef() { return	adjList_; }

int Node::getId() { return id_; }

void Node::setAsStart()
{
    this->startingNode = true;
};

void Node::setAsEnd()
{
    this->targetNode = true;
}

void Node::setVisited()
{
    this->Visited = true;
}

void Node::setAsPath()
{
    this->pathNode = true;
    update();
};
