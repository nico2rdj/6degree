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
#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
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
        Movie* movie;
        Vertex* vertex_actor;

        if(actor == actor_List.end()) {
            vertex_actor = createVertex(actor_name);            
        } else {
            vertex_actor = actor->second;
        }

        if (elem_movie == movie_List.end()) {
            movie = new Movie(movie_title, movie_year);
            movie->actors.push_back(vertex_actor);
            movie_list.insert(movie_key, movie);
        } else {
            movie = elem_movie->second;
            movie->actors.push_back(vertex_actor);            
        }


        vector_actor->movies.push_back(movie);

        if(actor == actor_List.end()){
            actor_list.insert(actor_key, vertex_actor);
        }


    }

    createGraph(actor_List, movie_List);

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

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
            for(int j = 0; j < movie_list[i].size(); j++) {
               int curr_index = movie_list[i][j].index;
               if (curr_index != actor_index && actor->adj.find(curr_index) != actor->adj->end()) {
                   actor->adj.push_back(curr_index);
               }
            }
        }
     } 
}
