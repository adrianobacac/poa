/*
 * PoMsa.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include <vector>
#include "PoMsa.h"
PoMsa::PoMsa(std::string filePath) {
	std::ifstream fin;
	fin.open(filePath);

	if (!fin.good()) {
		throw "File " + std::string(filePath) + " can't be opened";
	}
	std::string line;

	std::getline(fin, line); // VERSION=LPO.0.1
	this->version = line.substr(line.find('=', 0) + 1, line.length());

	std::getline(fin, line); // NAME=ABL1_HUMAN
	this->name = line.substr(line.find('=', 0) + 1, line.length());

	std::getline(fin, line); // PROTO-ONCOGENE TYROSINE-PROTEIN KINASE ABL (EC 2.7.1.112) (P150) (C-ABL).
	this->title = line.substr(line.find('=', 0) + 1, line.length());

	std::getline(fin, line); // LENGTH=1866
	this->nodeCnt = std::stoi(
			line.substr(line.find('=', 0) + 1, line.length()));

	std::getline(fin, line); // SOURCECOUNT=4
	this->seqCnt = std::stoi(line.substr(line.find('=', 0) + 1, line.length()));

	std::vector<int> nodeStartIds;

	for (int seqId = 0; seqId < this->seqCnt; ++seqId) {
		std::getline(fin, line); // SOURCENAME=CRKL_HUMAN
		std::string seqName = line.substr(line.find('=', 0) + 1, line.length());
		std::getline(fin, line); // SOURCEINFO=303 0 1 -1 CRK-LIKE PROTEIN.
		std::string params = line.substr(line.find('=', 0) + 1, line.length());

		std::stringstream os;
		os << line.substr(line.find('=', 0) + 1, line.length());
		int nodeCnt;
		os >> nodeCnt; // sequence node count: 303
		int firstNodeId;
		os >> firstNodeId; // id of first node: 0
		int weight;
		os >> weight; // weight: 1
		int none;
		os >> none; // bundle id: -1 by default
		std::string title;
		std::getline(os, title); // remaining is sequence title: CRK-LIKE PROTEIN.
		this->seqs.push_back(new Seq(seqName, title, nodeCnt, weight));
		nodeStartIds.push_back(firstNodeId);
				

	}
	for (int nodeId = 0; nodeId < this->nodeCnt; ++nodeId) {

		std::stringstream os;
		std::getline(fin, line); // M:L85L151S2S3A153
		os << line;
		char nucl;
		os >> nucl; // Nucleotide or protein: M
		os.ignore(1); // ignore :

		std::vector<Node *> previousNodes; // L
		std::set<int> alignedWithNodeIds;// A
		std::set<Seq *> seqs; // S

		while (!os.eof()) {
			char option;
			if (!(os >> option)) {
				break;
			}
			int value;
			os >> value;
			switch(option){
			case 'L':
				previousNodes.push_back(this->nodes[value]);
				break;
			case 'S':
				seqs.insert(this->seqs[value]);
				break;
			case 'A':
				alignedWithNodeIds.insert(value);
				break;
			}
		}
		// stvori novi cvor
		Node *node = new Node(nodeId, nucl, seqs, alignedWithNodeIds);
		this->nodes.push_back(node);

		// stvori veze prema svim prijasnjim cvorovima
		std::vector<Link *> *previousLinks = new std::vector<Link *>();

		for(Node *previousNode : previousNodes){
			previousLinks->push_back(new Link(previousNode, node));
		}
		node->previous = *previousLinks;
		if (node->previous.empty()){
			this->starts.push_back(node);
		}else{
			for(Link *previousLink : *previousLinks){
				// dodaj link sa novim u sljedece od proslog nodea
				previousLink->previous->next.push_back(previousLink);
			}
		}
		
	}
	for (int i = 0; i < this->seqs.size(); ++i){
		this->seqs[i]->setStartNode(this->nodes[nodeStartIds[i]]);
	}

	fin.close();

}

void PoMsa::createSeqOnPath(Seq* seq, std::vector<Node*> path) {
	Node *previous_node = nullptr;
	for (Node *node : path) {
		node->addSeq(seq);
		if (previous_node){
			previous_node->LinkTo(node)->addSeq(seq);
		}
		previous_node = node;
	}
}

std::vector<Node *> PoMsa::getStarts() {
	return this->starts;

}

std::string PoMsa::dotFormat() {
	std::ofstream fout;
	fout.open("test.dot");
	fout << "digraph {rankdir=LR;" << std::endl;
	for (Node *before : this->nodes) {
		for(Link *nextLink : before->next){
			fout << "\t" << before->dotFormat() << " -> " << nextLink->next->dotFormat() << ";" <<std::endl;
		}
	}
	fout << "}" << std::endl;
	fout.close();
	return "";
}
