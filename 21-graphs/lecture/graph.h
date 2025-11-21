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
//@requires nbors != NULL;x
