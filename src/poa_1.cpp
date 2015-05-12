//============================================================================
// Name        : poa_1.cpp
// Author      : Adriano Bacac
// Version     :
// Copyright   : Your copyright notice
// Description : Consensus generator from partial order sequence aligment
//============================================================================

#include <iostream>

#include "PoMsa.h"
#include "HeaviestBundle.h"
#include "SequenceBundler.h"
#include "PercentageMatchSeqRule.h"
using namespace std;

int main() {
	PoMsa *poMsa = new PoMsa("m_po_mine.aln");
	
	SequenceBundler *bundler = new SequenceBundler();
	bundler->addInclusionRule(new PercentageMatchSeqRule(1.0, 1.0));
	
	HeaviestBundle *hb = new HeaviestBundle(poMsa, 1);
	
	while (true){
		// pronadi najbolji put
		std::vector<Node *> bestPath;
		bestPath = hb->findTopScoringPath();
		// gotovo nalazenje najboljeg puta

		// stvori novu sekvencu
		Seq *new_consensus = new Seq("name", "> title", bestPath.size(), 0);
		poMsa->cons.insert(new_consensus);
		
		Node *previous_node = nullptr;
		for (Node *node : bestPath) {
			node->addSeq(new_consensus);
			if (previous_node){
				previous_node->LinkTo(node)->addSeq(new_consensus);
			}
			previous_node = node;
			std::cout << node->nucl << " -> ";
		}
		std::cout << std::endl;

		// gotovo stvaranje nove sekvence

		// pronadi slicne sekvence
		std::vector<Seq *> *bundle = new std::vector < Seq * > ;
		if (bundler->addSequencesToBundle(&poMsa->seqs, new_consensus, bundle) > 0){
			std::cout << "pronasao slicne sekvence" << std::endl;

			for (Seq *seq : *bundle){
				seq->rescaleWeight(0);
				std::cout << seq->name << std::endl;
			}
			std::cout << "-----------------" << std::endl;
		}
		else{
			std::cout << "nisam pronasao slicne sekvence" << std::endl;

			break;
		}
		std::getchar();
	}


	poMsa->dotFormat();

	std::getchar();
	return 0;
}
