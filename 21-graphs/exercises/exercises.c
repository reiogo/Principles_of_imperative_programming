// Exercise 1 ==========================================

bool is_in (adjlist* p, vertex u){
    while (p != NULL){
        if (p->vert == u) return true;
        else p = p->next;
    }
    return false;
}

bool is_vertex(graph* G, vertex u){
    return u < G->size;
}

bool is_graph(graph* G)
//@requires \length(G->adj) == G->size);
//acyclic, no duplicates, both vertices have the corresponding edge
{
    if (G == NULL) return false;
    if (G->adj == NULL) return false;
    for (vertex u = 0; u < G->size; u++){
        if (!is_acyclic(G->adj[u])) return false;
        for (adjlist* p = G->adj[u]; p != NULL; p->next){
            if (p->vert == u || !(is_vertex(G, p->vert))) return false;
            if (!is_in(G->adj[p->vert],u)) return false;
            if (is_in(p->next, p->vert)) return false;
        }
    }
    return true;
}


// Exercise 2 ==========================================

// implementation of graph interface
// in graph.c solution_graph.c

// Exercise 3 ==========================================

// write a client side function which uses graph_t G and returns 
// a new graph where, for every edge, both endpoints are even


// I understood the assignment to be removing uneven nodes, but that was wrong
/* void remove_node(graph_t G, vertex u){ */
/*     neighbors_t nbors = graph_get_neighbors(G, u); */
/*     while (graph_hasmore_neighbors(nbors)){ */
/*         vertex w = graph_next_neighbor(nbors); */
/*         remove_edge(G, w, u); */
/*     } */
/* } */

/* graph_t even_points(graph_t G) { */
/*     for (vertex u = 0; u < graph_size(G); u++){ */
/*         if (u % 2 != 0){ */
/*             remove_node(G, u); */
/*         } */
/*     } */
    
/* } */

graph_t even_points(graph_t G){
    for (vertex u = 0; u < graph_size(G)/2; u+=2){
        for (vertex w = graph_size(G)/2; w < graph_size(G); u+=2){
            if (u != w) {
                graph_addedge(G, u, w);
            }
        }
    }
    return G;
}

// solution:
graph_t even_connected(graph_t G){
    REQUIRES(G != NULL);
    int n = graph_size(G);
    graph_t G_new = graph_new(n);
    for (int i = 0; i < n; i += 2){
        if (i % 2 == 0) {
            neighbors_t nbors = graph_get_neighbors(G, i);
            while (graph_hasmore_neighbors(nbors)) {
                vertex w = graph_next_neighbor(nbors);
                if (w % 2 == 0 && !graph_hasedge(G_new, i, w)) {
                    graph_addedge(G_new, i, w);
                }
            }
            graph_free_neighbors(nbors);
        }
    }
    ENSURES(G_new != NULL);
    return G_new;
}


// Exercise 4 ==========================================

bool is_acyclic(adjlist* start) {
    if (start == NULL) return true;
    adjlist* h = start->next; // hare
    adjlist* t = start; // tortoise
    while (h != t) {
        if (h == NULL || h->next == NULL) return true;
        h = h->next->next;
        //@assert t != NULL; // hare is faster and hits NULL quicker
        t = t->next;
    }
    //@assert h == t;
    return false;
}

// for every b you have to check e nodes to know if it is acyclic
// so it should be O(v*min(v,e))
// The answer is O(v+e) my answer is off, but why? 
// it seems like i thought that acyclic check occurs on every edge when
// in fact it occurs on every node.

// Exercise 5 ==========================================

// Complexity analysis
// list: the for loop occurs O(v) times
// the graph_get_neighbors is O(1), graph_addedge is O(1), graph_free_neighbors is O(1)
// so overall it is O(v)
// matrix: the for loop is O(v) times
// graph_get_neighbors is O(v)
// graph_addedge is O(1)
// graph_free_neighbors is O(1) apparently i was wrong it should be O(min(e,v))
// overall it should be O(v^2)

int f1(graph_t G) {
    unsigned int n = graph_size(G);
    int total = 0;
    for (vertex u = 0; u < n; u++) {
        neighbors_t nbors = graph_get_neighbors(G, u);
        if (nbors != NULL) {
            total++;
        }
        else {
            graph_addedge(G, u, 0);
        }
        graph_free_neighbors(nbors);
    }
    return total;
}


