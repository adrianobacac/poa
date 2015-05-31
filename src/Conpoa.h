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
    Graph *poMsa;
    SequenceBundler *bundler;
    Conpoa(Graph *poMsa, SequenceBundler *bundler);
    int generateConsesuses(int limit, int thread_cnt, OutputFormater *output);
};


#endif //POA_CONPOA_H
