/*
 * Link.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: ppx10
 */

#include "Link.h"

Link::Link(Node *previous, Node *next) :
    previous_node_(previous), next_node_(next) {

  std::set<Seq *> intersect;
  set_intersection(next->seqs().begin(), next->seqs().end(),
                   previous->seqs().begin(), previous->seqs().end(),
                   std::inserter(intersect, intersect.begin()));

  for (Seq *seqNext : intersect) {
    bool found = false;
    for (Link *link : previous->exit_links()) {
      auto seqs = link->seqs();
      if (std::find(seqs.begin(), seqs.end(), seqNext) != seqs.end()) {
        // u linkovima od proslog  postoji link sa ovom sekvencom, treba ju preskocit
        found = true;
        break;
      }
    }
    if (!found) {
      AddSeq(seqNext);
    }

  }
  return;
}

int Link::Weight() {
  int weight = 0;
  for (Seq *seq : seqs_) {
    weight += seq->weight();
  }
  return weight;
}

bool Link::HasSeq(Seq *querySeq) {
  return std::find(seqs_.begin(), seqs_.end(), querySeq) != seqs_.end();
}

void Link::AddSeq(Seq *seq) {
  if (!HasSeq(seq)) {
    seqs_.push_back(seq);
  }
}

Link::~Link() {

}

