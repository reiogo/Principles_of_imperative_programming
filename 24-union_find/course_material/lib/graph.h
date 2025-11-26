/*
 * Weighted graphs
 *
 * 15-122 Principles of Imperative Computation
 */

#ifndef DGRAPH_H
#define DGRAPH_H

#include <stdbool.h>

typedef unsigned int vertex;
typedef struct graph_header *graph_t;

graph_t graph_new(unsigned int numvert); // New graph with numvert vertices
//@ensures \result != NULL;

void graph_free(graph_t G);
//@requires G != NULL;

unsigned int graph_size(graph_t G);  // Number of vertices in the graph
//@requires G != NULL;

// returns 0 if there is edge (v,w) is not in G
unsigned int graph_hasedge(graph_t G, vertex v, vertex w);
//@requires G != NULL;
//@requires v < graph_size(G) && w < graph_size(G);

void graph_addedge(graph_t G, vertex v, vertex w, unsigned int weight);
//@requires G != NULL;
//@requires v < graph_size(G) && w < graph_size(G);
//@requires v != w && graph_hasedge(G, v, w) != 0;
//@requires weight != 0;

void graph_print(graph_t G);
//@requires G != NULL;


typedef struct neighbor_header *neighbors_t;

neighbors_t graph_get_neighbors(graph_t G, vertex v);
//@requires G != NULL && v < graph_size(G);
//@ensures \result != NULL;

bool graph_hasmore_neighbors(neighbors_t nbors);
//@requires nbors  != NULL;

vertex graph_next_neighbor(neighbors_t nbors);
//@requires nbors  != NULL;
//@requires graph_hasmore_neighbors(nbors);

void graph_free_neighbors(neighbors_t nbors);
//@requires nbors != NULL;

#endif
