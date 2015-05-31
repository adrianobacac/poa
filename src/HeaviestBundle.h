
// Created by Adriano Bacac on 02.04.2015.
//
// Algorithm used to find best path in graph.
// Processes every node in graph and sets their best predecessor node.
//
//

#ifndef HEAVIESTBUNDLE_H_
#define HEAVIESTBUNDLE_H_

#include <queue>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "Graph.h"

class HeaviestBundle {

public:
  Graph *graph_;
  Node *top_scoring_node_;
  std::vector<Node *> ends_;
  std::queue<Node *> to_process_;

  //
  // Processes branch starting from <start> to find local top score.
  // Branch is a set of Nodes that can be processed in a single run,
  // meaning all of their predecessors have been analyzed.
  //
  // Sets best previous node for each node in branch.
  //
  // If a node is an end node adds it to ends.
  // Changes top scoring node if better node found.
  //
  void ProcessBranch(Node *start);

  //
  // Finds a new top scoring node that is an end node if the top scorer is not an end node.
  //
  Node *BranchCompletion(Node *topScoringNode);


  HeaviestBundle(Graph *graph);

  //
  // Finds path containing best scoring node.
  //
  std::list<Node *> FindTopScoringPath();

};

#endif /* HEAVIESTBUNDLE_H_ */
