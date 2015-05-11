#include "SequenceBundler.h"
#include <cassert>
#include <list>
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
	for (InclusionRule *rule : this->rules){
		rule->preprocess(seq, cons);
	}
	std::list<Node *> nodes;
	seq->nodes(&nodes);

	for (Node *node : nodes){
		for (InclusionRule *rule : this->rules){
			rule->process(node);
		}
	}
	for (InclusionRule *rule : this->rules){
		if (!rule->result()){
			return false;
		}
	}
	return true;
}


int SequenceBundler::addSequencesToBundle(std::vector<Seq *> *seqs, Seq *consensus, std::vector<Seq *> *bundled){
	assert(bundled != nullptr);
	bundled->clear();
	int cnt;
	for (Seq *seq : *seqs){
		if (seq->consensus != nullptr && _applyInsertionRules(seq, consensus)){
			seq->consensus = consensus;
			cnt++;
			bundled->push_back(seq);
		}
	}
	if (bundled->empty()){
		return 0;
	}
	return cnt;
}