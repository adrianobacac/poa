/*
 * PoMsa.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */
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


  std::vector<Node *> nodes() { return nodes_; }

  void AddNode(Node *node) { nodes_.push_back(node); }

  std::vector<Node *> starts() { return starts_; }

  void AddStart(Node *node) { starts_.push_back(node); }

  std::vector<Seq *> seqs() { return seqs_; }

  void AddSeq(Seq *seq) { seqs_.push_back(seq); }

  std::vector<Seq *> consensuses() { return cons_; }

  void AddConsensus(Seq *cons) { cons_.push_back(cons); }

  int node_cnt() const { return node_cnt_; }

  void set_node_cnt(int node_cnt) { node_cnt_ = node_cnt; }

  int seq_cnt() const { return seq_cnt_; }

  void set_seq_cnt(int seq_cnt) { seq_cnt_ = seq_cnt; }

  Graph();

  virtual ~Graph();

  void CreateSeqOnPath(Seq *seq, std::list<Node *> *path);

  void DrawGraph(std::string path);
};

#endif /* POA_GRAPH_H */
