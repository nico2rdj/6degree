#ifndef ACTORCONNECTIONS_H
#define ACTORCONNECTIONS_H


using namespace std;

//find connections between two actors
bool findConnections(char ** argv, unordered_map<string, Vertex*> actor_List, priority_queue<Movie*, vector<Movie*>, MovieComparator> pq);

//add connections based on the movies between two actors
void addConnections(vector<Movie*>& movies);


#endif 
