#include "SequenceBundler.h"
#include <cassert>

SequenceBundler::SequenceBundler(ThreadPool *pool):_pool(pool){
	assert(pool != nullptr);
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
	assert(seq!= nullptr && cons != nullptr);
	for (InclusionRule *rule : this->rules){
		if (!rule->check(seq, cons)){
			return false;
		}
	}
	return true;
}


int SequenceBundler::addSequencesToBundle(std::vector<Seq *> *seqs, Seq *consensus, std::vector<Seq *> *bundled){
	assert(bundled != nullptr);
	bundled->clear();
	int cnt = 0;
	std::vector< std::future<int> > results;

	std::mutex *mylock = new std::mutex;
	for (Seq *seq : *seqs){
		if (seq->consensus == nullptr){

			results.emplace_back(
					_pool->enqueue([this, seq, consensus, bundled, mylock] {
						// std::cout << "provjeram za: " << seq->name << std::endl;
						if (_applyInsertionRules(seq, consensus)){
							seq->consensus = consensus;
							mylock->lock();
							bundled->push_back(seq);
							mylock->unlock();
							//seq->rescaleWeight(0);
							//std::cout << seq->name <<"da" << std::endl;
							return 1;
						}
						return 0;
					})
			);

		}
		/*
		if (seq->consensus != nullptr){
			continue;
		}
		std::cout << "provjeram za: " << seq->name << std::endl;
		if(_applyInsertionRules(seq, consensus)){
			seq->consensus = consensus;
			cnt++;
			bundled->push_back(seq);
			std::cout << "da" << std::endl;

		}
		 */

	}
	for(auto && result: results) {
		cnt += result.get();
	}
	return cnt;
}