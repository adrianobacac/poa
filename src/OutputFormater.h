//
// Created by ppx on 17.05.15..
//

#ifndef POA_OUTPUTFORMATER_H
#define POA_OUTPUTFORMATER_H

#include <string.h>
#include <iostream>
#include "PoMsa.h"

class OutputFormater {
public:
    virtual void format(std::string file_path, PoMsa *poMsa)=0;
};


#endif //POA_OUTPUTFORMATER_H
