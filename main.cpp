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
#include "node.hpp"
#include "block.hpp"

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
        cout << t+1 << ' ';
        
        vector<vector<int>> graph(vertex_count[t]+1);
        for (int i = 0; i < (int) list[t].size(); ++i){
            for (int j = i+1; j < (int) list[t].size(); ++j){
                if(list[t][i].id != list[t][j].id){
                    if(checkConflict(list[t], i, j)){
                        graph[list[t][i].id-previousCount].push_back(list[t][j].id-previousCount);
                    }
                }
            }
        }

        for (int i = 1; i <= vertex_count[t]; ++i){
            cout << i + previousCount;
            if(i <= vertex_count[t]-1) cout << ',';
        }
        cout << ' ';
        
        if (hasCycle(graph)) cout << "NS ";
        else cout << "SS ";

        /*================ Equivalência por visão ================*/

        set<char> attributes;
        // store all unique attributes
        for(int i = 0; i < (int) list[t].size(); ++i){
            attributes.insert(list[t][i].attr);
        }

        // build graph to check wether there is a write before a read on the same attribute
        vector<vector<int>> viewGraph(vertex_count[t]+1);
        map<char, int> lastWritten;
        for (int i = 0; i < (int) list[t].size(); ++i){
            for (int j = i+1; j < (int) list[t].size(); ++j){
                if(list[t][i].id != list[t][j].id){
                    if(checkView(list[t], i, j)){
                        viewGraph[list[t][i].id-previousCount].push_back(list[t][j].id-previousCount);
                    }
                }
            }
            if(list[t][i].op == 'W'){
                lastWritten[list[t][i].attr] = list[t][i].id-previousCount;
            }
        }

        vector<block_t> blocks(vertex_count[t]);
        for(int i = 0; i < vertex_count[t]; i++){
            blocks[i].id = i+1;
            for(int j = 0; j < (int) list[t].size(); j++) if(blocks[i].id + previousCount == list[t][j].id){
                if(list[t][j].op == 'W'){
                    blocks[i].writtenAttributes.insert(list[t][j].attr);
                } else if(list[t][j].op == 'R'){
                    blocks[i].readAttributes.insert(list[t][j].attr);
                }
                blocks[i].transac.push_back(list[t][j]);
            }
        }
        // for(int i = 0; i < blocks.size(); ++i){
        //     cout << "Bloco de id: " <<blocks[i].id << " com "<< blocks[i].transac.size() << " operacoes" << endl;
        // }


        bool view;
        do {
            view = true;
            // checar ordem de escrita antes de leitura
            for(int i = 0; i < vertex_count[t]; i++){
                for(int j = i+1; j < vertex_count[t]; j++){
                    int u = blocks[i].id;
                    int v = blocks[j].id;
                    if(find(viewGraph[v].begin(), viewGraph[v].end(), u) != viewGraph[v].end()){
                        view = false;
                        // cout << "Existe a escrita do bloco " << v << " para " << u << endl;
                    }
                }
            }

            // ultima escrita é mantida?
            map<char, int> viewLastWritten;
            for(int i = 0; i < vertex_count[t]; i++){
                for(int j = 0; j < (int) blocks[i].transac.size(); j++){
                    if(blocks[i].transac[j].op == 'W'){
                        viewLastWritten[blocks[i].transac[j].attr] = blocks[i].id;
                    }
                }
            }
            for(auto i = attributes.begin(); i != attributes.end(); i++){
                // cout << lastWritten[*i] << ' ' << viewLastWritten[*i] << endl;  
                if(lastWritten[*i] != viewLastWritten[*i]){
                    view = false;
                }
            }

        } while (!view && next_permutation(blocks.begin(), blocks.end(), 
                        [](const auto & lhs, const auto & rhs) 
                            { return lhs.id < rhs.id; }));

        if(view) cout << "SV" << endl;
        else cout << "NV" << endl;
        
        previousCount += vertex_count[t];
    }
    return 0;
}
