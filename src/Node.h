/*
 * Node.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <set>

#include "Link.h"
#include "Seq.h"
class Link;
class Seq;

class Node {

public:
	int index;

    std::vector<Link *> previous;
    std::vector<Link *> next;

    std::set<int> alignedWithNodeIds;
    std::set<Seq *>seqs;

    char nucl;

    Node *bestPrevious;
    int score;

    Node(int index, char nucl, std::set<Seq *>seqs, std::set<int> alnNodesId);
    /**
	 * Adds Node to list of next nodes.
	 * @param next Node to add.
	 */
    void addToNext(Link *next);
	

	void addSeq(Seq *seq);
    /**
     * Follow best previous nodes to create path.
     * @return Best path to this node.
     */
    std::vector<Node *> traceback();

	bool hasSeq(Seq *seq);

	Link *LinkTo(Node *queryNode);
	Link *LinkTo(Seq *seq);

    std::string dotFormat();
};

#endif /* NODE_H_ */
