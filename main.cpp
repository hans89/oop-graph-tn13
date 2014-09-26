#include <iostream>
#include "graph.h"
#include "bfs.h"
#include "dfs.h"

using namespace std;

int main(void) {
    typedef Graph<int, DefaultEdge, double> IntWIGraph;
    
    IntWIGraph g;
    
    int v[6] = {0,1,2,3,4,5};
    double data[7] = {0.2,1.3,2.4,3.5,4.6,5.7,6.8};
    
    g.addEdge(&v[0], &v[1], &data[2]);
    g.addEdge(&v[0], &v[2], &data[1]);
    g.addEdge(&v[1], &v[2], &data[2]);
    g.addEdge(&v[1], &v[4], &data[3]);
    g.addEdge(&v[2], &v[4], &data[5]);
    g.addEdge(&v[3], &v[1], &data[1]);
    g.addEdge(&v[4], &v[3], &data[6]);
    
    BreadthFirstIterator<int, DefaultEdge, double> bfs(&g);
    
    while (bfs.hasNext()) {
        int *v = bfs.getNext();
        
        cout << *v << endl;
    }
    
    g.printEdges();
    
    // IntWIGraph::EdgeSet edges = g.edgesFrom(&v[4]);
    
    // IntWIGraph::EdgeSetIterator it;
    
    // for (it = edges.begin(); it != edges.end(); ++it) {
    //     DefaultEdge<int,int>* edge = *it;
        
    //     edge->print();
    // }
    
    typedef Graph<char, DefaultEdge, int> IntWCGraph;
    
    char l[] ="abcdefgh";
    
    IntWCGraph cGraph;
    
    cGraph.addEdge(&l[0], &l[1]); // a->b
    cGraph.addEdge(&l[0], &l[2]); // a->c
    cGraph.addEdge(&l[1], &l[3]); // b->d
    cGraph.addEdge(&l[1], &l[4]); // b->e
    cGraph.addEdge(&l[4], &l[7]); // e->h
    cGraph.addEdge(&l[2], &l[5]); // c->f
    cGraph.addEdge(&l[2], &l[6]); // c->g
    
    BreadthFirstIterator<char, DefaultEdge, int> cBFS(&cGraph);
    
    while (cBFS.hasNext()) {
        char *v = cBFS.getNext();
        
        cout << *v << endl;
    }
    
    cout << endl;
    
    DepthFirstIterator<char, DefaultEdge, int> cDFS(&cGraph);
    
    while (cDFS.hasNext()) {
        char *v = cDFS.getNext();
        
        cout << *v << endl;
    }
    
    return 0;
}