//
// Created by ppx on 29.05.15..
//

#ifndef POA_POGRAPHCREATOR_H
#define POA_POGRAPHCREATOR_H


#include <string>
#include "Graph.h"

class PoGraphCreator {
public:
  Graph *Create(std::string po_path);
};


#endif //POA_POGRAPHCREATOR_H
