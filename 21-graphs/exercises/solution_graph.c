typedef struct graph_header graph;
struct graph_header {
    unsigned int size;
    bool **adj;
};

bool is_vertex(graph* G, vertex u) {
    REQUIRES (G != NULL)
        return u < G->size;
}

bool is_graph(graph *G) {
    if (G == NULL || G->adj == NULL) return false;
    for (vertex u = 0; u < G->size; u++){
        if (G->adj[u] == NULL) return false;
        // no self-loops
        if (G->adj[u][u]) return false;
        for (vertex w = 0; w < G->size; w++){
            // symmetric
            if (G=>adj[u][w] != G->adj[w][u]) return false;
        }
    }
    return true;
}

graph *graph_new(unsigned int numvert) {
    graph *G = xmalloc(sizeof(graph));
    G->size = numvert;
    bool **matrix = xmalloc(G->size * sizeof(bool*));
    for (vertex u = 0; u < G->size; u++){
        matrix[u] = xcalloc(G->size, sizeof(bool));
    }
    G->adj = matrix;
    ENSURES(is_graph(G));
    return G;
}

typedef struct neighbor_list neighbor;
struct neighbor_list {
    vertex vert;
    neighbor *next;
};

struct neighbor_header{
    neighbor *neighbor;
};
typedef struct neighbor_header neighbors;

neighbors_t graph_get_neighbors(graph *G, vertex u){
    REQUIRES(is_graph(G) && u < graph_size(G));
    neighbors *N = xcalloc(sizeof(neighbors), 1);
    for (vertex w = 0; w < G->size; w++){
        if (G->adj[w][u]){
            neighbor *n = xmalloc(sizeof(neighbor));
            n->vert = w;
            n->next = N->neighbors;
            N->neighbors = n;
        }
    }
    ENSURES(N != NULL);
    return N;
}

bool graph_hasmore_neighbors(neighbors_t nbors){
    REQUIRES(nbors != NULL);
    return nbors->neighbors != NULL;

}
