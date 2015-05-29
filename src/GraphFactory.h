//
// Created by ppx on 29.05.15..
//

#ifndef POA_GRAPHFACTORY_H
#define POA_GRAPHFACTORY_H


#include <string>
#include "Graph.h"

class GraphFactory {
public:
    Graph *create(std::string path);

};


#endif //POA_GRAPHFACTORY_H
