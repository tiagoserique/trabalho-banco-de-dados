#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

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
    vector<vector<node_t>> list;

    readInput(list, vertex_count, stdin);

    for(int t = 0; t < list.size(); ++t){
        for (auto node: list[t]) cout << node.id << ' ';
        cout << endl;

        vector<vector<int>> graph(vertex_count[t]+1);
        for (int i = 0; i < list[t].size(); ++i){
            for (int j = i+1; j < list[t].size(); ++j){
                if(list[t][i].id != list[t][j].id){
                    if(checkConflict(list[t], i, j)){
                        graph[list[t][i].id].push_back(list[t][j].id);
                    }
                }
            }
        }

        for (int i = 1; i <= vertex_count[t]; ++i){
            cout << i << ": ";
            for(auto j: graph[i]) cout << j << ' ';
            cout << endl;
        }
        
        if (hasCycle(graph)) cout << "ciclo :O" << endl;
        else cout << "sem ciclo" << endl;

        /*================ Equivalência por visão ================*/

        set<char> attributes;
        // store all unique attributes
        for(int i = 0; i < list[t].size(); ++i){
            attributes.insert(list[t][i].attr);
        }

        vector<vector<int>> attributesGraph(vertex_count[t]+1);
        for (int i = 0; i < list[t].size(); ++i){
            for (int j = i+1; j < list[t].size(); ++j){
                if(list[t][i].id != list[t][j].id){
                    if(checkView(list[t], i, j)){
                        attributesGraph[list[t][i].id].push_back(list[t][j].id);
                    }
                }
            }
        }

        // armazena o id da ultima escrita do atributo
        map<char, int> lastWrittenId;
        map<char, int> lastWrittenTime;
        for(int i = 1; i <= vertex_count[t]; i++){
            for(int j = 0; j < list[t].size(); j++){
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
            blocks[i].id = i;
            for(int j = 0; j < list[t].size(); j++) if(i == list[t][j].id){
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
        int b = 0;
        do {
            view = true;

            // checar se últimas escritas dos atributos são as últimas nessa visão
            map<char, int> currentViewLastWrittenId;
            map<char, int> currentViewLastWrittenTime;
            // cout << "b size " << blocks.size() << endl; 

            for(int i = 1; i <= blocks.size()-1; i++){
                for(int j = 0; j < blocks[i].transac.size(); j++){
                    if(blocks[i].transac[j].op == 'W'){
                        if(currentViewLastWrittenTime.find(blocks[i].transac[j].attr) != currentViewLastWrittenTime.end()){
                            if(currentViewLastWrittenTime[blocks[i].transac[j].attr] < blocks[i].transac[j].time){
                                currentViewLastWrittenId[blocks[i].transac[j].attr]   = blocks[i].transac[j].id;
                                currentViewLastWrittenTime[blocks[i].transac[j].attr] = blocks[i].transac[j].time;
                            }
                        } else {
                            currentViewLastWrittenId[blocks[i].transac[j].attr]   = blocks[i].transac[j].id;
                            currentViewLastWrittenTime[blocks[i].transac[j].attr] = blocks[i].transac[j].time;
                        }
                    }
                }
            }

            for(auto i = attributes.begin(); i != attributes.end(); i++){
                 cout << *i << ' ' << lastWrittenId[*i] << ' ' << currentViewLastWrittenId[*i] << endl;
                if(lastWrittenId[*i] != currentViewLastWrittenId[*i])
                    view = false;
            }

            if(view) cout << "As últimas escritas são mantidas" << endl;
            else cout << "Não são mantidas as últimas escritas" << endl;

            // checar se é mantido r(x) antes de w(x) nessa visão
            // vector<vector<int>> currentViewGraph(blocks.size());
            // for (int i = 0; i < blocks.size(); ++i){
            //     for (int j = i+1; j < blocks.size(); ++j){
            //         // se houver leitura antes de escrita nessa visão e houver escrita antes de leitura no original
            //         // a visão é inválida
            //         if(haveIntersection(blocks[i].writtenAttributes, blocks[j].readAttributes) &&
            //             find(attributesGraph[j].begin(), attributesGraph[j].end(), i) != attributesGraph[j].end()){
            //             view = false;
            //         }
            //     }
            // }
            // if(view) cout << "A ordem é mantida" << endl;
            // else cout << "Não é mantida a ordem" << endl;
        } while ( next_permutation(blocks.begin()+1, blocks.end(), 
                        [](const auto & lhs, const auto & rhs) 
                            { return lhs.id < rhs.id; }));

        if(view) cout << "tem view" << endl;
        else cout << "nao tem view" << endl;
    }
    return 0;
}
