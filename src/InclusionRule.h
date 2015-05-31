#ifndef POA_INCLUSIONRULE_H
#define POA_INCLUSIONRULE_H

#pragma once

#include "Node.h"


class InclusionRule {
public:
  Seq *_seq;
  Seq *_cons;

  InclusionRule();

  virtual ~InclusionRule() = 0;

  virtual bool Check(Seq *seq, Seq *cons) = 0;
};

#endif