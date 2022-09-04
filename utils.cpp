#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "node.hpp"


using std::vector;


void readInput(vector<node_t> &list,  int &vertex_count, FILE *arq){
    int time, id;
    char operation, attribute;

    fscanf(arq, "%d %d %c %c", &time, &id, &operation, &attribute);
    while ( !feof(arq) ){
        list.push_back({.time = time, .id = id, .op = operation, .attr = attribute});

        if ( id > vertex_count ) vertex_count = id;

        fscanf(arq, "%d %d %c %c", &time, &id, &operation, &attribute);
    }
}

