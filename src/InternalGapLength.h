//
// Created by ppx on 13.05.15..
//

#ifndef POA_INTERNALGAPLENGHT_H
#define POA_INTERNALGAPLENGHT_H


#include "InclusionRule.h"

class InternalGapLength : public InclusionRule {
public:
  int limit_;

  virtual ~InternalGapLength();

  InternalGapLength(int limit);

  virtual bool Check(Seq *seq, Seq *cons);


};


#endif //POA_INTERNALGAPLENGHT_H
