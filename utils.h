#ifndef __UTILS_H__
#define __UTILS_H__
#include <vector>
#include <set>
#include "node.hpp"

using std::vector;
using std::set;

void readInput(vector<vector<node_t>> &list, vector<int> &vertex_count, FILE *arq);

bool haveIntersection(set<char> a, set<char> b);

#endif
