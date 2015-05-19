/*
 * Seq.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include "Seq.h"
#include <cassert>

Seq::Seq(std::string name, std::string title, int nodeCnt,
		int weight):name(name), title(title), nodeCnt(nodeCnt), weight(weight), consensus(nullptr), startNode(nullptr) {
}

void Seq::rescaleWeight(int factor) {
	weight *= factor;
}

void Seq::setStartNode(Node *startNode){
	assert(startNode->hasSeq(this));
	this->startNode = startNode;
}

void Seq::nodes(std::list<Node *> *nodeList){
	assert(this->startNode != nullptr);
	assert(nodeList != nullptr);
	nodeList->clear();
	Node *node = this->startNode;
	nodeList->push_back(node);

	Link *link = node->LinkTo(this);
	while (link){
		node = link->next;
		nodeList->push_back(node);
		link = node->LinkTo(this);
	}
	

}