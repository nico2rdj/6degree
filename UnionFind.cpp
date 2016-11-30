#include "UnionFind.h"

using namespace std;

NodeUnionFind* UnionFind::find(string actor){
  auto actorIt = this->unionFindSet->find(actor);
  auto actorNode = actorIt->second;
  if (actorNode->parent == 0) 
    return actorNode;
  NodeUnionFind* curr = actorNode;
  
  // Find the root by iteratively going up
  while (curr->parent != 0) {
    curr = curr->parent;
  }
  // path compression
  actorNode->parent = curr; 
  return curr;
}

void UnionFind::merge(string actor1, string actor2){
  NodeUnionFind* root1 = find(actor1);
  NodeUnionFind* root2 = find(actor2);

  // If in same set then already merged
  if (root1 == root2) 
      return; 
  if (root1->size > root2->size) {
    root2->parent = root1;
    root1->size += root2->size;
  } else {
    root1->parent = root2;
    root2->size += root1->size;
  }
  this->size--;
}
