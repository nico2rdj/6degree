#include "pathfinder.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <limits.h>


//display the connections between the two actors
string display_connection(Vertex * actor, Vertex* actor_connect) {
    Vertex* tmp = actor_connect;
    string connection = "(" + tmp->actor + ")";
    while((tmp->actor).compare(actor->actor) != 0){
       
       connection = "[" + tmp->prev_edge->title + "#@" + tmp->prev_edge->year + "]-->" + connection;
       tmp = tmp->prev;
        if(tmp != NULL){
            connection = "("+tmp->actor + ")--" + connection;     
        }
    }
    return connection;
}

//return the/one of the shortest path( movies) between two actors for unweighted graph
Vertex* BFS(Vertex* actor, Vertex* actor_connect, string output_file){
    ofstream myFile;
    myFile.open(output_file, std::ios_base::app);
    queue<Vertex*> all_connections;
    actor->dist = 0;
    Vertex* actual_connection;
    all_connections.push(actor);
    int counter = 0;
    while(!all_connections.empty()){
        actual_connection = all_connections.front();
        all_connections.pop();
        if((actual_connection->actor).compare(actor_connect->actor) == 0){
            Vertex* tmp = actual_connection;
  
            string connection = display_connection(actor, actual_connection);
            myFile << connection << endl;

            myFile.close();            
            return actor_connect;
        }

        auto connections = actual_connection->adj;
      
        for(int i = 0; i < connections.size(); i++){
            if (connections[i]->dist !=  INT_MAX) {
                continue;
            }
                       
            Vertex* edge = connections[i];
            edge->dist = actual_connection->dist+1;
            edge->prev = actual_connection;
            edge->prev_edge = actual_connection->edges[i];

            all_connections.push(edge);
        }
    }
    myFile.close();
    return 0;
}



//return the/one of the shortest path( movies) between two actors for weighted graph
Vertex* dijkstra( Vertex* actor, Vertex* actor_connect, string output_file) { 
  ofstream myFile;
  myFile.open(output_file, std::ios_base::app);
  priority_queue<Vertex*, vector<Vertex*>, VertexComparator> pq;
  actor->dist = 0;
  pq.push(actor); 
  while (!pq.empty()) {
    Vertex *actual_connection = pq.top(); 
    pq.pop();
    if((actual_connection->actor).compare(actor_connect->actor) == 0){
        Vertex* tmp = actual_connection;
  
        string connection = display_connection(actor, actual_connection);
        myFile << connection << endl;

        myFile.close();
        return actor_connect;

    }
    if (!actual_connection->done) {
      actual_connection->done = 1;
      auto connections = actual_connection->adj;
      for(int i = 0; i < connections.size(); i++) {  
            Vertex* neighbor = connections[i];
            int curr_dist = actual_connection->dist + actual_connection->edges[i]->weight;
            if (curr_dist < neighbor->dist) {
                neighbor->prev = actual_connection;
                neighbor->dist = curr_dist;
                neighbor->prev_edge = actual_connection->edges[i];
                pq.push(neighbor);
            }
       }
    }
  }
}


      

//BFS used for actorconnections 
Vertex* actorConnectBFS(Vertex* actor, Vertex* actor_connect){
    queue<Vertex*> all_connections;
    actor->dist = 0;
    Vertex* actual_connection;
    all_connections.push(actor);
    vector<Vertex*> vertex_visited;
    int counter = 0;
    while(!all_connections.empty()){
        actual_connection = all_connections.front();
        all_connections.pop();
        if((actual_connection->actor).compare(actor_connect->actor) == 0){
            return actor_connect;
        }

        auto connections = actual_connection->adj;
        for(int i = 0; i < connections.size(); i++){
            if (connections[i]->dist !=  INT_MAX) {
                continue;
            }
                 
            Vertex* edge = connections[i];
            edge->dist = actual_connection->dist+1;
            edge->prev = actual_connection;
            edge->prev_edge = actual_connection->edges[i];

            all_connections.push(edge);
        }

    }
    return 0;
}
