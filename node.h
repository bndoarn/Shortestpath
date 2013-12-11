//definition of node class

#include <list>

using namespace std;

#ifndef NODE_H
#define NODE_H

class node
{
public:
    node(int k);
    void setKey(int k);
    void setStartTime(int t);
    void setFinishTime(int t);
    void setDistance(int d);
    int getKey() const;
    int getStartTime();
    int getFinishTime();
    int getDistance() const;
    bool visited();
    void markVisited();
    void markUnvisited();
    
private:
    int key;
    int distance;
    int start_time;
    int finish_time;
    bool visit;
};

#endif