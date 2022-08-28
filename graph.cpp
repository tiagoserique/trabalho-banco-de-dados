#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "graph.h"
#include "linked_list.h"


graph_t *createGraph(int vertex_count){
    graph_t *graph = (graph_t *) malloc(sizeof(graph_t));
    
    graph->vertex_count = vertex_count;

    // graph->adj_list = (list_t **) malloc(sizeof(list_t *) * vertex_count);
    
    // for ( int i = 0; i < vertex_count; i++ ){
    //     graph->adj_list[i] = createList();
    // }

    graph->matrix = allocMatrix(vertex_count);

    return graph;
}



int addEdge(graph_t *graph, int vertex_1, int vertex_2){
    // check if graph is null
    if ( !graph ) return -1;
    
    // check if vertex_1 and vertex_2 are valid
    if ( vertex_1 - 1 < 0 || vertex_1 - 1 >= graph->vertex_count ||
         vertex_2 - 1 < 0 || vertex_2 - 1 >= graph->vertex_count ){
        return -1;
    }
    
    // check if there is an edge between vertex_1 and vertex_2
    if ( graph->matrix[vertex_1 - 1][vertex_2 - 1] ) return -1;
    
    // add edge between vertex_1 and vertex_2
    graph->matrix[vertex_1 - 1][vertex_2 - 1] = 1;
    
    return 0;
}


void printGraph(graph_t *graph){
    printf("\n");

    for ( int i = 0; i < graph->vertex_count; i++ ){
        printf("%d: ", i);
    
        for ( int j = 0; j < graph->vertex_count; j++ ){
            printf("%d ", graph->matrix[i][j]);
        }
    
        printf("\n");
    }

    printf("\n");
}


void destroyGraph(graph_t *graph){
    // for ( int i = 0; i < graph->vertex_count; i++ ){
    //     destroyList(graph->adj_list[i]);
    // }
    
    // free(graph->adj_list);

    free(graph->matrix);
    free(graph);
}


