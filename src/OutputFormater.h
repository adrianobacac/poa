//
// Created by ppx on 17.05.15..
//

#ifndef POA_OUTPUTFORMATER_H
#define POA_OUTPUTFORMATER_H

#include <string.h>
#include <iostream>
#include "Graph.h"

class OutputFormater {
public:
  virtual void Format(std::string file_path, Graph *poMsa) = 0;
};


#endif //POA_OUTPUTFORMATER_H
