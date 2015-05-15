#include "PercentageMatchSeqRule.h"
#include <cassert>

PercentageMatchSeqRule::PercentageMatchSeqRule(float lower, float upper) : _lower(lower), _upper(upper), _shared_cnt(0){
	assert(_lower <= _upper);
}


PercentageMatchSeqRule::~PercentageMatchSeqRule(){
}

bool PercentageMatchSeqRule::check(Seq *seq, Seq *cons) {
	std::list<Node *> nodes;
	seq->nodes(&nodes);
	int with_cons_cnt = 0;
	for(Node *node: nodes){
		if(node->hasSeq(cons)){
			with_cons_cnt++;
		}
	}
	float percentage = (float)with_cons_cnt / seq->nodeCnt;
	return _lower <= percentage && percentage <= _upper;
}
