/*
 * PoMsa.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */
#ifndef POA_GRAPH_H_
#define POA_GRAPH_H_

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "Node.h"
#include "Seq.h"
#include "Link.h"

class Graph {
public:
    std::string version;
    std::string name;
    std::string title;

    int nodeCnt;
    int seqCnt;

    std::vector<Node *> starts;

    std::vector<Node *> nodes;
    std::vector<Seq *> seqs;

    std::vector<Seq * >cons;

    Graph();

    virtual ~Graph();

    void createSeqOnPath(Seq *seq, std::list<Node *> path);

    std::vector<Node *> getStarts();


    void drawGraph(std::string path);
};

#endif /* POA_GRAPH_H */
