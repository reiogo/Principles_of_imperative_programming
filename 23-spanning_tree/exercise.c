// Exercise 1
#include <stdlib.h>
// implement function that generates random permutation of a array using random
// number generator with rand library. asymptotic complexity?

int *generate_permutation (int *original, size_t size) {
    REQUIRES(original != NULL);
    for (size_t i = size - 1; i > 0; i--){
        size_t rvalue = rand() % (i+1);

        int tmp = original[i];
        original[i] = original[rvalue];
        original[rvalue] = tmp;
    }
    return original
}

// Exercise 2

// Prove that the cycle property implies the correctness of kruskal

// The cycle property: let C be a simple cycle in graph G, and e 
// be an edge of maximal weight in C. Then there is some MST of G that
// does not contain e.

// Kruskal: sort all edges by increasing weight order
// consider the edges in order. If edge does not create a cycle
// add it to the spanning tree. Otherwise discard it. Stop when v-1
// edges are added.

// assuming the original graph
// removing cycles by removing the maximal edges 
// will create minimun spanning trees.
//
// assuming the cycle property.
// if you rebuild the graph up to 
// v-1 edges from the smallest weights
// avoiding cycles then you avoid the
// maximal weight of every cycle in the 
// original graph you end up with a minimal spanning tree.
// 
// assuming the cycle property
// for every cycle in the original graph
// there is a mst that does not contain
// the maximal edge of each cyle.
//
//
// ai help:
// kruskal only creates edges that do not create cycles
// the edges that are skipped are greater than all of the edges before it (by sorting)
// kruskal avoids maximal edges that create cycles
// by the cycle property and kruskal ending on v-1 edges (making it a spanning tree)
// kruskal creates a mst.
//
//
// an edge e that kruskal skips because adding it would form a cycle in the current forest.
// since kruskal processes edges in increading order, all other edges in C are lighter than e
// thus e is the maximal weight edge in C.
// By the cycle property there exists an MST that does not include e. Therefore skipping e does
// not prevent kruskal from building an MST. repeating this argument for every skipped edge 
// shows that all edges kruskal adds are part of some mst, and since the edges are chosen
// greedily by weight the resulting tree is a spanning treee with minimal total weight
// making it a mst.
