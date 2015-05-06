/*
 * Seq.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#ifndef SEQ_H_
#define SEQ_H_

#include <string>
#include <list>
#include "Node.h"

class Node;

class Seq {

public:
	std::string name;
	std::string title;
	int nodeCnt;


	Node *startNode;
	int weight;
	Seq *consensus;

	Seq(std::string name, std::string title, int nodeCnt,
			int weight);
	void rescaleWeight(int factor);

	void setStartNode(Node *stratNode);
	void nodes(std::list<Node *> *nodeList);
	
};


#endif /* SEQ_H_ */
