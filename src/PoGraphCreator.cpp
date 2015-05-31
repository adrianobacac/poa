//
// Created by ppx on 29.05.15..
//

#include <fstream>
#include <sstream>
#include "PoGraphCreator.h"

Graph *PoGraphCreator::create(std::string filePath) {
    std::ifstream fin;
    fin.open(filePath);

    Graph *graph = new Graph();

    if (!fin.good()) {
        throw "File " + std::string(filePath) + " can't be opened";
    }
    std::string line;

    std::getline(fin, line); // VERSION=LPO.0.1
    graph->version = line.substr(line.find('=', 0) + 1, line.length());

    std::getline(fin, line); // NAME=ABL1_HUMAN
    graph->name = line.substr(line.find('=', 0) + 1, line.length());

    std::getline(fin, line); // PROTO-ONCOGENE TYROSINE-PROTEIN KINASE ABL (EC 2.7.1.112) (P150) (C-ABL).
    graph->title = line.substr(line.find('=', 0) + 1, line.length());

    std::getline(fin, line); // LENGTH=1866
    graph->nodeCnt = std::stoi(
            line.substr(line.find('=', 0) + 1, line.length()));

    std::getline(fin, line); // SOURCECOUNT=4
    graph->seqCnt = std::stoi(line.substr(line.find('=', 0) + 1, line.length()));



    for (int seqId = 0; seqId < graph->seqCnt; ++seqId) {
        std::getline(fin, line); // SOURCENAME=CRKL_HUMAN
        std::string seqName = line.substr(line.find('=', 0) + 1, line.length());
        std::getline(fin, line); // SOURCEINFO=303 0 1 -1 CRK-LIKE PROTEIN.
        std::string params = line.substr(line.find('=', 0) + 1, line.length());

        std::stringstream os;
        os << line.substr(line.find('=', 0) + 1, line.length());
        int nodeCnt;
        os >> nodeCnt; // sequence node count: 303
        int firstNodeId;
        os >> firstNodeId; // id of first node: 0
        int weight;
        os >> weight; // weight: 1
        int none;
        os >> none; // bundle id: -1 by default
        std::string title;
        std::getline(os, title); // remaining is sequence title: CRK-LIKE PROTEIN.
        graph->seqs.push_back(new Seq(seqName, title, nodeCnt, weight));



    }
    for (int nodeId = 0; nodeId < graph->nodeCnt; ++nodeId) {

        std::stringstream os;
        std::getline(fin, line); // M:L85L151S2S3A153
        os << line;
        char nucl;
        os >> nucl; // Nucleotide or protein: M
        os.ignore(1); // ignore :

        std::vector<Node *> previousNodes; // L
        std::set<int> alignedWithNodeIds;// A
        std::set<Seq *> seqs; // S

        while (!os.eof()) {
            char option;
            if (!(os >> option)) {
                break;
            }
            int value;
            os >> value;
            switch(option){
                case 'L':
                    previousNodes.push_back(graph->nodes[value]);
                    break;
                case 'S':
                    seqs.insert(graph->seqs[value]);
                    break;
                case 'A':
                    alignedWithNodeIds.insert(value);
                    break;
            }
        }
        // stvori novi cvor

        Node *node = new Node(nodeId, nucl, seqs, alignedWithNodeIds);
        graph->nodes.push_back(node);

        for(Seq *seq : seqs){
            if (seq->startNode == nullptr){
                seq->startNode = node;
            }
        }

        // stvori veze prema svim prijasnjim cvorovima
        std::vector<Link *> *previousLinks = new std::vector<Link *>();

        for(Node *previousNode : previousNodes){
            previousLinks->push_back(new Link(previousNode, node));
        }
        node->previous = *previousLinks;
        if (node->previous.empty()){
            graph->starts.push_back(node);
        }else{
            for(Link *previousLink : *previousLinks){
                // dodaj link sa novim u sljedece od proslog nodea
                previousLink->previous->next.push_back(previousLink);
            }
        }

    }

    fin.close();
    return graph;

}
