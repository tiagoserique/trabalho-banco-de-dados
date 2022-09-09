// Vinicius Tikara Venturi Date - GRR20190367
// Tiago Serique Valadares - GRR20195138

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

#include "utils.h"
#include "graph.h"
#include "block.h"


using std::vector;
using std::map;


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
    if(list[first].op == 'W'){
        if(list[first].attr == list[second].attr && list[second].op == 'R')
            return true;
    } 
    return false;
}

vector<vector<int>> buildGraph(vector<node_t> list, int nrVertices, int previousCount, bool (*check)(vector<node_t>, int, int)){
    vector<vector<int>> graph(nrVertices);
    for (int i = 0; i < (int) list.size(); ++i){
        for (int j = i+1; j < (int) list.size(); ++j){
            if(list[i].id != list[j].id){
                // add an edge whenever the check function returns true
                if(check(list, i, j)){
                    graph[list[i].id-previousCount].push_back(list[j].id-previousCount);
                }
            }
        }
    }
    return graph;
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
    
    for(int i = 1; i < (int) graph.size(); ++i){
        if(visited[i] == 0) dfs(graph, visited, i, cycle); 
    }
    
    return cycle;
}


bool checkLastWritten(bool view, vector<int> vertex_count, int t, vector<block_t> blocks, set<char> attributes, map<char, int> lastWritten){
    map<char, int> viewLastWritten;

    for(int i = 0; i < vertex_count[t]; i++){
        for(int j = 0; j < (int) blocks[i].transac.size(); j++){
            if(blocks[i].transac[j].op == 'W'){
                viewLastWritten[blocks[i].transac[j].attr] = blocks[i].id;
            }
        }
    }
    for(auto i = attributes.begin(); i != attributes.end(); i++){
        if(lastWritten[*i] != viewLastWritten[*i]){
            return false;
        }
    }
    
    return view;
}


bool checkReadAndWriteOrder(bool view, vector<int> vertex_count, int t, vector<block_t> blocks, vector<vector<int>> viewGraph){
    // checar ordem de escrita e de leitura
    for(int i = 0; i < vertex_count[t]; i++){
        for(int j = i+1; j < vertex_count[t]; j++){
            int u = blocks[i].id;
            int v = blocks[j].id;
            // checa se existe aresta voltando, i.e, vindo de um bloco de baixo para um bloco de cima
            if(find(viewGraph[v].begin(), viewGraph[v].end(), u) != viewGraph[v].end()){
                return false;
            }
        }
    }

    return view;
}