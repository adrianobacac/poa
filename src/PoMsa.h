/*
 * PoMsa.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */
#include <vector>

#ifndef POMSA_H_
#define POMSA_H_

#include <string>
#include <vector>
#include <set>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Node.h"
#include "Seq.h"
#include "Link.h"

class PoMsa {
public:
    std::string version;
    std::string name;
    std::string title;

    int nodeCnt;
    int seqCnt;

    std::vector<Node *> starts;

    std::vector<Node *> nodes;
    std::vector<Seq *> seqs;
    std::vector<int> ungroupedSeqIndex;

    std::vector<Seq * >cons;

    PoMsa(std::string filePath);
    void createSeqOnPath(Seq *seq, std::vector<Node *> path);

    std::vector<Node *> getStarts();


    void drawGraph(std::string path);
};

#endif /* POMSA_H_ */
