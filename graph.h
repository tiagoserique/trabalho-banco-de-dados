#ifndef __GRAPH_H__
#define __GRAPH_H__


// TYPEDEFS ====================================================================

typedef struct graph_t graph_t;

// STRUCTS =====================================================================

struct graph_t {
    int **matrix;
    int vertex_count;
};

// HEADERS =====================================================================

// Creates a new graph with the given number of vertices.
// Returns a pointer to the new graph.
graph_t *createGraph(int vertex_count);

// Adds an edge to the graph.
// Returns 0 if the edge was added successfully, 1 otherwise.
int addEdge(graph_t *graph, int vertex_1, int vertex_2);

// Prints the graph.
void printGraph(graph_t *graph);

// Frees the memory used by the graph.
void destroyGraph(graph_t *graph);


#endif
