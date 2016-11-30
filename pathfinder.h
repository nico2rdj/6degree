#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "ActorNode.h"

//dijkstra algorithm to weighted graph
Vertex* dijkstra( Vertex* actor, Vertex* actor_connect, string outputfile);

//bfs to unweighted graph
Vertex* BFS(Vertex* actor, Vertex* actor_connect, string output_file);

//bfs for actorconnections.cpp
Vertex* actorConnectBFS(Vertex* actor, Vertex* actor_connect);

#endif 

