/*
 Name: Brandon Craven
 Class: COP4531
 Assignment: Programming Assignment 3
 Date: December 10, 2013
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <limits>
#include <cstdlib>
#include "node.h"
#include "comparison.h"

using namespace std;

//a priority queue for dijkstra
typedef priority_queue<node*, vector<node*>, comparison> node_queue;

//struct for node with weight to node
typedef struct {
    node* nodes;
    int weight;
} nodestruct;

//dijkstra's algorithms
vector<node*> Dijkstra(vector< list<nodestruct> > &graph, vector<node*> &nodes, int start);

//relax nodes
void Relax(node* u, node* v, int w);

//rebuild the queue
void Rebuild(node_queue &Q);

//convert enum to char
string OutputNode(int i);

//enum for nodes
enum nodeLetter { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};

int main (int argc, const char * argv[])
{
    vector< list<nodestruct> > graph;
    vector<node*> nodes;
    vector<node*> S;
    vector<nodeLetter> sources, destinations;
    vector<int> weights;
    ifstream inFile;
    ofstream outFile;
    char source;
    char destination;
    int weight;
    int size;
    nodeLetter start;
    int k;
    string graph_type;
    bool directed = false;
    bool get_type = true;
    
    //check number of arguments
    if (argc != 4)
    {
        cout << "usage: ./shortestpath.x <filename> <source> <k>\n";
        return 1;
    }
    
    //set start and k
    start = (nodeLetter)(argv[2][0] - 65);
    k = atoi(argv[3]);
    
    //open file
    inFile.open(argv[1]);
    
    if(inFile)
    {
        //get sources and destinations
        while (inFile)
        {
            //ignore comments
            if (inFile.peek() == '#')
            {
                inFile.ignore(180, '\n');
                continue;
            }
            
            //get type of graph
            if (get_type)
            {
                get_type = false;
                
                inFile >> graph_type;
                
                if (graph_type == "D")
                    directed = true;
                
                continue;
            }
            
            //get sources, destinations, and weight
            inFile >> source >> destination >> weight;
            
            //add information to vectors
            sources.push_back(static_cast<nodeLetter>(source - 65));
            destinations.push_back(static_cast<nodeLetter>(destination - 65));
            weights.push_back(weight);
            
            if (!directed)
            {
                //if undirected, add reverse edge
                sources.push_back(static_cast<nodeLetter>(destination - 65));
                destinations.push_back(static_cast<nodeLetter>(source - 65));
                weights.push_back(weight);
            }
            
            inFile.ignore(80, '\n');
        }
        
        size = (int)sources.size();
        
        //creat a list of all nodes
        for (int i = 0; i < size; i++)
        {
            if (nodes.size() < (int)sources[i]+1)
                nodes.resize((int)sources[i]+1);
            
            if(nodes[sources[i]] == NULL)
                nodes[sources[i]] = new node(sources[i]);
            
            if (nodes.size() < destinations[i]+1)
                nodes.resize(destinations[i]+1);
            
            if(nodes[destinations[i]] == NULL)
                nodes[destinations[i]] = new node(destinations[i]);
        }
        
        //create graph
        for (int i = 0; i < size; i++)
        {
            nodestruct temp;
            
            if (graph.size() < sources[i]+1)
                graph.resize(sources[i]+1);
            
            temp.nodes = nodes[destinations[i]];
            temp.weight = weights[i];
            
            graph[sources[i]].push_back(temp);
        }
        
        //clear these since we're done using them
        sources.clear();
        destinations.clear();
        weights.clear();
        
        //perform dijkstra's algorithms
        S = Dijkstra(graph, nodes, start);
        
        outFile.open("out.txt");
        
        //output dijkstra's results
        outFile << "Dijkstra\n";
        outFile << "Source: " << OutputNode(S[0]->getKey()) << "\n";
        
        size = (int)nodes.size();
        
        for (int i = 0; i < size; i++)
        {
            if (nodes[i] != S[0])
                outFile << "Node " << OutputNode(nodes[i]->getKey()) << ": " << nodes[i]->getDistance() << "\n";
        }
        outFile << "End Dijkstra\n";
        
        //couldn't figure out this one
        outFile << "\n\nShortest Reliable Paths Algorithm\n";
        outFile << "I don't know how to do this one :(\n";
        outFile << "End Shortest Reliable Paths Algorithm\n";
        outFile.close();
        
    }
    else
    {
        //bad file name
        cout << "error: Invalid filename\n";
        return 1;
    }
    
    inFile.clear();
    inFile.close();
    
    return 0;
}

vector<node*> Dijkstra(vector< list<nodestruct> > &graph, vector<node*> &nodes, int start)
{
    vector<node*> S;
    node_queue Q (comparison(true));
    list<nodestruct>::iterator itr;
    node* u;
    int size = (int)nodes.size();
    
    //set source distance to 0
    //set all others to max value of int
    for (int i = 0; i < size; i++)
    {
        if (i == start)
            nodes[i]->setDistance(0);
        else
            nodes[i]->setDistance(numeric_limits<int>::max());
        
    }
    
    //push all the nodes into the queue
    for (int i = 0; i < size; i++)
    {
        Q.push(nodes[i]);
    }
    
    //while the queue isn't empty
    while(!Q.empty())
    {
        u = Q.top();            //set u to the min
        Q.pop();                //extract the min
        S.push_back(u);         //add u to S
        
        u->markVisited();       //mark vistied
        
        //initalize the iterator
        itr = graph[u->getKey()].begin();
        
        //relax adjacent nodes
        while (itr != graph[u->getKey()].end())
        {
            if (!((*itr).nodes->visited()))
                Relax(u, (*itr).nodes, (*itr).weight);
            itr++;
        }
        
        //rebuild the queue
        Rebuild(Q);
    }
    
    return S;
    
}

void Relax(node* u, node* v, int w)
{
    //set the distance if it's shorter
    if ((u->getDistance() + w) < v->getDistance())
    {
        v->setDistance(u->getDistance() + w);
    }
}

void Rebuild(node_queue &Q)
{
    //create a new queue
    node_queue R;
    
    //empty it just incase
    while (!R.empty())
    {
        R.pop();
    }
    
    //add Q elements to R
    while (!Q.empty())
    {
        R.push(Q.top());
        Q.pop();
    }
    
    //add R elements back to Q
    while (!R.empty())
    {
        Q.push(R.top());
        R.pop();
    }
}

string OutputNode(int i)
{
    switch (i)
    {
        case 0: return "A";
        case 1: return "B";
        case 2: return "C";
        case 3: return "D";
        case 4: return "E";
        case 5: return "F";
        case 6: return "G";
        case 7: return "H";
        case 8: return "I";
        case 9: return "J";
        case 10: return "K";
        case 11: return "L";
        case 12: return "M";
        case 13: return "N";
        case 14: return "O";
        case 15: return "P";
        case 16: return "Q";
        case 17: return "R";
        case 18: return "S";
        case 19: return "T";
        case 20: return "U";
        case 21: return "V";
        case 22: return "W";
        case 23: return "X";
        case 24: return "Y";
        case 25: return "Z";
    }
    
    return "ERROR";
}