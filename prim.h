#ifndef __PRIM_MINIMUM_SPANNING_TREE__
#define __PRIM_MINIMUM_SPANNING_TREE__

#include <set>
#include <map>
#include "graph.h"

using namespace std;

template<typename V, template<typename,typename> class E, typename D> 
struct MinVerticeCompare {
private:
	static map<V*, E<V,D>*> distanceMap;
public:
  bool operator()(V* v1, V* v2) {
    E<V,D> *e1 = distanceMap[v1],
      *e2 = distanceMap[v2];

    D *d1 = e1->getData(),
    	*d2 = e2->getData();
           
    return (*d1) < (*d2) || ((*d1) == (*d2) && (v1 < v2));
  }

  void updateValue(V* key, E<V,D>* value) {
  	distanceMap[key] = value;
  }

  E<V,D>* getValue(V* key) {
  	return distanceMap[key];
  }

  bool contains(V* key) {
  	return distanceMap.find(key) != distanceMap.end();
  }
};

template<typename V, template<typename,typename> class E, typename D> 
map<V*, E<V,D>*> MinVerticeCompare<V,E,D>::distanceMap;

template<typename V, template<typename,typename> class E, typename D>
class PrimMinimumSpanningTree {
public:
private:
	typename Graph<V, E, D>::EdgeSet minimumSpanningTreeEdges;

public:
	PrimMinimumSpanningTree(Graph<V, E, D>& g) {
		
		// mark all g's vertices as unspanned
		set<V*> unspanned(g.getAllVertices());

		while (!unspanned.empty()) {

			// get the root of the tree
			typename set<V*>::iterator rootIt = unspanned.begin();
			// root is the root of a spanning tree
			// in case of multiple spanning trees (a forest)
			// then we'll have many roots, each is created in each iteration
			// of the current while loop
			V* root = *rootIt;

			// remove root from the unspanned
			unspanned.erase(rootIt);

			// Manage edges crossing the cut C = (S, V \ S), where S is set of
	    // already spanned vertices
			// we use the set (implemented by RB-tree) as the priority queue
			// for the cut-crossing edges' end vertices V \ S

			typedef set<V*,  MinVerticeCompare<V,E,D> > MinVerPriorityQueue;
	    
	    MinVerticeCompare<V,E,D> minCmp;

			MinVerPriorityQueue mQueue(minCmp);

			typename Graph<V, E, D>::EdgeSetIterator it;
			typename Graph<V, E, D>::EdgeSet outEdges = g.edgesFrom(root);
			// the queue is started with root's out-edges
			for (it = outEdges.begin(); it != outEdges.end(); ++it) {
				V *outVer = (*it)->getTarget();

				minCmp.updateValue(outVer, *it);
				mQueue.insert(outVer);
			}

			// iterator to the front of the queue
			typename MinVerPriorityQueue::iterator minIt;

			// now get the next smallest cut, 
	    // and update all the cuts' distances each iteration
	    // until the queue is empty

			while (!mQueue.empty()) {
				minIt = mQueue.begin();

				// the current min vertice
				V* minVer = *minIt;
				// remove it from queue
				mQueue.erase(minIt);

				// if both are already spanned, skip this edge
				if (unspanned.find(minVer) == unspanned.end()) {
				 	continue;
				}

				// remove it from unspanned
				unspanned.erase(minVer);

				// insert the new edge
				minimumSpanningTreeEdges.insert(minCmp.getValue(minVer));

				outEdges = g.edgesFrom(minVer);

				// adding or update the distance of neighboring of minVer
				for (it = outEdges.begin(); it != outEdges.end(); ++it) {
					V *outVer = (*it)->getTarget();
					// skip spanned vertices
					if (unspanned.find(outVer) == unspanned.end())
						continue;
					
					D *weight = (*it)->getData();

					// if the outVer is already in queue
					if (minCmp.contains(outVer) && mQueue.find(outVer) != mQueue.end()) {
						// if its the new weight is more optimal, update
						if (*(minCmp.getValue(outVer)->getData()) > *weight) {
							mQueue.erase(outVer);
							minCmp.updateValue(outVer, *it);
							mQueue.insert(outVer);
						}
						// or else just skip this
					} else {
						// if not, insert to queue
						minCmp.updateValue(outVer, *it);
						mQueue.insert(outVer);
					}
				}
			}
		}
	}

	typename Graph<V, E, D>::EdgeSet& getMinimumSpanningTreeEdges() {
		return minimumSpanningTreeEdges;
	}
};

#endif