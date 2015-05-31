#pragma once

#ifndef POA_PERCENTAGEMATCHSEQRULE_H
#define POA_PERCENTAGEMATCHSEQRULE_H

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

#endif