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
#include "PoMsa.h"

class HeaviestBundle {

public:
    PoMsa *poMsa;

    Node *topScoringNode;
    std::vector<Node*> ends;

    int activeThreadCount;
    int maxThreadCount;

    std::queue<Node*> toProcess;

    std::set<Node*> threadEndPoints;

    /**
     * Processes branch to find local top score.
     * Branch is a set of Nodes that can be processed in a single run, meaning all of their predecessors have been analyzed.
     *
     * If a node is an end node adds it to ends.
     * Changes top scoring node if better node found.
     *
     * @param start_ Node to start_ from.
     */
    void processBranch(Node *start);

    /**
     * Sets a new top scoring node that is an end node if the top scorer is not an end node.
     *
     * @param topScoringNode Top scoring node.
     * @return Top scoring end node.
     */
    void BranchCompletion();



    HeaviestBundle(PoMsa *poMsa, int maxTreadCount);
    /**
     * Finds path containing best scoring node.
     */
    std::vector<Node *> findTopScoringPath();

    Node *getTopScoringNode();
};

#endif /* HEAVIESTBUNDLE_H_ */
