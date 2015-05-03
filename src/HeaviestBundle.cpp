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

	std::cout << "Zapoceo granu: " << current->nucl << " -- " << current->score
			<< std::endl;
	while (true) {
		std::cout << "Zapoceo:  " << current->nucl << std::endl;
		if (current->previous.size() > 1) {

			// provjeri ako su svi prijasnji vec obradeni
			int closed = 0;
			for (Link *previousLink : current->previous) {
				// SYNC zbog provjere obradenih
				if (this->threadEndPoints.find(previousLink->previous)
						!= this->threadEndPoints.end()) {
					closed++;
				}

			}
			if (closed < (current->previous.size() - 1)) { // -1 jer je ova dretva dosla iz jednog
				// prijasnji nisu obradeni, umri
				std::cout << "------- nesmijem dalje --------" << std::endl;
				this->threadEndPoints.insert(beforeCurrent);
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
			std::cout << "maxWeight:  "<< maxWeight << std::endl;

			current->bestPrevious = bestPreviousScorer;
			current->score = bestPreviousScorer->score + maxWeight;

			if(current->score > localMaxScorer->score){
				localMaxScorer = current;
			}
		}
		std::cout << "Zavrsio:  " << current->nucl << " -- " << current->score
				<< std::endl << std::endl;

		if (current->next.size() > 1) {
			// SYNC zbog pristupa toProcess, treba probudit main
			for (int i = 1; i < current->next.size(); ++i) {
				std::cout << "Dodao za obradu: " << current->next[i]->next->nucl
						<< std::endl;
				this->toProcess.push(current->next[i]->next);
			}
			// END SYNC
		}
		if (current->next.empty()) {
			break;
		}
		beforeCurrent = current;
		current = current->next[0]->next;
		std::cout << "Sljedeci: " << current->nucl << std::endl;

	}
	// SYNC zavrsi obradu
	if (this->topScoringNode == nullptr) {
		this->topScoringNode = localMaxScorer;
	} else if (localMaxScorer->score > this->topScoringNode->score) {
		std::cout << localMaxScorer->score << " > " << this->topScoringNode->score <<std::endl <<std::endl;
		this->topScoringNode = localMaxScorer;
	}
	if(!forbiddenEntry){
		this->threadEndPoints.insert(current);

	}
	// END SYNC
}

void HeaviestBundle::BranchCompletion() {

}

HeaviestBundle::HeaviestBundle(PoMsa *poMsa, int maxThreadCount) {
	this->poMsa = poMsa;

	this->topScoringNode = nullptr;
	this->ends = std::set<Node *>();

	this->activeThreadCount = 0;
	this->maxThreadCount = maxThreadCount;

	this->toProcess = std::queue<Node *>();

	this->threadEndPoints = std::set<Node *>();
}

std::vector<Node *> HeaviestBundle::findTopScoringPath() {

	for (Node* start : this->poMsa->getStarts()) {
		this->toProcess.push(start);
	}

	while (!this->toProcess.empty()) {
		if (this->activeThreadCount < this->maxThreadCount) {
			Node *localStart = this->toProcess.front();
			this->toProcess.pop();

			this->processBranch(localStart);
		}
	}
	return this->topScoringNode->traceback();
}

Node* HeaviestBundle::getTopScoringNode() {
	return this->topScoringNode;
}
