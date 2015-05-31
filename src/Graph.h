//
// Created by Adriano Bacac on 21.03.15.
//
// Representation of partial order multiple sequence alignment graph.
// Must be constructed with GraphFactory using supported formats.
//

#ifndef POA_GRAPH_H_
#define POA_GRAPH_H_

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "Node.h"
#include "Seq.h"
#include "Link.h"

class Graph {
public:
  int node_cnt_;
  int seq_cnt_;
  std::vector<Node *> starts_;
  std::vector<Node *> nodes_;
  std::vector<Seq *> seqs_;
  std::vector<Seq *> cons_;

  // Return all nodes contained in graph.
  std::vector<Node *> nodes() { return nodes_; }

  // Adds new node to graph.
  void AddNode(Node *node) { nodes_.push_back(node); }

  // Returns all starting nodes from gaph.
  // Starting nodes are nodes with no links pointing to them.
  std::vector<Node *> starts() { return starts_; }

  // Adds a node to starting nodes.
  void AddStart(Node *node) { starts_.push_back(node); }

  // Return all sequences contained in graph.
  // Does NOT apply to consensus sequences.
  std::vector<Seq *> seqs() { return seqs_; }

  // Adds a sequence to the list of sequences in graph.
  void AddSeq(Seq *seq) { seqs_.push_back(seq); }

  // Return all consensuses in graph.
  std::vector<Seq *> consensuses() { return cons_; }

  // Adds a new consensus to list of consensuses in graph.
  void AddConsensus(Seq *cons) { cons_.push_back(cons); }

  // Return number of nodes in graph.
  int node_cnt() const { return node_cnt_; }

  // Sets the number of sequences in graph.
  void set_node_cnt(int node_cnt) { node_cnt_ = node_cnt; }

  // Return the number of sequences in graph.
  int seq_cnt() const { return seq_cnt_; }

  // Sets the number of sequences in graph to <seq_cnt>.
  void set_seq_cnt(int seq_cnt) { seq_cnt_ = seq_cnt; }

  // Constructs graph with zero nodes and sequences.
  Graph();

  // Destroys graph.
  virtual ~Graph();

  // Adds sequence <seq> to a path of nodes <path>.
  void CreateSeqOnPath(Seq *seq, std::list<Node *> *path);

  // Creates .dot format that can be viewed with graphviz.
  // Is only applicable to small graphs (< 1000 nodes).
  // Last generated consensus is marked.
  void DrawGraph(std::string path);
};

#endif /* POA_GRAPH_H */
