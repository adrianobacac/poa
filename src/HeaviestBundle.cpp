/*
 * HeaviestBundle.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include "HeaviestBundle.h"

void HeaviestBundle::processBranch(Node *start) {

	Node *localMaxScorer = start;

	if (start->previous.empty()) {
		//start->score = 0;
	}
	Node *current = start;

	
	while (true) {

		if (current->previous.size() > 1) {
			current->_times_visited++;
			if(current->_times_visited != current->previous.size()){
				break;
			}

		}
		// reset for next round
		current->_times_visited = 0;
		if (current->previous.size() > 0) {

			// trazimo najbolji prijasnji
			int maxWeight = -1; // sigurno nece bit
			int maxPreviousScore = 0; // gledamo ako imaju istu tezinu rubova
			Node *bestPreviousScorer;
			for (Link *link : current->previous) {
				int weight = link->weight();

				if (weight > maxWeight
						|| (weight == maxWeight
								&& link->previous->score > maxPreviousScore)) {
					maxWeight = weight;
					bestPreviousScorer = link->previous;
					maxPreviousScore = link->previous->score;
				}
			}

			current->bestPrevious = bestPreviousScorer;
			current->score = bestPreviousScorer->score + maxWeight;

			if(current->score > localMaxScorer->score){
				localMaxScorer = current;
			}
		}


		if (current->next.size() > 1) {
			// std::cout << "multiple next: "<<current->nucl <<std::endl;
			// SYNC zbog pristupa toProcess, treba probudit main
			for (unsigned int i = 1; i < current->next.size(); ++i) {
				this->_toProcess.push(current->next[i]->next);
			}
			// END SYNC
		}
		if (current->next.empty()) {
			this->_ends.push_back(current);
			break;
		}
		current = current->next[0]->next;

	}
	// SYNC zavrsi obradu
	if (this->_topScoringNode == nullptr) {
		this->_topScoringNode = localMaxScorer;
	} else if (localMaxScorer->score > this->_topScoringNode->score) {
		this->_topScoringNode = localMaxScorer;
	}
	// END SYNC
}

Node *HeaviestBundle::branchCompletion(Node *topScoringNode) {
	if (topScoringNode->next.size() != 0){
		Node *best = this->_ends[0];
		for (Node *ending : this->_ends){
			if (ending->score > best->score){
				best = ending;
			}
		}
		this->_topScoringNode = best;
	}
	return this->_topScoringNode;
}

HeaviestBundle::HeaviestBundle(Graph *poMsa, int maxThreadCount) :
	_poMsa(poMsa),
	_topScoringNode(nullptr),
	_ends(std::vector<Node *>()),
	_activeThreadCount(0),
	_maxThreadCount(maxThreadCount),
	_toProcess(std::queue<Node *>()){
}

std::list<Node *> HeaviestBundle::findTopScoringPath() {
	for (Node* start : this->_poMsa->getStarts()) {
		this->_toProcess.push(start);
	}

	while (!this->_toProcess.empty()) {
		if (this->_activeThreadCount < this->_maxThreadCount) {
			Node *localStart = this->_toProcess.front();
			this->_toProcess.pop();

			this->processBranch(localStart);
		}
	}

	return this->branchCompletion(this->_topScoringNode)->traceback();
}

Node* HeaviestBundle::getTopScoringNode() {
	return this->_topScoringNode;
}
