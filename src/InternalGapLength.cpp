//
// Created by ppx on 13.05.15..
//

#include "InternalGapLength.h"
#include <cassert>

InternalGapLength::~InternalGapLength() {

}

void InternalGapLength::init(Seq *seq, Seq *cons){
    this->_seq = seq;
    this->_cons = cons;
    this-> _gap_length = 0;
    this-> _temp_gap_length = 0;
    this-> _was_first_match = false;

}

void InternalGapLength::process(Node *node){
    assert(_seq != nullptr && _cons != nullptr && node->hasSeq(this->_seq));
    if (!node->hasSeq(_cons) && !_was_first_match){
        return;
    }else if(node->hasSeq(_cons) && !_was_first_match){
        _was_first_match = true;
    }else if(!node->hasSeq(_cons) && _was_first_match){
        _temp_gap_length++;
    }else if(node->hasSeq(_cons) && _was_first_match){
        _gap_length += _temp_gap_length;
        _temp_gap_length = 0;
    }

}

bool InternalGapLength::result(){
    assert(_gap_length >= 0 && _limit >= 0);
    return _gap_length <= _limit;

}

InternalGapLength::InternalGapLength(int limit):_limit(limit), _gap_length(0), _temp_gap_length(0), _was_first_match(false) {
    assert(limit >= 0);
}

InternalGapLength *InternalGapLength::copy() {
    return new InternalGapLength(_limit);
}
