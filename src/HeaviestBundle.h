/*
 * HeaviestBundle.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

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


  /**
   * Processes branch to find local top score.
   * Branch is a set of Nodes that can be processed in a single run, meaning all of their predecessors have been analyzed.
   *
   * If a node is an end node adds it to ends.
   * Changes top scoring node if better node found.
   *
   * @param start_ Node to start_ from.
   */
  void ProcessBranch(Node *start);

  /**
   * Sets a new top scoring node that is an end node if the top scorer is not an end node.
   *
   * @param topScoringNode Top scoring node.
   * @return Top scoring end node.
   */
  Node *BranchCompletion(Node *topScoringNode);


  HeaviestBundle(Graph *graph);

  /**
   * Finds path containing best scoring node.
   */
  std::list<Node *> FindTopScoringPath();

};

#endif /* HEAVIESTBUNDLE_H_ */
