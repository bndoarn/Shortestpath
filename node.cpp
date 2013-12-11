//implementation of node class

#include "node.h"

node::node(int k)
{
    key = k;
    start_time = 0;
    finish_time = 0;
    visit = false;
}

void node::setKey(int k)
{
    key = k;
}

void node::setStartTime(int t)
{
    start_time = t;
}

void node::setFinishTime(int t)
{
    finish_time = t;
}

void node::setDistance(int d)
{
    distance = d;
}

int node::getKey() const
{
    return key;
}

int node::getStartTime()
{
    return start_time;
}

int node::getFinishTime()
{
    return finish_time;
}

int node::getDistance() const
{
    return distance;
}

bool node::visited()
{
    return visit;
}

void node::markVisited()
{
    visit = true;
}

void node::markUnvisited()
{
    visit= false;
}