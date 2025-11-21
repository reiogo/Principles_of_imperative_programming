/* void graph_print(graph_t G){ */
/*     REQUIRES(is_graph(G)); */
/*     for (int i = 0; i < G->size; i++){ */
/*         for (int j = 0; j < G->size; j++){ */
/*             printf("%d\n", G->matrix[i][j]); */
/*         } */
/*     } */
/* } */

void graph_print(graph_t G){
    REQUIRE(is_graph(G));
    for (vertex u = 0; u < graph_size(G); u++){
        neighbors* nbors = graph_get_neighbors(G, u);
        printf("for %u: ", u);
        while (graph_hasmore_neighbors(nbors)){
            vertex w = graph_next_neighbor(nbors);
            printf("%u ", w);
        }
    }
    graph_free_neighbors(nbors);
    printf("\n");
}
