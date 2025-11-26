/* Union-find testing via Kruskal's algorithm
 * 15-122 Principles of Imperative Computation, Fall 2010
    Frank Pfenning,
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/graph.h"
#include "kruskal.h"


// pre-sorted edge list
graph_t nine_edges() {
  graph_t G = graph_new(6);

  graph_addedge(G, 0, 3, 1);
  graph_addedge(G, 4, 5, 2);
  graph_addedge(G, 2, 4, 3);
  graph_addedge(G, 4, 3, 5);
  graph_addedge(G, 3, 5, 5);
  graph_addedge(G, 2, 3, 5);
  graph_addedge(G, 0, 2, 8);
  graph_addedge(G, 0, 1, 13);
  graph_addedge(G, 1, 2, 15);

  return G;
}

int main () {
  graph_t G = nine_edges();
  printf("Graph:\n");
  graph_print(G);

  graph_t T = kruskal(G);
  printf("Spanning tree:\n");
  graph_print(T);

  graph_free(T);
  graph_free(G);

  printf("All tests passed!\n");
  return 0;
}
