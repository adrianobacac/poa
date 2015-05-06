#include "InclusionRule.h"
#include "Seq.h"
#include <vector>

class SequenceBundler
{
public:
	SequenceBundler();
	virtual ~SequenceBundler();

	void addInclusionRule(InclusionRule *rule);
	void removeInclusionRule(InclusionRule *rule);

	int addSequencesToBundle(std::vector<Seq *> *seqs, Seq *consensus, std::vector<Seq *> *bundled);
};