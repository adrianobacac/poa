#include "SequenceBundler.h"
#include <cassert>
SequenceBundler::SequenceBundler(PoMsa *pomsa):_pomsa(pomsa){
}


SequenceBundler::~SequenceBundler(){
}

void SequenceBundler::addInclusionRule(InclusionRule  *rule){
	assert(rule != nullptr);
	this->rules.insert(rule);
}
void SequenceBundler::removeInclusionRule(InclusionRule  *rule){
	assert(rule != nullptr);
	auto it = this->rules.find(rule);
	if (it != this->rules.end()){
		this->rules.erase(this->rules.find(rule));
	}
}
bool SequenceBundler::_applyInsertionRules(Seq *seq, Seq *cons){
	// traverse seq
	// for Node in Seq
	for (InclusionRule *rule : this->rules){
		// process Node
	}
	// check if any rule is false.
	return false;
}


int SequenceBundler::addSequencesToBundle(std::vector<Seq *> *seqs, Seq *consensus, std::vector<Seq *> *bundled){
	assert(bundled != nullptr);
	bundled->clear();
	for (Seq *seq : *seqs){
		if (seq->consensus != nullptr && _applyInsertionRules(seq, consensus)){
			seq->consensus = consensus;
			bundled->push_back(seq);
		}
	}
	if (bundled->empty()){
		return 0;
	}
	return 1;
}