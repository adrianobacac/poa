//
// Created by ppx on 17.05.15..
//

#ifndef POA_FASTAOUTPUTFORMATER_H
#define POA_FASTAOUTPUTFORMATER_H


#include "OutputFormater.h"

class FastaOutputFormater:public OutputFormater {
    void format(std::string file_path, PoMsa *poMsa);
};


#endif //POA_FASTAOUTPUTFORMATER_H
