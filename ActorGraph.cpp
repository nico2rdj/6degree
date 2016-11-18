/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "ActorGraph.h"
#include "ActorNode.h"
#include "pathfinder.h"
 
using namespace std;

ActorGraph::ActorGraph(void) {}
void createGraph(unordered_map<string, Vertex*>& actor_List, unordered_map<string, Movie*>& movie_List);

int main(int argc, char ** argv) {
    
    if (argc != 5) { //./pathfinder movie_casts.tsv u test_pairs.tsv out_paths_unweighted.tsv
        return 1;
    }
    ActorGraph graph;
    
    graph.loadFromFile(argv[1], false, argv);

    return 0;    
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges, char ** argv) {
    // Initialize the file stream
    cout << in_filename << endl;
    ifstream infile(in_filename);
    
    bool have_header = false;

    unordered_map<string, Vertex*> actor_List;
    unordered_map<string, Movie*> movie_List;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

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
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        string movie_year(record[2]);
    
        // we have an actor/movie relationship, now what?

        string actor_key = actor_name;
        string movie_key = movie_title + movie_year;
        unordered_map<string, Vertex*>::const_iterator actor = actor_List.find(actor_key);
        unordered_map<string, Movie*>::const_iterator elem_movie = movie_List.find(movie_key);
        Movie* movie = 0;
        Vertex* vertex_actor = 0;
           

        if(actor == actor_List.end()) {
                      
            vertex_actor = createVertex(actor_name); 
            
            
        } else {
            vertex_actor = actor->second;
        }
           

        if (elem_movie == movie_List.end()) {
            movie = new Movie(movie_title, movie_year);
            movie->actors.push_back(vertex_actor);
            movie_List.insert(make_pair(movie_key, movie));
        } else {
            movie = elem_movie->second;
            movie->actors.push_back(vertex_actor);            
        }

           

        vertex_actor->movies.push_back(movie);

        if(actor == actor_List.end()){
            actor_List.insert(make_pair(actor_key, vertex_actor));
        }


    }


    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    createGraph(actor_List, movie_List);
    
    /// taking actors in the pair file
    ifstream infile_actor(argv[3]);
    cout << argv[3] << endl;

    have_header = false;

      
    // keep reading lines until the end of file is reached
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
        
        cout << "name1" << actor_name1 << endl;
        cout << "name2" << actor_name2 << endl;



        auto actor = actor_List.find(actor_name1)->second;
        auto actortwo = actor_List.find(actor_name2)->second;
       //cout << actor->actor;
    
        Vertex * result = BFS(actor, actortwo, argv[4]);


        if (result) {
            cout << "true\n";    
        } else {
            cout << "false\n";    
        }

    

    }
    
    return true;

}

void createGraph(unordered_map<string, Vertex*>& actor_List, unordered_map<string, Movie*>& movie_List) {
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
               }
            }
        }
     } 
}

