/*
 * Node.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include "Node.h"

Node::Node(int index, char nucl, std::set<Seq *> seqs, std::set<int> aln_nodes_id) :
    index_(index), nucl_(nucl), seqs_(seqs), aligned_with_node_ids_(aln_nodes_id),
    score_(0),
    best_previous_(nullptr), times_visited_(0) {
}

void Node::AddExitLink(Link *next) {
  exit_links_.push_back(next);
}

void Node::AddSeq(Seq *seq) {
  seqs_.insert(seq);
}

std::list<Node *> Node::Traceback() {
  std::list<Node *> *path = new std::list<Node *>();
  Node *node = this;
  while (node) {
    path->insert(path->begin(), node);
    node = node->best_previous_;
  }
  return *path;
}


std::string Node::DotFormat() {
  return "i" + std::to_string(index_) + "_" + std::string(1, nucl_) + "_" +
         std::to_string(score_);
}

bool Node::HasSeq(Seq *querySeq) {
  return (std::find(seqs_.begin(), seqs_.end(), querySeq) != seqs_.end());
}

Link *Node::LinkTo(Seq *querySeq) {
  for (Link *link: exit_links_) {
    auto seqs = link->seqs();
    if (std::find(seqs.begin(), seqs.end(), querySeq) != seqs.end()) {
      return link;
    }
  }
  return nullptr;
}


Link *Node::LinkTo(Node *queryNode) {
  for (Link *link : exit_links_) {
    if (link->next_node() == queryNode) {
      return link;
    }
  }
  return nullptr;
}

Node::~Node() {
  for (Link *link : exit_links_) {
    delete link;
  }
}
