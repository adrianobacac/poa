//
// Created by ppx on 29.05.15..
//

#include "GraphFactory.h"
#include "PoGraphCreator.h"

Graph *GraphFactory::Create(std::string path) {
  if (path.compare(path.length() - 3, 3, ".po") == 0) {
    PoGraphCreator po;
    return po.Create(path);
  }
  return nullptr;
}