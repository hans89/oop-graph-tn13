#include <set>

using namespace std;

template<typename V, typename D>
class DefaultEdge {
public:
    DefaultEdge(V* s, V* t, D* d = NULL) : source(s), target(t), data(d) {}
    
    V* getSource() { 
        return source;
    }
    
    V* getTarget() {
        return target;
    }
    
    D* getData() {
        return data;
    }
    
    void print() {
        if (data != NULL)
            cout << *source << " -" << *data << "-> " << *target << endl;
        else 
            cout << *source << " --> " << *target << endl;
    }
    
private:
    V *source, *target;
    D *data;
};

template<template<typename,typename> class E, typename V, typename D> 
struct EdgeCompare {
    bool operator()(E<V,D>* firstEdge, E<V,D>* secondEdge) {
        V   *s1 = firstEdge->getSource(),
            *e1 = firstEdge->getTarget(),
            *s2 = secondEdge->getSource(),
            *e2 = secondEdge->getTarget();
             
        return (s1 < s2) || ((s1 == s2) && (e1 < e2));
    }
};

template<typename V, template<typename, typename> class E, typename D>
class Graph {
public:
    typedef set<E<V,D>*, EdgeCompare<E,V,D>> EdgeSet;
    typedef typename EdgeSet::iterator EdgeSetIterator;
    
    Graph(set<V*> vs, EdgeSet es)
        : vertices(vs), edges(es) {}
        
    Graph() {}
    
    E<V,D>* addEdge(V* source, V* target, D* data = NULL) {
        
        vertices.insert(source);
        vertices.insert(target);
        
        E<V,D>* newEdge = new E<V,D>(source, target, data);
        
        EdgeSetIterator it = edges.find(newEdge);
            
        if (it == edges.end()) {
            edges.insert(newEdge);    
            return newEdge;
        } else {
            delete newEdge;
            return *it;
        }
    }
    
    set<V*> getAllVertices() {
        return vertices;
    }
    
    set<V*> verticesFrom(V* source) {
        set<V*> fromVertices;
        
        EdgeSetIterator it;
        for (it = edges.begin(); it != edges.end(); ++it) {
            E<V,D>* edge = *it;
            
            if (edge->getSource() == source) {
                fromVertices.insert(edge->getTarget());
            }
        }
        return fromVertices;
    }
    
    set<V*> verticesTo(V* target) {
        set<V*> toVertices;
        
        EdgeSetIterator it;
        for (it = edges.begin(); it != edges.end(); ++it) {
            E<V,D>* edge = *it;
            
            if (edge->getTarget() == target) {
                toVertices.insert(edge->getTarget());
            }
        }
        return toVertices;
    }
    
    EdgeSet getAllEdges() {
        return edges;
    }
    
    EdgeSet edgesFrom(V* source) {
        EdgeSet fromEdges;
        
        EdgeSetIterator it;
        for (it = edges.begin(); it != edges.end(); ++it) {
            E<V,D>* edge = *it;
            
            if (edge->getSource() == source) {
                fromEdges.insert(edge);
            }
        }
        return fromEdges;
    }
    
    EdgeSet edgesTo(V* target) {
        EdgeSet toEdges;
        
        EdgeSetIterator it;
        for (it = edges.begin(); it != edges.end(); ++it) {
            E<V,D>* edge = *it;
            
            if (edge->getTarget() == target) {
                toEdges.insert(edge);
            }
        }
        return toEdges;
    }
    
    ~Graph() {
        EdgeSetIterator it;
        for (it = edges.begin(); it != edges.end(); ++it)
            delete (*it);
    }
    
    void printEdges() {
        EdgeSetIterator it;
        for (it = edges.begin(); it != edges.end(); ++it)
            (*it)->print();
    }
private:
    set<V*> vertices;
    EdgeSet edges;
};
