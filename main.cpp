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

        // cout << "nr of transactions: " << vertex_count[t] << endl;
        // cout << "prev count: " << previousCount << endl;
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

        vector<vector<int>> attributesGraph(vertex_count[t]+1);
        for (int i = 0; i < (int) list[t].size(); ++i){
            for (int j = i+1; j < (int) list[t].size(); ++j){
                if(list[t][i].id != list[t][j].id){
                    if(checkView(list[t], i, j)){
                        attributesGraph[list[t][i].id-previousCount].push_back(list[t][j].id-previousCount);
                        // cout << "Tem aresta de " << list[t][i].id << " para " << list[t][j].id << endl;
                    }
                }
            }
        }

        // armazena o id da ultima escrita do atributo
        map<char, int> lastWrittenId;
        map<char, int> lastWrittenTime;
        for(int i = 1; i <= vertex_count[t]; i++){
            for(int j = 0; j < (int) list[t].size(); j++){
                if(list[t][j].op == 'W'){
                    if(lastWrittenTime[list[t][j].attr] < list[t][j].time){
                        lastWrittenId[list[t][j].attr]   = list[t][j].id;
                        lastWrittenTime[list[t][j].attr] = list[t][j].time;
                    }
                }    
            }
        }

        vector<block_t> blocks(vertex_count[t]+1);
        int time = 0;
        for(int i = 1; i <= vertex_count[t]; i++){
            // int relativeIndex = i - previousCount + 1;
            blocks[i].id = i;
            
            for(int j = 0; j < (int) list[t].size(); j++) if(i+previousCount == list[t][j].id){
                if(list[t][j].op == 'W'){
                    blocks[i].writtenAttributes.insert(list[t][j].attr);
                } else if(list[t][j].op == 'R'){
                    blocks[i].readAttributes.insert(list[t][j].attr);
                }

                node_t newTransaction = list[t][j];
                newTransaction.time = time;
                blocks[i].transac.push_back(newTransaction);
                time++;
            }
        }

        
        bool view;
        bool view2;
        int b = 0;
        do {
            view = true;
            view2 = true;

            // checar se últimas escritas dos atributos são as últimas nessa visão
            map<char, int> currentLastWrittenId;
            map<char, int> currentLastWrittenTime;
            // cout << "b size " << blocks.size() << endl; 

            int time = 1;
            for(int i = 1; i <= vertex_count[t]; i++){
                for(int j = 0; j < (int) blocks[i].transac.size(); j++){
                    node_t currTransac = blocks[i].transac[j];
                    currTransac.time = time++;
                    // cout << "t: " << currTransac.time << endl;
                    if(currTransac.op == 'W'){
                        if(currTransac.time > currentLastWrittenTime[currTransac.attr]){
                            currentLastWrittenId[currTransac.attr]   = currTransac.id;
                            currentLastWrittenTime[currTransac.attr] = currTransac.time;
                            // cout << "t: " << currentLastWrittenTime[currTransac.attr] << " id: " <<  currentLastWrittenId[currTransac.attr] << endl;
                        }
                    }
                }
            }

            for(auto i = attributes.begin(); i != attributes.end(); i++){
                //  cout << *i << ' ' << lastWrittenId[*i] << ' ' << currentLastWrittenId[*i] << endl;
                if(lastWrittenId[*i] != currentLastWrittenId[*i])
                    view = false;
            }

            // if(view) cout << "As últimas escritas são mantidas" << endl;
            // else cout << "Não são mantidas as últimas escritas" << endl;

            // checar se é mantido r(x) antes de w(x) nessa visão
            // vector<vector<int>> currentViewGraph(blocks.size());
            for (int i = 1; i < (int)blocks.size(); ++i){
                for (int j = i+1; j < (int)blocks.size(); ++j){

                    set<char> intersect;
                    set_intersection(blocks[i].writtenAttributes.begin(), blocks[i].writtenAttributes.end(), 
                                     blocks[j].readAttributes.begin(), blocks[j].readAttributes.end(), 
                                     std::inserter(intersect, intersect.begin()));

                    if(!intersect.empty() &&
                        find(attributesGraph[j].begin(), attributesGraph[j].end(), i) != attributesGraph[j].end()){
                        view2 = false;
                    }
                }
            }
            // if(view2) cout << "A ordem é mantida" << endl;
            // else cout << "Não é mantida a ordem" << endl;
            // for (int i = 1; i < blocks.size(); ++i){
            //     cout << blocks[i].id << " ";
            // }
            // cout << endl;

            ++b;
        } while ((!view || !view2) && next_permutation(blocks.begin()+1, blocks.end(), 
                        [](const auto & lhs, const auto & rhs) 
                            { return lhs.id < rhs.id; }));

        if(view && view2) cout << "SV" << endl;
        else cout << "NV" << endl;
        // cout << "permutations: " << ++b << "\n" << endl;
        
        previousCount += vertex_count[t];
    }
    return 0;
}
