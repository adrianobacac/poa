//
// Created by Adriano Bacac on 13.05.15.
//
// Implantation of an inclusion rule to define the maximum allowed length of gap in
// the alignment of two sequences. Gap does not include non-matched edges.
//
// Example of usage:
// InternalGapLength rule(
//   20    // maximum allowed inner gap
// );
// if(rule.Check(seq1, seq2)){
//   ...
// }
//

#ifndef POA_INTERNALGAPLENGHT_H
#define POA_INTERNALGAPLENGHT_H


#include "InclusionRule.h"

class InternalGapLength : public InclusionRule {
public:
  int limit_;

  virtual ~InternalGapLength();

  // Creates internal gap length rule with limit <limit>.
  InternalGapLength(int limit);

  // Compares two sequences, <seq> and <cons>. As soon as a inner gap
  // with length greater then limit is found, return false.
  // If no such gap is found return true.
  virtual bool Check(Seq *seq, Seq *cons);


};


#endif //POA_INTERNALGAPLENGHT_H
