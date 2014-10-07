#ifndef __DFS__
#define __DFS__

#include <stack>

using namespace std;

template<typename V, template<typename,typename> class E, typename D>
class DepthFirstIterator {
public:
    DepthFirstIterator(Graph<V,E,D>* g) : graph(g) {
        set<V*> vertices = graph->getAllVertices();
        
        vStack.push(*(vertices.begin()));
    }
    
    DepthFirstIterator(Graph<V,E,D>* g, V* s) : graph(g), startVertex(s) {
        vStack.push(startVertex);
    }
    
    bool hasNext() {
        return !vStack.empty();
    }
    
    V* getNext() {
        if (hasNext()) {
            V* current = vStack.top();
            vStack.pop();
            
            extendVisit(current);
            
            return current;    
        }
        return NULL;
    }
    
private:
    Graph<V,E,D>* graph;
    V* startVertex;
    stack<V*> vStack;
    set<V*> markSet;
    
    void extendVisit(V* current) {
        set<V*> adjVertices = graph->verticesFrom(current);
        
        typename set<V*>::iterator it;
        
        for (it = adjVertices.begin(); it != adjVertices.end(); ++it) {
            V* v = *it;
            // not visited yet
            if (markSet.find(v) == markSet.end()) {
                vStack.push(v);
                markSet.insert(v);
            }
        }
    }
};

#endif