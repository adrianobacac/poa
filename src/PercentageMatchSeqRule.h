#pragma once
#include "InclusionRule.h"
#
class PercentageMatchSeqRule :
	public InclusionRule
{
public:
	float _lower;
	float _upper;
	int _shared_cnt;

	PercentageMatchSeqRule(float lower, float upper);
	virtual ~PercentageMatchSeqRule();
	virtual bool check(Seq *seq, Seq *cons);
};

