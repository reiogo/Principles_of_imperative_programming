typedef unsigned int vertex;
typedef struct graph_header *graph_t;

graph_t graph_new(unsigned int numvert);
//@ensures \result != NULL;

void graph_free(graph_t G);
//@requires G != NULL;

unsigned int graph_size(graph_t G);
//@requires G != NULL;

bool graph_hasedge(graph_t G, vertex u, vertex w);
//@requires G != NULL;
//@requires u < graph_size(G) && w < graph_size(G);

void graph_addedge(graph_t G, vertex u, vertex w);
//@requires G != NULL;
//@requires u < graph_size(G) && w < graph_size(G);
//@requires u != w && !graph_hasedge(G, u, w);

typedef struct neighbor_header *neighbors_t;

neighbors_t graph_get_neighbors(graph_t G, vertex u);
//@requires G != NULL && u < graph_size(G);
//@ensures \result != NULL;

bool graph_hasmore_neighbors(neighbors_t nbors);
//@requires nbors != NULL;

vertex graph_next_neighbor(neighbors_t nbors);
//@requires nbors != NULL;
//@requires graph_hasmore_neighbors(nbors);

void graph_free_neighbors(neighbors_t nbors);
//@requires nbors != NULL;



bool dfs_helper(graph_t G, bool *mark, vertex start, vertex target) {
    REQUIRES(G != NULL && mark != NULL);
    REQUIRES(start < graph_size(G) && target < graph_size(G));
    REQUIRES(!mark[start]);

    // start is seen
    mark[start] = true;

    if (target == start) return true;

    neighbors_t nbors = graph_get_neighbors(G, start);
    while (graph_hasmore_neighbors(nbors)) {
        vertex u = graph_next_neighbor(nbors);
        if (!mark[u] && dfs_helper(G, mark, u, target)) {
            graph_free_neighbors(nbors);
            return true;
        }
    }
    graph_free_neighbors(nbors);
    return false;
}

bool dfs(graph_t G, vertex start, vertex target) {
    REQUIRES(G != NULL);
    REQUIRES(start < graph_size(G) && target < graph_size(G));
    bool *mark = xcalloc(graph_size(G), sizeof(bool));
    bool connected = dfs_helper(G, mark, start, target);
    free(mark);
    return connected;
}


bool dfs_explicit_stack(graph_t G, vertex start, vertex target) {
    REQUIRES(G != NULL);
    REQUIRES(start < graph_size(G) && target < graph_size(G));

    if (start == target) return true;

    bool *mark = xcalloc(graph_size(G), sizeof(bool));
    mark[start] = true;

    stack_t S = stack_new();
    push(S, start);

    while (!stack_empty(S)) {
        // every marked vertex is connected to start
        // every vertex in the stack is marked
        // every path from start to target passes through a vertex in the frontier
        vertex u = pop(S);
        if (u == target) {
            stack_free(S);
            free(mark);
            return true;
        }
        neighbors_t nbors = graph_get_neighbors(G, u);
        while (graph_hasmore_neighbors(nbors)){
            vertex w = graph_next_neighbor(nbors);
            if (!mark[w]){
                mark[w] = true;
                push(S, w);
            }
        }
        graph_free_neighbors(nbors);
    }
    stack_free(S);
    free(mark);
    return false;
}
