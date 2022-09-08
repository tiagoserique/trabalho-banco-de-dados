#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "graph.h"

using std::vector;


bool checkConflict(vector<node_t> list, int first, int second){
    if(list[first].op == 'R'){
        if(list[first].attr == list[second].attr && list[second].op == 'W')
            return true;
    } 
    else if(list[first].op == 'W'){
        if(list[first].attr == list[second].attr && (list[second].op == 'W' || list[second].op == 'R'))
            return true;
    }
    
    return false;
}

bool checkView(vector<node_t> list, int first, int second){
    if(list[first].op == 'R'){
        if(list[first].attr == list[second].attr && list[second].op == 'W')
            return true;
    } 
    
    return false;
}

static void dfs(vector<vector<int>> &graph, vector<int> &visited, int v, bool &cycle){
    visited[v] = 1;
    
    for (auto i: graph[v]){
        if ( visited[i] == 0 )
            dfs(graph, visited, i, cycle);
        else if (visited[i] == 1)
            cycle = true;
    }

    visited[v] = 2;
}

bool hasCycle(vector<vector<int>> graph){
    vector<int> visited(graph.size(), 0); // inicializa em 0 == nao explorado
    bool cycle;
    
    for(int i = 1; i < graph.size(); ++i){
        if(visited[i] == 0) dfs(graph, visited, i, cycle); 
    }
    
    return cycle;
}