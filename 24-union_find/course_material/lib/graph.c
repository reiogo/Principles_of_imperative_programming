/*
 * Weighted graphs
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include "xalloc.h"
#include "contracts.h"
#include "graph.h"

/**************** Weighted graphs ****************/

typedef struct adjlist_node adjlist;
struct adjlist_node {
  vertex vert;
  unsigned int weight;
  adjlist *next;
};

typedef struct graph_header graph;
struct graph_header {
  unsigned int size;
  adjlist **adj;      // adjlist*[] adj in C0
};

/* Data structure invariants */

bool is_vertex(graph *G, vertex v) {
  REQUIRES(G != NULL);
  return v < G->size;
}

bool is_acyclic(adjlist *start) {
  if (start == NULL) return true;
  adjlist *h = start->next;         // hare
  adjlist *t = start;               // tortoise
  while (h != t) {
    if (h == NULL || h->next == NULL) return true;
    h = h->next->next;
    //@assert t != NULL; // hare is faster and hits NULL quicker
    t = t->next;
  }
  //@assert h == t;
  return false;
}

// Check for the presence of a vertex in an adjacency list
bool is_in_adjlist(adjlist *L, vertex v) {
  REQUIRES(is_acyclic(L));

  while (L != NULL) {
    if (L->vert == v) return true;
    L = L->next;
  }
  return false;
}

bool is_adjlist(graph *G, vertex v, adjlist *L) {
  REQUIRES(G != NULL);
  //@requires(G->size == \length(G->adj));
  if (!is_vertex(G, v)) return false;

  if (!is_acyclic(L)) return false;

  while (L != NULL) {

    // Neighbors are legal vertices
    if (!is_vertex(G, L->vert)) return false;

    // No self-edges
    if (v == L->vert) return false;

    // Every outgoing edge has a corresponding edge coming back to it
    if (!is_in_adjlist(G->adj[L->vert], v)) return false;

    // Edges aren't duplicated
    if (is_in_adjlist(L->next, L->vert)) return false;

    // Weights are strictly positive
    if (L->weight == 0) return false;
    L = L->next;
  }
  return true;
}

bool is_graph(graph *G) {
  if (G == NULL) return false;
  //@assert(G->size == \length(G->adj));
  for (unsigned int i = 0; i < G->size; i++) {
    if (!is_adjlist(G, i, G->adj[i])) return false;
  }
  return true;
}

/* Interface functions */

graph *graph_new(unsigned int size) {
  graph *G = xmalloc(sizeof(graph));
  G->size = size;
  G->adj = xcalloc(size, sizeof(adjlist*));
  ENSURES(is_graph(G));
  return G;
}

void graph_free(graph *G) {
  REQUIRES(is_graph(G));
  for (vertex v = 0; v < G->size; v++) {
    adjlist *L = G->adj[v];
    while (L != NULL) {
      adjlist *tmp = L->next;
      free(L);
      L = tmp;
    }
  }
  free(G->adj);
  free(G);
}

unsigned int graph_size(graph *G) {
  REQUIRES(is_graph(G));
  return G->size;
}

unsigned int graph_hasedge(graph *G, vertex v, vertex w) {
  REQUIRES(is_graph(G) && is_vertex(G, v) && is_vertex(G, w));

  for (adjlist *L = G->adj[v]; L != NULL; L = L->next) {
    if (L->vert == w) {
      return L->weight;
    }
  }
  return 0;
}

void graph_addedge(graph *G, vertex v, vertex w, unsigned int weight) {
  REQUIRES(is_graph(G) && is_vertex(G, v) && is_vertex(G, w));
  REQUIRES(v != w && graph_hasedge(G, v, w) == 0);
  REQUIRES(weight != 0);

  adjlist *L;

  L = xmalloc(sizeof(adjlist));  // add w as a neighbor of v
  L->vert = w;
  L->weight = weight;
  L->next = G->adj[v];
  G->adj[v] = L;

  L = xmalloc(sizeof(adjlist));  // add v as a neighbor of w
  L->vert = v;
  L->weight = weight;
  L->next = G->adj[w];
  G->adj[w] = L;

  ENSURES(is_graph(G));
  ENSURES(graph_hasedge(G, w, v));
}


void graph_print(graph_t G) {
  for (vertex v = 0; v < G->size; v++) {
    printf("Vertices connected to %u: ", v);
    for (adjlist *L = G->adj[v]; L != NULL; L = L->next) {
      vertex w = L->vert;       // w is a neighbor of v
      printf(" %u,", w);
    }
    printf("\n");
  }
}

/**************** Neighbors ****************/

struct neighbor_header {
  adjlist *next_neighbor;
};
typedef struct neighbor_header neighbors;

/* Representation invariants */

bool is_neighbors(neighbors *nbors) {
  if (nbors == NULL) return false;

  // Check for acyclicity
  if (!is_acyclic(nbors->next_neighbor)) return false;

  // Check for duplicates

  for (adjlist *L = nbors->next_neighbor; L != NULL; L = L->next) {
    if (is_in_adjlist(L->next, L->vert)) return false;
  }

  return true;
}

/* Interface functions */

neighbors *graph_get_neighbors(graph *G, vertex v) {
  REQUIRES(is_graph(G) && is_vertex(G, v));

  neighbors *nbors = xmalloc(sizeof(neighbors));
  nbors->next_neighbor = G->adj[v];
  ENSURES(is_neighbors(nbors));
  return nbors;
}

bool graph_hasmore_neighbors(neighbors *nbors) {
  REQUIRES(is_neighbors(nbors));
  return nbors->next_neighbor != NULL;
}

vertex graph_next_neighbor(neighbors *nbors) {
  REQUIRES(is_neighbors(nbors));
  REQUIRES(graph_hasmore_neighbors(nbors));

  vertex v = nbors->next_neighbor->vert;
  // Must not free the adjacency list node since it is owned by the graph
  nbors->next_neighbor = nbors->next_neighbor->next;

  return v;
}

void graph_free_neighbors(neighbors *nbors) {
  REQUIRES(is_neighbors(nbors));
  // Must not free the adjacency list since it is owned by the graph
  free(nbors);
}
