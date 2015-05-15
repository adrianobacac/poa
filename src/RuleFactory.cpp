//
// Created by ppx on 15.05.15..
//

#include <sstream>
#include "RuleFactory.h"
#include "PercentageMatchSeqRule.h"
#include "InternalGapLength.h"

InclusionRule *RuleFactory::createRule(std::string line) {
    std::string type = line.substr(0, line.find(' ', 0));
    std::stringstream params(line.substr(line.find(' ', 0) + 1, line.length()));

    if (type == "seq_percentage_in_consensus"){
        float lower, upper;
        params >> lower;
        params >> upper;
        return new PercentageMatchSeqRule(lower, upper);


    }else if (line == "internal_gap_length"){
        int limit;
        params >> limit;
        return new InternalGapLength(limit);
    }
    return nullptr;
}
