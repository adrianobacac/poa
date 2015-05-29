#include "InclusionRule.h"
#include "Seq.h"
#include "Node.h"
#include "Graph.h"
#include "ThreadPool.h"

#include <vector>
#include <set>

class SequenceBundler
{
public:
	ThreadPool *_pool;
	std::set<InclusionRule *> rules;
	
	SequenceBundler(ThreadPool *pool);
	
	virtual ~SequenceBundler();

	void addInclusionRule(InclusionRule *rule);
	void removeInclusionRule(InclusionRule *rule);

	int addSequencesToBundle(std::vector<Seq *> *seqs, Seq *consensus, std::vector<Seq *> *bundled);
	bool _applyInsertionRules(Seq *seq, Seq *cons);
};