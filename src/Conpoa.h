//
// Created by Adriano Bacac on 31.05.15.
//
// Finds multiple consensuses in graph using sequence bundler to group sequences
// that can be grouped with individual consensus.
//
// Example of usage:
// Conpoa conpoa(graph, bundler)
// conpoa.GenerateConsesuses(
//          3,      // maximum number of consensuses to generate
//          output  // class used to generate output
// )
//
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

  // Constructor initializing which graph to search in how to group generated
  // consensuses.
  Conpoa(Graph *graph, SequenceBundler *bundler);

  // Analyzes preset graph with preset bundler and generates a maximum of <limit>
  // consensuses. Uses <output> to generate output.
  int GenerateConsesuses(int limit, OutputFormater *output);
};


#endif //POA_CONPOA_H
