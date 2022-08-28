#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__


// TYPEDEFS ====================================================================

typedef struct list_node_t list_node_t;
typedef struct list_t list_t;

// STRUCTS =====================================================================

struct list_node_t {
	int time;           // start time
    int id;             // id of the transaction
    char op;            // operation of the transaction
    char attr;          // attribute of the transaction
	list_node_t *next;
	list_node_t *prev;
};


struct list_t {
	list_node_t *start;
	list_node_t *end;
	int size;
};

// HEADERS =====================================================================


list_node_t *createNode(int time, int id, char op, char attr);


list_t *createList();


int appendList(list_t *list, list_node_t *node);


int removeList(list_t *list, list_node_t *node);


void printList(list_t *list);


void destroyList(list_t *list);

#endif