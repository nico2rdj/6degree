/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "ActorGraph.h"
#include "ActorNode.h"
#include "pathfinder.h"


// Maybe include some data structures here

using namespace std;

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here

public:
    ActorGraph(void);

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
     bool loadFromFile(const char* in_filename, bool use_weighted_edges, char ** argv, unordered_map<string, Vertex*> &actor_List, unordered_map<string, Movie*> &movie_List);

     bool reading_Actors(char ** argv,  unordered_map<string, Vertex*> actor_List);


 
};


#endif // ACTORGRAPH_H
