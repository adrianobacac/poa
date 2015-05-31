/*
 * PoMsa.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */
#include "Graph.h"


#include <fstream>
#include <sstream>

Graph::Graph():nodeCnt(0), seqCnt(0){

}

void Graph::createSeqOnPath(Seq* seq, std::list<Node*> path) {
	Node *previous_node = nullptr;
	for (Node *node : path) {
		node->addSeq(seq);
		if (previous_node){
			previous_node->LinkTo(node)->addSeq(seq);
		}
		previous_node = node;
	}
}

std::vector<Node *> Graph::getStarts() {
	return this->starts;

}

void Graph::drawGraph(std::string name) {
	std::ofstream fout;
	fout.open(("graphs/" + name + ".dot").c_str());
	fout << "digraph {rankdir=LR;" << std::endl;
	Seq *lastConsensus = nullptr;
	if(cons.size()) {
		lastConsensus = cons[cons.size() - 1];
	}
	for (Node *before : this->nodes) {
		for(Link *nextLink : before->next){

			std::string line = before->dotFormat() + " -> " + nextLink->next->dotFormat() +  "[ label = " +
					std::to_string(nextLink->weight());

			if (lastConsensus && nextLink->hasSeq(lastConsensus)) {
				line += "fillcolor = red";
			}
			fout << "\t" << line << "];" <<std::endl;
		}
	}
	fout << "}" << std::endl;
	fout.close();

}

Graph::~Graph() {
	for(Node *node:nodes){
		delete node;
	}
	for(Seq *seq:seqs){
		delete seq;
	}
	for(Seq *con: cons){
		delete con;
	}
}
