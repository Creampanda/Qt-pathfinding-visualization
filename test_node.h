#ifndef TEST_NODE_H
#define TEST_NODE_H

#include <QTest>
#include <QObject>

class Test_node : public QObject
{
    Q_OBJECT
public:
    explicit Test_node(QObject *parent = nullptr);

signals:

};

#endif // TEST_NODE_H
