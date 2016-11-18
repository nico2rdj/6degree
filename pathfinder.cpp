#include "pathfinder.h"
#include <fstream>

Vertex* BFS(Vertex* actor, Vertex* actor_connect, string output_file){
    ofstream myFile;
    myFile.open(output_file, std::ios_base::app);
    queue<Vertex*> all_connections;
    actor->dist = 0;
    Vertex* actual_connection;
    
    all_connections.push(actor);
    while(!all_connections.empty()){
        actual_connection = all_connections.front();
        all_connections.pop();
        if(actual_connection == actor_connect){
            Vertex* tmp = actual_connection;
            /*for(int i = 0; i < tmp->path.size(); i++){
                myFile << tmp->path[i]->title;
                myFile << tmp->path[i]->year;
            }*/
            if(tmp->prev != NULL){
                myFile << tmp->actor;
                cout << tmp->actor << endl;
                
                tmp = tmp->prev; 
               
            }
            myFile << "\n";
            return actor_connect;
        }

        auto connections = actual_connection->adj;
       
       // if(time){
        for(int i = 0; i < connections.size(); i++){
            Vertex* edge = connections[i];
           
            edge->dist = actual_connection->dist+1;
            edge->prev = actual_connection;
            

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

