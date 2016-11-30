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


public:
    ActorGraph(void);
    
    //load the movies and actors from the file and create our actorList and movie_List
    bool loadFromFile(const char* in_filename, bool use_weighted_edges, char ** argv, unordered_map<string, Vertex*> &actor_List, unordered_map<string, Movie*> &movie_List);

    //we read the actors in the file and depending on weighted or unweighted we find the connections between the two actors
     bool reading_Actors(char ** argv,  unordered_map<string, Vertex*> actor_List);


 
};


#endif // ACTORGRAPH_H
