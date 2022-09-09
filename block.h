// Vinicius Tikara Venturi Date - GRR20190367
// Tiago Serique Valadares - GRR20195138

#ifndef __BLOCK_T_HPP__
#define __BLOCK_T_HPP__

#include <vector>
#include <set>
#include "node.h"

using std::vector;
using std::set;

struct block_t {
    int id;
    vector<node_t> transac; // list of transactions in the block
};


#endif