#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "utils.h"
#include "graph.h"
#include "node.hpp"

using std::vector;
using std::cout;
using std::endl;

int main(){
    vector<node_t> list;

    int vertex_count = 0;

    readInput(list, vertex_count, stdin);

    for (auto node: list) cout << node.id << ' ';
    cout << endl;

    vector<vector<int>> graph(vertex_count+1);

    for (int i = 0; i < list.size(); ++i){
        for (int j = i+1; j < list.size(); ++j){
            if(list[i].id != list[j].id){
                if(checkConflict(list, i, j)){
                    graph[list[i].id].push_back(list[j].id);
                }
            }
        }
    }

    for (int i = 1; i <= vertex_count; ++i){
        cout << i << ": ";
        for(auto j: graph[i]) cout << j << ' ';
        cout << endl;
    }
    
    if (hasCycle(graph)) cout << "ciclo :O" << endl;

    return 0;
}
