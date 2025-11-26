/* Union-find testing via Kruskal's algorithm
 * 15-122 Principles of Imperative Computation, Fall 2010
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/graph.h"
#include "unionfind.h"
#include "kruskal.h"

struct edge_info {
  unsigned int weight;
  vertex v1;
  vertex v2;
};
typedef struct edge_info edge;


// returns an array containing the edges of G
edge** get_edges(graph_t G) {
  unsigned int n = graph_size(G);
  // unused positions are set to NULL
  edge** E = xcalloc(sizeof(edge*), n*(n-1)/2);

  size_t idx = 0;  // next position to fill in E
  for (vertex u = 0; u < n; u++)
    for (vertex j = u+1; j < n; j++) {  // avoid duplicates
      unsigned int weight = graph_hasedge(G, u, j);

      if (weight != 0) {
        edge* e = xmalloc(sizeof(edge));
        e->v1 = u;
        e->v2 = j;
        e->weight = weight;
        E[idx] = e;
        idx++;
      }
    }
  return E;
}

// NULL is bigger than any edge
bool lt_edge(edge *e1, edge *e2) {
  if (e1 != NULL && e2 != NULL)
    return (e1->weight < e2->weight);
  if (e1 != NULL)
    return true;
  return false;
}

void merge_edge(edge **E, size_t lo, size_t mid, size_t hi) {
  edge **TMP = xcalloc(sizeof(edge*), hi-lo);
  size_t i = lo;
  size_t j = mid;
  size_t k = 0;

  while (i < mid && j < hi) {
    if (lt_edge(E[i], E[j])) {
      TMP[k] = E[i];
      i++;
    } else {
      TMP[k] = E[j];
      j++;
    }
    k++;
  }

  while (i < mid) { TMP[k] = E[i]; i++; k++; }
  while (j < hi)  { TMP[k] = E[j]; j++; k++; }

  // Copy sorted array back into A
  for (k = 0; k < hi-lo; k++)
    E[lo+k] = TMP[k];

  free(TMP);
}

void msort_edge(edge **E, size_t lo, size_t hi) {
  REQUIRES(lo <= hi);

  if (hi - lo <= 1) return;

  size_t mid = lo + (hi - lo)/2;
  msort_edge(E, lo, mid);
  msort_edge(E, mid, hi);
  merge_edge(E, lo, mid, hi);
}

// sort E of size n in increasing weight order
void sort_edges(edge **E, size_t n) {
  msort_edge(E, 0, n);
}

// return a spanning tree for G
graph_t kruskal(graph_t G) {
  unsigned int n = graph_size(G);

  edge **E = get_edges(G);
  size_t num_edges = n*(n-1)/2;
  sort_edges(E, num_edges);

  graph_t T = graph_new(n);        // spanning tree
  size_t inT = 0;                  // number of edged in T

  ufs_t eqs = ufs_new(n);          // Union-find data structure

  for (size_t i = 0; i < num_edges; i++) {
    edge *e = E[i];
    if (e == NULL) break;          // no more edges in E

    int cr1 = ufs_find(eqs, e->v1);
    int cr2 = ufs_find(eqs, e->v2);
    if (cr1 != cr2) {
      graph_addedge(T, e->v1, e->v2, e->weight);
      ufs_union(eqs, cr1, cr2);
      inT++;
      if (inT > n-1) break;         // T is a tree
    }
  }

  ufs_free(eqs);
  for (size_t i = 0; i < num_edges; i++)
    free(E[i]);
  free(E);
  return T;
}
