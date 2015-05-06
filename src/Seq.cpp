/*
 * Seq.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include "Seq.h"

Seq::Seq(std::string name, std::string title, int nodeCnt,
		int weight):name(name), title(title), nodeCnt(nodeCnt), weight(weight), consensus(nullptr) {
}

void Seq::rescaleWeight(int factor) {
	weight *= factor;
}

void Seq::setStartNode(Node *stratNode){
	this->startNode = startNode;
}