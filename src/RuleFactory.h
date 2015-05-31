//
// Created by ppx on 15.05.15..
//

#ifndef POA_RULEFACTORY_H
#define POA_RULEFACTORY_H


#include "InclusionRule.h"

class RuleFactory {
public:
    int createRules(std::string filePath, std::list<InclusionRule *> *rules);
private:
    InclusionRule *createRule(std::string line);
};


#endif //POA_RULEFACTORY_H
