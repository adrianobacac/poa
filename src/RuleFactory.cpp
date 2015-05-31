//
// Created by ppx on 15.05.15..
//
#include "RuleFactory.h"

#include <sstream>
#include <fstream>

#include "PercentageMatchSeqRule.h"
#include "InternalGapLength.h"

int RuleFactory::createRules(std::string filePath, std::list<InclusionRule *> *rules){
    std::ifstream fin;
    fin.open(filePath);

    if (!fin.good()) {
        throw "File " + std::string(filePath) + " can't be opened";
    }
    std::string line;
    while(std::getline(fin, line)){

        InclusionRule *rule = createRule(line);
        if (rule){
            rules->push_back(rule);
        }
    }
    return EXIT_SUCCESS;
}

InclusionRule *RuleFactory::createRule(std::string line) {
    std::string type = line.substr(0, line.find(' ', 0));
    std::stringstream params(line.substr(line.find(' ', 0) + 1, line.length()));

    if (type == "seq_percentage_in_consensus"){
        float lower, upper;
        params >> lower;
        params >> upper;
        return new PercentageMatchSeqRule(lower, upper);


    }else if (type == "internal_gap_length"){
        int limit;
        params >> limit;
        return new InternalGapLength(limit);
    }
    return nullptr;
}
