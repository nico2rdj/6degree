#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "ActorGraph.h"
#include "ActorNode.h"

struct actorPair {
    string actor1;
    string actor2;
    string year;
};

// Node class for the Union Find data structure
class NodeUnionFind{
public:
    NodeUnionFind* parent;
    string key;
    Vertex* actor;
    int size;

    NodeUnionFind(Vertex* actorNode) {
        this->actor = actorNode;
        this->key = actorNode->actor;
        this->parent = 0;
        this->size = 1;
    }
    ~NodeUnionFind(){};
};

// Union Find data structure
class UnionFind{
private:
  unordered_map<string, NodeUnionFind*>* unionFindSet;
  int size;

public:
  UnionFind(unordered_map<string, Vertex*> * actors) {
      unionFindSet = new unordered_map<string, NodeUnionFind*>();
      auto it = actors->begin();
      for (; it != actors->end(); ++it) {
          NodeUnionFind* node = new NodeUnionFind(it->second);
          unionFindSet->insert(make_pair(it->first, node));
      }
      size = unionFindSet->size();
  };
  
  NodeUnionFind* find(string actor);
  
  void merge(string actor1, string actor2);
  ~UnionFind() {
      auto it = unionFindSet->begin();
      for (; it != unionFindSet->end(); ++it) {
          delete it->second;
      }

      delete unionFindSet;
  };
  
};

#endif // UNIONFIND_H
