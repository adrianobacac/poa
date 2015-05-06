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

	std::cout << previous->nucl << " -> " << next->nucl << std::endl;
	for (Seq *seqNext : intersect) {
		std::cout << seqNext->name << std::endl;
		bool found = false;
		for (Link *link : previous->next) {
			if (std::find(link->seqs.begin(), link->seqs.end(), seqNext)
					!= link->seqs.end()) {
				// u linkovima od proslog  postoji link sa ovom sekvencom, treba ju preskocit
				found = true;
				break;
			}
		}
		if (!found) {
			std::cout << " ^ dodajem" << std::endl;
			this->seqs.push_back(seqNext);
		}

	}
	return;
	for (Seq *seqNext : next->seqs) {
		for (Seq *seqPrev : previous->seqs) {
			if (seqPrev == seqNext) {
				this->seqs.push_back(seqNext);
				continue;
				// TODO popravi ovo ispod
				for (Link *link : previous->next) {
					if (std::find(link->seqs.begin(), link->seqs.end(), seqNext)
							== link->seqs.end()) {
						// u linkovima od proslog ne postoji link sa ovom sekvencom, da je postojao taj bi bio pravi
						// u ovaj link stavljamo ovu sekvencu

						std::cout << "_" << std::endl;
						this->seqs.push_back(seqNext);
						break;
					}
				}
				break;
			}
		}
	}
}

int Link::weight() {
	int weight = 0;
	for (Seq * seq : seqs) {
		std::cout << "*" << std::endl;
		weight += seq->weight;
	}
	return weight;
}

bool Link::hasSeq(Seq *querySeq){
	return std::find(this->seqs.begin(), this->seqs.end(), querySeq) != this->seqs.end();
}

Link::~Link() {

}

