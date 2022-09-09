#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <vector>
#include "node.hpp"

// TYPEDEFS ====================================================================

typedef struct graph_t graph_t;

// STRUCTS =====================================================================

struct graph_t {
    int **matrix;
    int vertex_count;
};

// HEADERS =====================================================================

bool checkConflict(std::vector<node_t> list, int first, int second);

bool checkView(std::vector<node_t> list, int first, int second);

bool checkEqView(std::vector<node_t> list, int first, int second);

bool hasCycle(std::vector<std::vector<int>> graph);

#endif
