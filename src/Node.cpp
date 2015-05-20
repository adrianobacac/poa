/*
 * Node.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include "Node.h"

Node::Node(int index, char nucl, std::set<Seq *> seqs, std::set<int> alnNodesId) :
		index(index), nucl(nucl), seqs(seqs), alignedWithNodeIds(alnNodesId)
, score(0), bestPrevious(nullptr), _times_visited(0) {
}

void Node::addToNext(Link* next) {
	this->next.push_back(next);
}

void Node::addSeq(Seq *seq){
	this->seqs.insert(seq);
}

std::list<Node*> Node::traceback() {
	std::list<Node *> *path = new std::list<Node *>();
	Node *node = this;
	while (node) {
		path->insert(path->begin(), node);
		node = node->bestPrevious;
	}
	return *path;
}


std::string Node::dotFormat() {
	return  "i" + std::to_string(this->index) + "_" + std::string(1, this->nucl)   +"_" + std::to_string(this->score);
}

bool Node::hasSeq(Seq *querySeq){
	return (std::find(this->seqs.begin(), this->seqs.end(), querySeq) != this->seqs.end());
}

Link *Node::LinkTo(Seq *querySeq){
	for (Link *link: next){
		if (std::find(link->seqs.begin(), link->seqs.end(), querySeq) != link->seqs.end()){
			return link;
		}
	}
	return nullptr;
}


Link *Node::LinkTo(Node *queryNode){
	for (Link *link : next){
		if (link->next == queryNode){
			return link;
		}
	}
	return nullptr;
}

Node::~Node() {
	for (Link *link : next){
		delete link;
	}
}
