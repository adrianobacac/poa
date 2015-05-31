#include "PercentageMatchSeqRule.h"
#include <cassert>

PercentageMatchSeqRule::PercentageMatchSeqRule(float lower, float upper) :
    lower_(lower), upper_(upper) {
  assert(lower_ <= upper_);
}


PercentageMatchSeqRule::~PercentageMatchSeqRule() {
}

bool PercentageMatchSeqRule::Check(Seq *seq, Seq *cons) {
  assert(seq != nullptr && cons != nullptr);
  std::list<Node *> nodes;
  seq->GetNodes(&nodes);
  int with_cons_cnt = 0;
  for (Node *node: nodes) {
    if (node->HasSeq(cons)) {
      ++with_cons_cnt;
    }
  }
  float percentage = (float) with_cons_cnt / seq->node_cnt();
  return lower_ <= percentage && percentage <= upper_;
}
