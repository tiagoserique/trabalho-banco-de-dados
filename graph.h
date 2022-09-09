// Vinicius Tikara Venturi Date - GRR20190367
// Tiago Serique Valadares - GRR20195138

#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <vector>
#include "node.h"
#include "block.h"

using std::vector;
using std::map;

// TYPEDEFS ====================================================================

typedef struct graph_t graph_t;

// STRUCTS =====================================================================

struct graph_t {
    int **matrix;
    int vertex_count;
};

// HEADERS =====================================================================

// build a graph of dependencies using the current schedule and what kinda of dependecy you want to check via the check function
vector<vector<int>> buildGraph(vector<node_t> list, int nrVertices, int previousCount, bool (*check)(vector<node_t>, int, int));

// conflict serializable check
bool checkConflict(vector<node_t> list, int first, int second);

// view serializable check
bool checkView(vector<node_t> list, int first, int second);

// check wether or not the graph has a cycle using dfs and its back-edges
bool hasCycle(vector<vector<int>> graph);

// check if the transactions that have wrote the attributes of the current view are the same that wrote them in the original schedule 
bool checkLastWritten(bool view, vector<int> vertex_count, int t, vector<block_t> blocks, set<char> attributes, map<char, int> lastWritten);

// check if the order of writes and reads of the view graph has conflicts with the order of trasactions blocks  
bool checkReadAndWriteOrder(bool view, vector<int> vertex_count, int t, vector<block_t> blocks, vector<vector<int>> viewGraph);

#endif
