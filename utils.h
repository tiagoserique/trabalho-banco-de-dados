// Vinicius Tikara Venturi Date - GRR20190367
// Tiago Serique Valadares - GRR20195138

#ifndef __UTILS_H__
#define __UTILS_H__
#include <vector>
#include <set>
#include "node.h"

using std::vector;
using std::set;

// Read the input and convert it to the desired format:
// a list of schedules
void readInput(vector<vector<node_t>> &list, vector<int> &vertex_count, FILE *arq);

#endif
