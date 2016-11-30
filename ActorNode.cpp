#include "ActorNode.h"
#include <limits.h>

int counter = 0;

Vertex* createVertex(string actor){
    
    //Vertex* node = (Vertex*)malloc(sizeof(Vertex));
    Vertex* node = new Vertex;
    
    node->index = counter++;
    
    node->actor = actor;
    node->dist = INT_MAX;
    node->done = 0;
    
    return node;
}

Vertex* createVertex(Vertex* node){
    
    //Vertex* node = (Vertex*)malloc(sizeof(Vertex));
    Vertex* new_node = new Vertex;
    
    new_node->index = node->index;
    new_node->dist = node->dist;
    new_node->actor = node->actor;
    new_node->prev_edge = node->prev_edge;
    new_node->prev = node->prev;
    new_node->movies = node->movies;
    new_node->adj = node->adj;
    new_node->edges = node->edges;
    new_node->weight = node->weight;
    
    return new_node;
}

