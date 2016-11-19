#include "pathfinder.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <limits.h>


Vertex* BFS(Vertex* actor, Vertex* actor_connect, string output_file){
    ofstream myFile;
    myFile.open(output_file, std::ios_base::app);
    queue<Vertex*> all_connections;
    actor->dist = 0;
    Vertex* actual_connection;
    all_connections.push(actor);
    vector<Vertex*> vertex_visited;
    vertex_visited.push_back(actor);
    int counter = 0;
    while(!all_connections.empty()){
        actual_connection = all_connections.front();
        all_connections.pop();
        if((actual_connection->actor).compare(actor_connect->actor) == 0){
            Vertex* tmp = actual_connection;
            /*for(int i = 0; i < tmp->path.size(); i++){
                myFile << tmp->path[i]->title;
                myFile << tmp->path[i]->year;
            */

            string connection = "(" + tmp->actor + ")";
            while((tmp->actor).compare(actor->actor) != 0){
               
               connection = "[" + tmp->prev_edge->title + "#@" + tmp->prev_edge->year + "]-->" + connection;
               tmp = tmp->prev;
                if(tmp != NULL){
                    connection = "("+tmp->actor + ")--" + connection;


                
                }
            }
            myFile << connection << endl;

            for (int i = 0; i < vertex_visited.size(); i++) {
                vertex_visited[i]->dist = INT_MAX;
            }
            return actor_connect;
        }

        auto connections = actual_connection->adj;
       // if(time){
        for(int i = 0; i < connections.size(); i++){
            if (connections[i]->dist !=  INT_MAX) {
                continue;
            }
                
           // Vertex* edge = createVertex(connections[i]);
           
            Vertex* edge = connections[i];
            edge->dist = actual_connection->dist+1;
            edge->prev = actual_connection;
            edge->prev_edge = actual_connection->edges[i];
            vertex_visited.push_back(edge);

         /*   for(int i = 0; i < actual_connection->edges.size(); i++) {
                for(int j = 0; j < edge->edges.size(); j++){
                    
                    if(actual_connection->edges[i] == edge->edges[j]){
                        
                        edge->path.push_back(actual_connection->edges[i]);
                    }
                }
            }
*/
         
            
            all_connections.push(edge);
        }
       /* time = false;
    }
    else
    {
         for(int i = 0; i < connections.size(); i++){
            Vertex* edge = connections[i];
           
            edge->dist = actual_connection->dist+1;
            edge->prev = actual_connection;
            

            for(int i = 0; i < actual_connection->path.size(); i++) {
                for(int j = 0; j < edge->edges.size(); j++){
                    
                    if(actual_connection->edges[i] == edge->edges[j]){
                        
                        edge->path.push_back(actual_connection->edges[i]);
                    }
                }
            }

            
            all_connections.push(edge);
        }

    }*/
    }
    myFile.close();
    return 0;
}

