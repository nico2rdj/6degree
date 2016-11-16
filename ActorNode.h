#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

struct Vertex
{
    vector<int> adj;
    int dist;
    int index;
    int prev;
    string actor;
    vector<Movie*> movies;
};

int counter = 0;

Vertex* createVertex(string actor){
    Vertex* node = (Vertex*)malloc(sizeof(Vertex));
    node->index = counter++;
    node->actor = actor;
    return node;
}

class Movie {
public:
  string title;
  int year;
  vector <Vertex*> actors;
  Movie(string title, unsigned int year){
     this->title = title;
     this->year = year;
  }
};
