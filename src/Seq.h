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

  std::string name_;
  std::string title_;

  int node_cnt_;
  Node *start_node_;
  int weight_;
  Seq *consensus_;

  Node *start_node() const { return start_node_; }

  void set_start_node(Node *start_node) { start_node_ = start_node; }

  bool HasStartNode() { return start_node_ != nullptr; }

  int weight() const { return weight_; }

  void set_weight(int weight) { weight_ = weight; }

  Seq *consensus() const { return consensus_; }

  void set_consensus(Seq *consensus) { consensus_ = consensus; }

  bool HasConsensus() { return consensus_ != nullptr; }

  int node_cnt() const { return node_cnt_; }

  const std::string &title() const { return title_; }

  void set_title(const std::string &name) { title_ = name; }

  const std::string &name() const { return name_; }

  void set_name(const std::string &name) { name_ = name; }

  Seq(std::string name, std::string title, int node_cnt,
      int weight);

  void RescaleWeight(int factor);

  void GetNodes(std::list<Node *> *nodeList);

};


#endif /* SEQ_H_ */
