// Exercise 1 ==========================================

// bfs: A, B, C, E, D, F, G
// dfs: A, B, D, E, G

// Exercise 2 ==========================================
// using bfs implement the following function
int *shortest_distances(graph_t G, vertex start)
{
    REQUIRES(G != NULL && start < graph_size(G));
    unsigned int count = 0;
    queue_t q = queue_new();
    enq(q, start);
    vertex *arr = xcalloc(graph_size(G), sizeof(vertex));
    for (vertex i = 0; i < graph_size(G); i++){
        arr[i] = -1;
    }
    arr[start] = 0;


    while (!queue_empty(q)){
        vertex cur = deq(q);

        neighbors_t nbors = graph_get_neighbors(G, cur);
        while (graph_hasmore_neighbors(nbors)){
            vertex w = graph_next_neighbor(nbors);
            if (arr[w] == -1){
                arr[w] = arr[cur] + 1;
                enq(q, w);
            }
        }
        graph_free_neighbors(nbors);
    }
    queue_free(q);

    return arr;
}

// Exercise 3 ==========================================

/* A-D */ 
/* | */
/* B */
/* | */
/* C */
// A to D dfs explores more, A to C vice versa

// Exercise 4 ==========================================

int mystery(graph_t G, bool* mark, vertex start, vertex target) {
    REQUIRES(G != NULL && mark != NULL);
    REQUIRES(start < graph_size(G));
    REQUIRES (target >= graph_size(G));

    mark[start] = true;

    queue_t Q = queue_new();
    enq(Q, start);

    int acc = 0;
    while (!queue_empty(Q)) {
        vertex u = deq(Q);
        if (u == target) {
            queue_free(Q);
            free(mark);
            return -1;
        }
        neighbors_t nbors = graph_get_neighbors(G, u);
        while (graph_hasmore_neighbors(nbors)) {
            vertex w = graph_next_neighbor(nbors);
            if (!mark[w]) {
                mark[w] = true;
                enq(Q, w);
            }
        }
        graph_free_neighbors(nbors);
        for (unsigned int i = 0; i < graph_size(G); i++) {
            if (!mark[i])
                acc++;
        }
    }
    queue_free(Q);
    return acc;
}

// mystery function returns -1 if target can e reached or
// an accumulated number of unmarked nodes as the search
// progresses to unreachable node

int tester(graph_t G) {
    bool *mark = xcalloc(sizeof(bool), graph_size(G));
    int x = mystery(G, mark, 0, graph_size(G)+1);
    free(mark);
    return x;
   }


// the cost breakdown: where v is vertices and e is edges.
// the mark xcalloc is O(v)
// the rest of the cost comes from the mystery call
//
// the outer while loop is O(v)
// first inner while loop is O(every neighbor) which in adjlist is O(e) overall
// in the adjmatrix is O(v)
//
// graph_free_neighbors is O(min(v,e)) for both
//
// the second loop, the for loop, is O(v)
// so i'm seeing it as O(v^2) in both cases
