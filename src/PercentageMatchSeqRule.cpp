#include "PercentageMatchSeqRule.h"
#include <cassert>

PercentageMatchSeqRule::PercentageMatchSeqRule(float lower, float upper) : _lower(lower), _upper(upper), _shared_cnt(0){
	assert(_lower <= _upper);
}


PercentageMatchSeqRule::~PercentageMatchSeqRule(){
}


void PercentageMatchSeqRule::init(Seq *seq, Seq *cons){
	this->_seq = seq;
	this->_cons = cons;
	this->_shared_cnt = 0;

}

void PercentageMatchSeqRule::process(Node *node){
	assert(_seq != nullptr && _cons != nullptr && node->hasSeq(this->_seq));
	if (node->hasSeq(_cons)){
		_shared_cnt++;
	}
}


bool PercentageMatchSeqRule::result(){
	assert(_seq != nullptr && _cons != nullptr);
	float perc = float(_shared_cnt)  / _seq->nodeCnt;
	return _lower <= perc && perc <= _upper;
}

PercentageMatchSeqRule *PercentageMatchSeqRule::copy() {
	return new PercentageMatchSeqRule(_lower, _upper);
}

