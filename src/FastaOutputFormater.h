//
// Created by ppx on 17.05.15..
//

#ifndef POA_FASTAOUTPUTFORMATER_H
#define POA_FASTAOUTPUTFORMATER_H


#include "OutputFormater.h"

class FastaOutputFormater : public OutputFormater {
  void Format(std::string file_path, Graph *poMsa);
};


#endif //POA_FASTAOUTPUTFORMATER_H
