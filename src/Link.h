/*
 * Link.h
 *
 *  Created on: Apr 16, 2015
 *      Author: ppx10
 */

#ifndef LINK_H_
#define LINK_H_

#include <algorithm>
#include <iostream>

#include "Node.h"
#include "Seq.h"

class Node;
class Seq;

class Link {
public:
	Node *previous;
	Node *next;

	std::vector<Seq *> seqs;

	Link(Node *previous, Node *next);

	int weight();
	
	bool hasSeq(Seq *querySeq);
	void addSeq(Seq *seq);

	virtual ~Link();
};

#endif /* LINK_H_ */
