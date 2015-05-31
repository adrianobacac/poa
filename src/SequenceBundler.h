#ifndef POA_SEQUENCEBUNDLER_H_
#define POA_SEQUENCEBUNDLER_H_

#include "InclusionRule.h"
#include "Seq.h"
#include "Node.h"
#include "Graph.h"
#include "ThreadPool.h"

#include <vector>
#include <set>

class SequenceBundler {
private:
  bool ApplyInsertionRules(Seq *seq, Seq *cons);

public:
  ThreadPool *pool_;
  std::set<InclusionRule *> rules_;

  SequenceBundler(ThreadPool *pool);

  virtual ~SequenceBundler();

  void AddInclusionRule(InclusionRule *rule);

  void RemoveInclusionRule(InclusionRule *rule);

  int AddSequencesToBundle(std::vector<Seq *> seqs, Seq *consensus,
                           std::vector<Seq *> *bundled);


};

#endif // POA_SEQUENCEBUNDLER_H_