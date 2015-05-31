#include "SequenceBundler.h"
#include <cassert>

SequenceBundler::SequenceBundler(ThreadPool *pool) : pool_(pool) {
  assert(pool != nullptr);
}


SequenceBundler::~SequenceBundler() {
}

void SequenceBundler::AddInclusionRule(InclusionRule *rule) {
  assert(rule != nullptr);
  rules_.insert(rule);
}

void SequenceBundler::RemoveInclusionRule(InclusionRule *rule) {
  assert(rule != nullptr);
  auto it = rules_.find(rule);
  if (it != rules_.end()) {
    rules_.erase(rules_.find(rule));
  }
}

bool SequenceBundler::ApplyInsertionRules(Seq *seq, Seq *cons) {
  assert(seq != nullptr && cons != nullptr);
  for (InclusionRule *rule : rules_) {
    if (!rule->Check(seq, cons)) {
      return false;
    }
  }
  return true;
}


int SequenceBundler::AddSequencesToBundle(std::vector<Seq *> seqs, Seq *consensus,
                                          std::vector<Seq *> *bundled) {
  assert(bundled != nullptr);
  bundled->clear();
  int cnt = 0;
  std::vector<std::future<int> > results;

  std::mutex *mylock = new std::mutex;
  for (Seq *seq : seqs) {
    if (!seq->HasConsensus()) {

      results.emplace_back(
          pool_->enqueue([this, seq, consensus, bundled, mylock] {
            if (ApplyInsertionRules(seq, consensus)) {
              seq->set_consensus(consensus);
              mylock->lock();
              bundled->push_back(seq);
              mylock->unlock();
              return 1;
            }
            return 0;
          })
      );

    }
  }
  delete mylock;
  for (auto &&result: results) {
    cnt += result.get();
  }
  return cnt;
}