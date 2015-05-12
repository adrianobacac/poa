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
	Node *beforeCurrent = nullptr; // za oznaku kraja dretve pamtimo gdje je zadnje bila
	bool forbiddenEntry = false;
	Node *current = start;

	
	while (true) {
		if (current->previous.size() > 1) {

			// provjeri ako su svi prijasnji vec obradeni
			unsigned int closed = 0;
			for (Link *previousLink : current->previous) {
				// SYNC zbog provjere obradenih
				if (this->_threadEndPoints.find(previousLink->previous)
						!= this->_threadEndPoints.end()) {
					closed++;
				}

			}
			if (closed < (current->previous.size() - 1)) { // -1 jer je ova dretva dosla iz jednog
				// prijasnji nisu obradeni, umri
				this->_threadEndPoints.insert(beforeCurrent);
				// END SYNC
				forbiddenEntry = true;
				break;
			}else{
				// END SYNC
			}

		}
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
			// SYNC zbog pristupa toProcess, treba probudit main
			for (unsigned int i = 1; i < current->next.size(); ++i) {
				
				this->_toProcess.push(current->next[i]->next);
			}
			// END SYNC
		}
		if (current->next.empty()) {
			break;
		}
		beforeCurrent = current;
		current = current->next[0]->next;

	}
	// SYNC zavrsi obradu
	if (this->_topScoringNode == nullptr) {
		this->_topScoringNode = localMaxScorer;
	} else if (localMaxScorer->score > this->_topScoringNode->score) {
		this->_topScoringNode = localMaxScorer;
	}
	if(!forbiddenEntry){
		this->_threadEndPoints.insert(current);

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

HeaviestBundle::HeaviestBundle(PoMsa *poMsa, int maxThreadCount) :
	_poMsa(poMsa),
	_topScoringNode(nullptr),
	_ends(std::vector<Node *>()),
	_activeThreadCount(0),
	_maxThreadCount(maxThreadCount),
	_toProcess(std::queue<Node *>()),
	_threadEndPoints(std::set<Node *>()){
}

std::vector<Node *> HeaviestBundle::findTopScoringPath() {

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
