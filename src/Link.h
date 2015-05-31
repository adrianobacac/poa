/*
 * Link.h
 *
 *  Created on: Apr 16, 2015
 *      Author: ppx10
 */

#ifndef LINK_H_
#define LINK_H_

#include <algorithm>
#include <iostream>

#include "Node.h"
#include "Seq.h"

class Node;

class Seq;

class Link {
public:
  Node *previous_node_;
  Node *next_node_;
  std::vector<Seq *> seqs_;

  bool HasSeq(Seq *querySeq);

  void AddSeq(Seq *seq);

  std::vector<Seq *> seqs() { return seqs_; };
  //void AddSeq(Seq *seq){seqs_.push_back(seq);}


  Node *previous_node() const { return previous_node_; }

  void set_previous_node(Node *previous_node) { previous_node_ = previous_node; }


  Node *next_node() const { return next_node_; }

  void set_next_node(Node *next_node) { next_node_ = next_node; }


  Link(Node *previous, Node *next);

  int Weight();


  virtual ~Link();
};

#endif /* LINK_H_ */
