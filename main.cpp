#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "graph.h"
#include "linked_list.h"

#define true 1

int main(){
    list_t *list = createList();

    int vertex_count = 0;

    readInput(list, &vertex_count, stdin);

    printList(list);

    destroyList(list);
    
    return 0;
}
