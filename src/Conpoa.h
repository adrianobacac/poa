//
// Created by ppx on 31.05.15..
//

#ifndef POA_CONPOA_H
#define POA_CONPOA_H


#include "Graph.h"
#include "OutputFormater.h"
#include "SequenceBundler.h"

class Conpoa {
public:
  Graph *graph_;
  SequenceBundler *bundler_;

  Conpoa(Graph *poMsa, SequenceBundler *bundler);

  int GenerateConsesuses(int limit, int thread_cnt, OutputFormater *output);
};


#endif //POA_CONPOA_H
