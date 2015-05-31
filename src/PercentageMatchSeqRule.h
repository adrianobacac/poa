#pragma once

#ifndef POA_PERCENTAGEMATCHSEQRULE_H
#define POA_PERCENTAGEMATCHSEQRULE_H

#include "InclusionRule.h"


class PercentageMatchSeqRule : public InclusionRule {
public:
  float lower_;
  float upper_;

  PercentageMatchSeqRule(float lower, float upper);

  virtual ~PercentageMatchSeqRule();

  virtual bool Check(Seq *seq, Seq *cons);
};

#endif