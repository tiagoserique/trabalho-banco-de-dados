#ifndef __BLOCK_T_HPP__
#define __BLOCK_T_HPP__

#include <vector>
#include <set>
#include "node.hpp"

using std::vector;
using std::set;

struct block_t {
    int id;
    vector<node_t> transac; // list of transactions in the block
    set<char> writtenAttributes;
    set<char> readAttributes;
};


#endif