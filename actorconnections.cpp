#include "ActorGraph.h"
#include "pathfinder.h"
#include <string.h>
#include <unordered_map>
#include "actorconnections.h"
#include "ActorNode.h"
#include <stdio.h>
#include <limits.h>
#include "UnionFind.h"

using namespace std;
void unionFind(vector<actorPair*>& pairs, priority_queue<Movie*, vector<Movie*>, MovieComparator> pq, unordered_map<string, Vertex*>* actor_List);

//display the year where the two actors became first connected 
string display_connection_year(Vertex * actor, Vertex * actor_connect, string year){
    Vertex * tmp = actor;
    string connection = actor->actor + "	" + actor_connect->actor + "	" + year;
    return connection; 
}


int main(int argc, char ** argv){
    
    
    if( argc != 5){
        cout << "issue number of arguments" << endl;
    }

    ActorGraph graph; 
    unordered_map<string, Vertex*> actor_List;    
    unordered_map<string, Movie*> movie_List;
    
    graph.loadFromFile(argv[1], false, argv, actor_List, movie_List);


    priority_queue<Movie*, vector<Movie*>, MovieComparator> pq;

    auto movie_it = movie_List.begin();

    for(;movie_it != movie_List.end(); ++movie_it) {     
        pq.push(movie_it->second);
    }

    findConnections(argv, actor_List, pq);

    movie_it = movie_List.begin();

    for(;movie_it != movie_List.end(); ++movie_it) {     
        delete movie_it->second;
    }
    auto actor_it = actor_List.begin();

    for(;actor_it != actor_List.end(); ++actor_it) {     
        delete actor_it->second;
    }

    
}

//Find the connections between the two actors
bool findConnections(char ** argv, unordered_map<string, Vertex*> actor_List, priority_queue<Movie*, vector<Movie*>, MovieComparator> pq){ 
    
    bool have_header = false;
    ifstream infile_actor(argv[2]);
    ofstream myFile;
    myFile.open(argv[3], std::ios_base::app);
    myFile << "Actor1	Actor2	Year\n";
    myFile.close();

    vector<actorPair*> unionFindPairs;
    while (infile_actor) {
        string s;
        if (!getline( infile_actor, s )) break;
        
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 2) {
            // we should have exactly 2  columns
            continue;
        }

        string actor_name1(record[0]);
        string actor_name2(record[1]);

        auto actor = actor_List.find(actor_name1)->second;
        auto actortwo = actor_List.find(actor_name2)->second;
        
        priority_queue<Movie*, vector<Movie*>, MovieComparator> tmp(pq);
        if(strcmp(argv[4], "bfs") == 0){
            Vertex * result = 0;
            while(!pq.empty()) {
                vector <Movie *> movies;
                string year = "";
                do {
                    Movie* movie = pq.top();
                    pq.pop();
                    year = movie->year;
                    movies.push_back(movie);
                } while(!pq.empty() && pq.top()->year == year);

                addConnections(movies);
                result = actorConnectBFS(actor, actortwo);
                if (result) {
                    ofstream myFile;
                    myFile.open(argv[3], std::ios_base::app);
                    string connection = display_connection_year(actor, actortwo, year);
                    myFile << connection << endl;
                    myFile.close();
                    break;    
                }
                
                auto actor_it = actor_List.begin();

                for(; actor_it != actor_List.end(); ++actor_it) {
                    Vertex * curr_actor = actor_it->second;
                    curr_actor->dist = INT_MAX;
                    curr_actor->prev = 0;
                    curr_actor->done = false;
                }

            }

            if(!result) {
                ofstream myFile;
                myFile.open(argv[3], std::ios_base::app);
                string connection = display_connection_year(actor, actortwo, "9999");
                myFile << connection << endl;
                myFile.close();
            }

            auto actor_it = actor_List.begin();
            
            //reset the graph
            for(; actor_it != actor_List.end(); ++actor_it) {
                actor_it->second->adj.clear();
                actor_it->second->edges.clear();
                Vertex * curr_actor = actor_it->second;
                curr_actor->dist = INT_MAX;
                curr_actor->prev = 0;
                curr_actor->done = false;
            }

        } else if(strcmp(argv[4], "ufind") == 0) {
           actorPair* pair = new actorPair();
           pair->actor1 = actor_name1;
           pair->actor2 = actor_name2;
           pair->year = "9999";

           unionFindPairs.push_back(pair);
        }

        pq = tmp;
    }

    if(strcmp(argv[4], "ufind") == 0) {
        unionFind(unionFindPairs, pq, &actor_List);
    }
    
    int i = 0;
    myFile.open(argv[3], std::ios_base::app);
    auto pairs = unionFindPairs;

    for(; i < pairs.size(); i++) {
            string connection = pairs[i]->actor1 + "	" + pairs[i]->actor2 + "	" + pairs[i]->year; 
        myFile << connection << endl;
        delete pairs[i];
    }
    
    myFile.close();
    
    return true;

}


// We add the connections between the two actors with the movies
void addConnections(vector<Movie*>& movies) {
    int i = 0;
    for (; i < movies.size(); i++) {
        int j = 0;
        for(; j < movies[i]->actors.size(); j++) {
            int k = j + 1;
            for (; k < movies[i]->actors.size(); k++) {
                movies[i]->actors[j]->adj.push_back(movies[i]->actors[k]);
                movies[i]->actors[j]->edges.push_back(movies[i]);

                movies[i]->actors[k]->adj.push_back(movies[i]->actors[j]);
                movies[i]->actors[k]->edges.push_back(movies[i]);

             }    
        }

    }
}

void unionFind(vector<actorPair*>& pairs, priority_queue<Movie*, vector<Movie*>, MovieComparator> pq, unordered_map<string, Vertex*>* actor_List) {

    UnionFind uf(actor_List);
    int foundAllPairs = 0;    
    while(!pq.empty()) {
       vector <Movie *> movies;
       string year = "";
       do {
            Movie* movie = pq.top();
            pq.pop();
            year = movie->year;
            movies.push_back(movie);
       } while(!pq.empty() && pq.top()->year == year);

        int i = 0;
        for (; i < movies.size(); i++) {
            int j = 0;
            for(; j < movies[i]->actors.size(); j++) {
                int k = j + 1;
                for (; k < movies[i]->actors.size(); k++) {
                    uf.merge(movies[i]->actors[j]->actor, movies[i]->actors[k]->actor);
                }    
            }

        }
        
        i = 0;
        for(; i < pairs.size(); i++) {
            if (uf.find(pairs[i]->actor1) == uf.find(pairs[i]->actor2)) {
                if(pairs[i]->year == "9999") {
                    foundAllPairs++;
                    pairs[i]->year = year;
                }
            }  
        }

        if (foundAllPairs == pairs.size()) {
            return;
        }
    }
    
}
