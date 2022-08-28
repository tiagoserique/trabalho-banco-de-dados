#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "linked_list.h"


void readInput(list_t *list, int *vertex_count, FILE *arq){
    list_node_t *node = NULL;

    int time, id;
    char operation, attribute;

    fscanf(arq, "%d %d %c %c", &time, &id, &operation, &attribute);
    while ( !feof(arq) ){
        node = createNode(time, id, operation, attribute);

        appendList(list, node);

        if ( id > *vertex_count ) *vertex_count = id;

        fscanf(arq, "%d %d %c %c", &time, &id, &operation, &attribute);
    }
}


int **allocMatrix(int vertex_count){
    int pointer_array_size = sizeof(int *) * vertex_count;
    int elements_quantity = sizeof(int) * vertex_count * vertex_count;

    int **matrix = (int **) malloc(pointer_array_size + elements_quantity);

    matrix[0] = (int *) ( matrix + vertex_count );
    
    for (int i = 0; i < vertex_count; i++){
        matrix[i] = matrix[0] + ( i * vertex_count );
    }

    for (int i = 0; i < vertex_count; i++){
        for (int j = 0; j < vertex_count; j++) matrix[i][j] = 0;
    }

    return matrix;
}


