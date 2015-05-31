//
// Created by ppx on 15.05.15..
//

#ifndef POA_RULEFACTORY_H
#define POA_RULEFACTORY_H


#include "InclusionRule.h"

class RuleFactory {
private:
  InclusionRule *CreateRule(std::string line);

public:
  int CreateRules(std::string file_path, std::list<InclusionRule *> *rules);

};


#endif //POA_RULEFACTORY_H
