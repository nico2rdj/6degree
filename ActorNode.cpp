#include "ActorNode.h"

int counter = 0;

Vertex* createVertex(string actor){
    
    //Vertex* node = (Vertex*)malloc(sizeof(Vertex));
    Vertex* node = new Vertex;
    
    node->index = counter++;
    
    node->actor = actor;
    
    return node;
}

