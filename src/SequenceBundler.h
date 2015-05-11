#include "InclusionRule.h"
#include "Seq.h"
#include "Node.h"
#include "PoMsa.h"

#include <vector>
#include <set>

class SequenceBundler
{
public:
	PoMsa *_pomsa;
	std::set<InclusionRule *> rules;
	SequenceBundler(PoMsa *pomsa);
	virtual ~SequenceBundler();

	void addInclusionRule(InclusionRule *rule);
	void removeInclusionRule(InclusionRule *rule);

	int addSequencesToBundle(std::vector<Seq *> *seqs, Seq *consensus, std::vector<Seq *> *bundled);
	bool _applyInsertionRules(Seq *seq, Seq *cons);
};