#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

class Movie;

struct Vertex
{
    vector<Vertex*> adj;
    int dist;
    int index;
    Vertex* prev;
    Movie* prev_edge;
    string actor;
    vector<Movie*> movies;
    vector<Movie*> edges; // tout les films de l'acteur
    vector<Movie*> path;

};

Vertex* createVertex(string actor);
Vertex* createVertex(Vertex* node);

class Movie {
public:
  string title;
  string year;
  vector <Vertex*> actors;
  Movie(string& title, string& year){
     this->title = title;
     this->year = year;
  }
};

#endif // ACTORNODE_H
