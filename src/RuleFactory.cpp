//
// Created by ppx on 15.05.15..
//
#include "RuleFactory.h"

#include <sstream>
#include <fstream>

#include "PercentageMatchSeqRule.h"
#include "InternalGapLength.h"

int RuleFactory::CreateRules(std::string file_path, std::list<InclusionRule *> *rules) {
  std::ifstream fin;
  fin.open(file_path);

  if (!fin.good()) {
    throw "File " + std::string(file_path) + " can't be opened";
  }
  std::string line;
  while (std::getline(fin, line)) {

    InclusionRule *rule = CreateRule(line);
    if (rule) {
      rules->push_back(rule);
    }
  }
  return EXIT_SUCCESS;
}

InclusionRule *RuleFactory::CreateRule(std::string line) {
  std::string type = line.substr(0, line.find(' ', 0));
  std::stringstream params(line.substr(line.find(' ', 0) + 1, line.length()));

  if (type == "seq_percentage_in_consensus") {
    float lower, upper;
    params >> lower;
    params >> upper;
    return new PercentageMatchSeqRule(lower, upper);


  } else if (type == "internal_gap_length") {
    int limit;
    params >> limit;
    return new InternalGapLength(limit);
  }
  return nullptr;
}
