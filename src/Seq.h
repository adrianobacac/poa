/*
 * Seq.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#ifndef SEQ_H_
#define SEQ_H_

#include <string>
#include "Node.h"

class Node;

class Seq {

public:
	std::string name;
	std::string title;
	int nodeCnt;

	int startNode;

	int weight;
	Seq *consensus;

	Seq(std::string name, std::string title, int startNode, int nodeCnt,
			int weight);
	void rescaleWeight(int factor);
};

#endif /* SEQ_H_ */
