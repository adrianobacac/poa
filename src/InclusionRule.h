//
// Created by Adriano Bacac on 12.05.15.
//
// Interface to define inclusion rules.
// Inclusion rules define if a sequence can be included in a bundle with consensus.
// Can also be used to compare two sequences.
//

#ifndef POA_INCLUSIONRULE_H
#define POA_INCLUSIONRULE_H

#pragma once

#include "Node.h"


class InclusionRule {
public:
  virtual ~InclusionRule() = 0;

  // Compares sequence to consensus and returns true if
  // they are similar enough and false otherwise.
  virtual bool Check(Seq *seq, Seq *cons) = 0;
};

#endif