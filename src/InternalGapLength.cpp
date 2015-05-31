//
// Created by ppx on 13.05.15..
//

#include "InternalGapLength.h"
#include <cassert>

InternalGapLength::~InternalGapLength() {

}


InternalGapLength::InternalGapLength(int limit) : limit_(limit) {
  assert(limit >= 0);
}


bool InternalGapLength::Check(Seq *seq, Seq *cons) {
  assert(seq != nullptr && cons != nullptr);
  std::list<Node *> nodes;

  seq->GetNodes(&nodes);
  int largest_gap = 0;
  int temp_cons_gap = 0;
  int temp_seq_gap = 0;
  Node *match = nullptr;
  for (Node *node: nodes) {
    if (!node->HasSeq(cons) && !match) {
      // preskoci sve dok nema nekog zajednickog
      continue;
    }
    if (!node->HasSeq(cons) && match) {
      ++temp_seq_gap;
      continue;
    }
    if (node->HasSeq(cons)) {
      match = node;
      if (temp_cons_gap > largest_gap || temp_seq_gap > largest_gap) {
        largest_gap =
            temp_cons_gap > temp_seq_gap ? temp_cons_gap : temp_seq_gap;
        if (largest_gap > limit_) {
          return false;
        }
      }
      temp_seq_gap = 0;
      temp_cons_gap = 0;
    }

    if (node->LinkTo(seq) != node->LinkTo(cons) && match) {

      // u ovom cvoru se racvaju putevi
      // pronadi duljinu rupe u konsenzusu
      if (!node->LinkTo(cons)) {
        continue;
      }
      Node *cons_node = node->LinkTo(cons)->next_node();
      while (cons_node && !cons_node->HasSeq(seq)) {
        ++temp_cons_gap;
        if (cons_node->LinkTo(cons)) {
          cons_node = cons_node->LinkTo(cons)->next_node();
        } else {
          break;
        }
      }
    }


  }
  return largest_gap <= limit_;
}
