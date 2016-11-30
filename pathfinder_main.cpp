#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string.h>
#include <limits.h> 
#include "ActorGraph.h"
#include "ActorNode.h"
#include "pathfinder.h"

void createGraph(unordered_map<string, Vertex*>& actor_List, unordered_map<string, Movie*>& movie_List);
bool reading_Actors(char ** argv,  unordered_map<string, Vertex*> actor_List);


int main(int argc, char ** argv) {
    
    if (argc != 5) { //./pathfinder movie_casts.tsv u test_pairs.tsv out_paths_unweighted.tsv
        return 1;
    }
    ActorGraph graph;
    unordered_map<string, Vertex*> actor_List;
    unordered_map<string, Movie*> movie_List;

    graph.loadFromFile(argv[1], false, argv, actor_List, movie_List);
    createGraph(actor_List, movie_List);
    graph.reading_Actors(argv, actor_List);

   


    return 0;    
}


bool ActorGraph::reading_Actors(char ** argv, unordered_map<string, Vertex*> actor_List ){ 
    
    bool have_header = false;
    ifstream infile_actor(argv[3]);
    ofstream myFile;
    myFile.open(argv[4], std::ios_base::app);
    myFile << "(actor)--[movie#@year]-->(actor)--...\n";
    myFile.close();


    while (infile_actor) {
        string s;
                // get the next line
        if (!getline( infile_actor, s )) break;
        
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 2) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name1(record[0]);
        string actor_name2(record[1]);
        



        auto actor = actor_List.find(actor_name1)->second;
        auto actortwo = actor_List.find(actor_name2)->second;
        
        if(strcmp(argv[2], "u") == 0){
            Vertex * result = BFS(actor, actortwo, argv[4]);
        } else if(strcmp(argv[2], "w") == 0) {
            Vertex * result = dijkstra(actor, actortwo, argv[4]);
        }

        auto actor_it = actor_List.begin();

        for(; actor_it != actor_List.end(); ++actor_it) {
            Vertex * curr_actor = actor_it->second;
            curr_actor->dist = INT_MAX;
            curr_actor->prev = 0;
            curr_actor->done = false;
        }
    }
    
    return true;

}

void createGraph(unordered_map<string, Vertex*>& actor_List, unordered_map<string, Movie*>& movie_List){
    
    auto actor_it = actor_List.begin();

    for(; actor_it != actor_List.end(); ++actor_it) {
        Vertex * actor = actor_it->second;
        int actor_index = actor->index;
        auto movie_list = actor->movies;
        int i = 0;
        for(; i < movie_list.size(); i++) {
            for(int j = 0; j < movie_list[i]->actors.size(); j++) {
               int curr_index = movie_list[i]->actors[j]->index;
               if (curr_index == actor_index) {
                   continue;
               }
               auto actor_found = find(actor->adj.begin(), actor->adj.end(), movie_list[i]->actors[j]);
               if (actor_found == actor->adj.end()) {
                   actor->adj.push_back(movie_list[i]->actors[j]);
                   actor->edges.push_back(movie_list[i]);
               } else {
                    auto index = std::distance(actor->adj.begin(), actor_found);
                    if (actor->edges[index]->weight > movie_list[i]->weight) {
                        actor->edges[index] = movie_list[i];
                    }
               }
            }
        }
     } 
}

