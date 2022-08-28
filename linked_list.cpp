#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


list_node_t *createNode(int time, int id, char op, char attr){

    list_node_t *aux = (list_node_t *) malloc(sizeof(list_node_t)); 

    aux->id   = id; 
    aux->time = time; 
    aux->op   = op; 
    aux->attr = attr;
    
    return aux;
}


list_t *createList(){
    list_t *aux = (list_t *) malloc(sizeof(list_t)); 

    aux->start  = NULL;
    aux->end    = NULL;
    aux->size   = 0;

    return aux;
}


int appendList(list_t *list, list_node_t *node){
    // check if list is empty or node is null
    if ( !list || !node ) return -1;

    // check if the node is already in the list
    if ( node->prev || node->next ) return -1;

    list->size++;

    // if list is empty, set start and end to the node
    if ( !list->start && !list->end ){
        list->start = list->end = node;

        return 0;
    }

    list->end->next = node;
    list->end = node;

    return 0;
}


int removeList(list_t *list, list_node_t *node){
    // check if list is empty or node is null
    if ( !list || !node ) return -1;

    // check if node is not in the list
    if ( !node->next && !node->prev && list->start != node ) return -1;

    // check if the node is the start
    if ( node->prev ) node->prev->next = node->next;
    else {
        list->start = node->next;
        node->next->prev = NULL;
    }

    // check if the node is the last one
    if ( node->next ) node->next->prev = node->prev;
    else {
        list->end = node->prev;
        node->prev->next = NULL;
    }

    list->size--;

    return 0;
}


void printList(list_t *list){
    list_node_t *aux = list->start;

    while ( aux != NULL ){
        printf("%d %d %c %c\n", aux->time, aux->id, aux->op, aux->attr);
        aux = aux->next;
    }
}


void destroyList(list_t *list){
    list_node_t *aux = list->start;
    
    while ( aux != NULL ){
        list->start = aux->next;
        
        free(aux);
        
        aux = list->start;
    }

    free(list);
}

