#ifndef __BFS__
#define __BFS__

#include <queue>

using namespace std;

template<typename V, template<typename,typename> class E, typename D>
class BreadthFirstIterator {
public:
    BreadthFirstIterator(Graph<V,E,D>* g) : graph(g) {
        set<V*> vertices = graph->getAllVertices();
        
        vQueue.push(*(vertices.begin()));
    }
    
    BreadthFirstIterator(Graph<V,E,D>* g, V* s) : graph(g), startVertex(s) {
        vQueue.push(startVertex);
    }
    
    bool hasNext() {
        return !vQueue.empty();
    }
    
    V* getNext() {
        if (hasNext()) {
            V* current = vQueue.front();
            vQueue.pop();
            
            extendVisit(current);
            
            return current;    
        }
        return NULL;
    }
    
private:
    Graph<V,E,D>* graph;
    V* startVertex;
    queue<V*> vQueue;
    set<V*> markSet;
    
    void extendVisit(V* current) {
        set<V*> adjVertices = graph->verticesFrom(current);
        
        typename set<V*>::iterator it;
        
        for (it = adjVertices.begin(); it != adjVertices.end(); ++it) {
            V* v = *it;
            // not visited yet
            if (markSet.find(v) == markSet.end()) {
                vQueue.push(v);
                markSet.insert(v);
            }
        }
    }
};

#endif