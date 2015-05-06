//============================================================================
// Name        : poa_1.cpp
// Author      : Adriano Bacac
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "PoMsa.h"
#include "HeaviestBundle.h"
using namespace std;

int main() {
	PoMsa *poMsa = new PoMsa("m_po_mine.aln");
	std::cout << "Graf stvoren" << std::endl;
	HeaviestBundle *hb = new HeaviestBundle(poMsa, 1);

	std::vector<Node *> bestPath;
	bestPath = hb->findTopScoringPath();

	for (Node *node : bestPath) {
		std::cout << node->nucl << " -> ";
	}
	poMsa->dotFormat();

	std::getchar();
	return 0;
}
