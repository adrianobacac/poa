/*
 * Seq.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include "Seq.h"
#include <cassert>

Seq::Seq(std::string name, std::string title, int node_cnt,
         int weight) : name_(name),
                       title_(title),
                       node_cnt_(node_cnt),
                       weight_(weight),
                       consensus_(nullptr),
                       start_node_(nullptr) {
}

void Seq::RescaleWeight(int factor) {
  weight_ *= factor;
}


void Seq::GetNodes(std::list<Node *> *nodeList) {
  assert(start_node_ != nullptr);
  assert(nodeList != nullptr);
  nodeList->clear();
  Node *node = start_node_;
  nodeList->push_back(node);

  Link *link = node->LinkTo(this);
  while (link) {
    node = link->next_node();
    nodeList->push_back(node);
    link = node->LinkTo(this);
  }


}