/*
 * PoMsa.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */
#include "Graph.h"


#include <fstream>
#include <sstream>

Graph::Graph() : node_cnt_(0), seq_cnt_(0) {
}

void Graph::CreateSeqOnPath(Seq *seq, std::list<Node *> *path) {
  Node *previous_node = nullptr;
  for (Node *node : *path) {
    node->AddSeq(seq);
    if (previous_node) {
      previous_node->LinkTo(node)->AddSeq(seq);
    }
    previous_node = node;
  }
}


void Graph::DrawGraph(std::string name) {
  std::ofstream fout;
  fout.open(("graphs/" + name + ".dot").c_str());
  fout << "digraph {rankdir=LR;" << std::endl;
  Seq *lastConsensus = nullptr;
  if (cons_.size()) {
    lastConsensus = cons_[cons_.size() - 1];
  }
  for (Node *before : this->nodes_) {
    for (Link *nextLink : before->exit_links()) {

      std::string line =
          before->DotFormat() + " -> " + nextLink->next_node()->DotFormat() +
          "[ label = " + std::to_string(nextLink->Weight());

      if (lastConsensus && nextLink->HasSeq(lastConsensus)) {
        line += "fillcolor = red";
      }
      fout << "\t" << line << "];" << std::endl;
    }
  }
  fout << "}" << std::endl;
  fout.close();

}

Graph::~Graph() {
  for (Node *node:nodes_) {
    delete node;
  }
  for (Seq *seq:seqs_) {
    delete seq;
  }
  for (Seq *con: cons_) {
    delete con;
  }
}
