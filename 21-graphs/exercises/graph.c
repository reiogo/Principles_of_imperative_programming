#include <bool.h>

typedef struct graph_header graph;
struct graph_header {
    unsigned int size;
    bool** matrix;
};

bool is_vertex(graph* G, vertex u){
    return u < size;
}

bool is_graph(graph* G){
    return graph != NULL
        && graph->matrix != NULL;
}

graph* graph_new(unsigned int numvert){
    graph* G = xmalloc(sizeof(graph));
    G->size = numvert;
    G->matrix = xmalloc(sizeof(bool*)*numvert);
    for (vertex i = 0; i < numvert; i++){
        G->matrix[i] = xcalloc(numvert, sizeof(bool));
    }
    ENSURES(is_graph(G));
    return G;
}

void graph_free(graph* G){
    REQUIRES(is_graph(G));
    for (vertex i = 0; i < G->size; i++){
        free(G->matrix[i]);
    }
    free(G->matrix);
    free(G);
}

unsigned int graph_size(graph* G){
    REQUIRES(is_graph(G));
    return G->size;
}

bool graph_hasedge(graph* G, vertex u, vertex w){
    REQUIRES(is_graph(G));
    REQUIRES(u < graph_size(G) && w < graph_size(G));
    return G->matrix[u][w];
}

void graph_addedge(graph* G, vertex u, vertex w){
    REQUIRES(is_graph(G));
    REQUIRES(u < graph_size(G) && w < graph_size(G));
    REQUIRES(u != w && !graph_hasedge(G, u, w));
    G->matrix[u][w] = true;
    G->matrix[w][u] = true;
}

typedef struct neighbor_header neighbors;
struct neighbor_header {
    unsigned int size;
    bool* row;
    vertex cur;
};

neighbors* graph_get_neighbors(graph* G, vertex u){
    REQUIRES(is_graph(G) && u < graph_size(G));

    neighbors* res = xmalloc(sizeof(neighbors));
    res->size = G->size;
    res->row = G->matrix[u];
    res->cur = 0;

    ENSURES(res != NULL);
    return res;
}


bool graph_hasmore_neighbors(neighbors* nbors){
    REQUIRES(nbors != NULL);
    for (unsigned int i = nbors->cur; i < nbors->size; i++){
        if (nbors->row[i]) return true;
    }
    return false;
}

vertex graph_next_neighbor(neighbor* nbors){
    REQUIRES(nbors != NULL);
    REQUIRES(graph_hasmore_neighbors(nbors));
    for (unsigned int i = nbors->cur; i < nbors->size; i++){
        if (nbors->row[i]){
            nbors->cur += 1;
            return i;
        }
    }
    assert(false);
    return 0;
}

void graph_free_neighbors(neighbors* nbors){
    REQUIRES(nbors != NULL);
    free(nbors);
}





