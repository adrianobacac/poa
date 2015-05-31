//
// Created by Adriano Bacac on 16.04.15.
//
// Representation of a single link between two nodes in a
// partial order multiple sequence alignment graph.
//
// Must be constructed alongside Graph with GraphFactory using supported formats.
//

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

  // Returns true if sequence <query_seq> passes this link.
  bool HasSeq(Seq *query_seq);

  // Adds sequence to list of sequences on this link.
  void AddSeq(Seq *seq);

  // Return all sequences on this link.
  std::vector<Seq *> seqs() { return seqs_; };

  // Returns node from which this link starts.
  Node *previous_node() const { return previous_node_; }

  // Changes starting node for this link.
  void set_previous_node(Node *previous_node) { previous_node_ = previous_node; }

  // Returns node where this link ends.
  Node *next_node() const { return next_node_; }

  // Changes ending node for this link.
  void set_next_node(Node *next_node) { next_node_ = next_node; }

  // Constructs link between two nodes.
  // Link is filled with all sequences that belong to both nodes, if the starting node
  // doesn't already have an exit link with such sequence.
  Link(Node *start, Node *end);

  // Calculates weights of link using weights of all sequences on it.
  int Weight();

  virtual ~Link();
};

#endif /* LINK_H_ */
