/*
 * Link.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: ppx10
 */

#include "Link.h"

Link::Link(Node* previous, Node* next) :
		previous(previous), next(next) {

	std::set<Seq *> intersect;
	set_intersection(next->seqs.begin(), next->seqs.end(),
			previous->seqs.begin(), previous->seqs.end(),
			std::inserter(intersect, intersect.begin()));

	for (Seq *seqNext : intersect) {
		bool found = false;
		for (Link *link : previous->next) {
			if (std::find(link->seqs.begin(), link->seqs.end(), seqNext) != link->seqs.end()) {
				// u linkovima od proslog  postoji link sa ovom sekvencom, treba ju preskocit
				found = true;
				break;
			}
		}
		if (!found) {
			this->seqs.push_back(seqNext);
		}

	}
	return;
}

int Link::weight() {
	int weight = 0;
	for (Seq * seq : seqs) {
		weight += seq->weight;
	}
	return weight;
}

bool Link::hasSeq(Seq *querySeq){
	return std::find(this->seqs.begin(), this->seqs.end(), querySeq) != this->seqs.end();
}
void Link::addSeq(Seq *seq){
	if (!hasSeq(seq)){
		this->seqs.push_back(seq);
	}
}

Link::~Link() {

}

