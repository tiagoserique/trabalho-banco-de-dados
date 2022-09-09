// Vinicius Tikara Venturi Date - GRR20190367
// Tiago Serique Valadares - GRR20195138

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

#include "utils.h"
#include "graph.h"
#include "node.h"
#include "block.h"

using std::vector;
using std::set;
using std::map;
using std::pair;
using std::cout;
using std::endl;

int main(){
    vector<int> vertex_count;
    int previousCount = 0;
    vector<vector<node_t>> list;

    readInput(list, vertex_count, stdin);

    for(int t = 0; t < (int) list.size(); ++t){
        // part of the output print
        cout << t+1 << ' ';
        for (int i = 1; i <= vertex_count[t]; ++i){
            cout << i + previousCount;
            if(i <= vertex_count[t]-1) cout << ',';
        }
        cout << ' ';

        /*================ Serialidade por Conflito ================*/

        vector<vector<int>> graph = buildGraph(list[t], vertex_count[t]+1, previousCount, checkConflict);

        if (hasCycle(graph)) cout << "NS ";
        else cout << "SS ";

        /*================= Equivalência por visão =================*/

        set<char> attributes;
        // store all unique attributes
        for(int i = 0; i < (int) list[t].size(); ++i){
            attributes.insert(list[t][i].attr);
        }

        // build graph to check wether there is a write before a read on the same attribute
        vector<vector<int>> viewGraph = buildGraph(list[t], vertex_count[t]+1, previousCount, checkView);

        // stores which transaction has wrote last in the attribute
        map<char, int> lastWritten;
        for (int i = 0; i < (int) list[t].size(); ++i){
            if(list[t][i].op == 'W'){
                lastWritten[list[t][i].attr] = list[t][i].id-previousCount;
            }
        }

        // build sequential transaction blocks for permutation later
        vector<block_t> blocks(vertex_count[t]);
        for(int i = 0; i < vertex_count[t]; i++){
            blocks[i].id = i+1;
            for(int j = 0; j < (int) list[t].size(); j++) if(blocks[i].id + previousCount == list[t][j].id){
                blocks[i].transac.push_back(list[t][j]);
            }
        }

        // check the permutation of the blocks to see if there is a conflict between them
        bool view;
        do {
            view = true;
            
            view = checkReadAndWriteOrder(view, vertex_count, t, blocks, viewGraph);

            view = checkLastWritten(view, vertex_count, t, blocks, attributes, lastWritten);

        } while (!view && next_permutation(blocks.begin(), blocks.end(), 
                        [](const auto & lhs, const auto & rhs) 
                            { return lhs.id < rhs.id; }));

        if(view) cout << "SV" << endl;
        else cout << "NV" << endl;
        
        previousCount += vertex_count[t];
    }
    return 0;
}
