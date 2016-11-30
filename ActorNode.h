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
    int done;
    int index;
    Vertex* prev;
    Movie* prev_edge;
    string actor;
    vector<Movie*> movies;
    vector<Movie*> edges; 
    int weight = 1;
    
};

Vertex* createVertex(string actor);
Vertex* createVertex(Vertex* node);

class VertexComparator {
public:
    bool operator()(Vertex* lhs, Vertex* rhs) const {
        return lhs->dist > rhs->dist;
    }
};



class Movie {
public:
  string title;
  string year;
  int weight;
  vector <Vertex*> actors;
  Movie(string& title, string& year) {
     this->title = title;
     this->year = year;
     weight = (2015 - stoi(year)) + 1;
  }

  ~Movie(){}
};

class MovieComparator{
public:
    bool operator()(Movie* lhs, Movie* rhs) const {
        return stoi(lhs->year) > stoi(rhs->year);
    }
};

#endif // ACTORNODE_H
