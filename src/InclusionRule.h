#pragma once
#include "Node.h"

class InclusionRule{
public:
	Seq *_seq;
	Seq *_cons;

	InclusionRule();
	virtual ~InclusionRule()=0;

	virtual void init(Seq *seq, Seq *cons) = 0;
	virtual void process(Node *node) = 0;
	virtual bool result() = 0;
	virtual InclusionRule *copy()=0;
};

