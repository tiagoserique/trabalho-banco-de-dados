#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "node.hpp"

using std::vector;
using std::set;

void readInput(vector<vector<node_t>> &list,  vector<int> &vertex_count, FILE *arq){
    int time, id;
    char operation, attribute;
    set<int> activeTransactions;
    vector<node_t> currentSchedule;
    int currentVertexCount = 0;
    
    fscanf(arq, "%d %d %c %c", &time, &id, &operation, &attribute);
    while ( !feof(arq) ){
        // if it is a commit, we remove de transaction id from the list
        if(operation == 'C'){
            activeTransactions.erase(id);
        } else {
            activeTransactions.insert(id);
            if((int)activeTransactions.size() > currentVertexCount)
                currentVertexCount = activeTransactions.size();
        }

        currentSchedule.push_back({.time = time, .id = id, .op = operation, .attr = attribute});

        // after pushing the operation, we check wether the 
        // schedule has finished or not
        if(activeTransactions.empty()){
            list.push_back(currentSchedule);
            vertex_count.push_back(currentVertexCount);
            currentSchedule.clear();
            currentVertexCount = 0;
        }

        fscanf(arq, "%d %d %c %c", &time, &id, &operation, &attribute);
    }
}
