//
// Created by ppx on 13.05.15..
//

#ifndef POA_INTERNALGAPLENGHT_H
#define POA_INTERNALGAPLENGHT_H


#include "InclusionRule.h"

class InternalGapLength: public InclusionRule {
public:
    int _limit;
    int _gap_length;
    int _temp_gap_length;

    bool _was_first_match;

    virtual ~InternalGapLength();

    InternalGapLength(int limit);

    virtual bool check(Seq *seq, Seq *cons);



};


#endif //POA_INTERNALGAPLENGHT_H
