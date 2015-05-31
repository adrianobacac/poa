//
// Created by ppx on 29.05.15..
//

#include <fstream>
#include <sstream>
#include "PoGraphCreator.h"

Graph *PoGraphCreator::Create(std::string filePath) {
  std::ifstream fin;
  fin.open(filePath);

  Graph *graph = new Graph();

  if (!fin.good()) {
    throw "File " + std::string(filePath) + " can't be opened";
  }
  std::string line;

  std::getline(fin, line); // VERSION=LPO.0.1
  std::getline(fin, line); // NAME=ABL1_HUMAN
  std::getline(fin,
               line); // PROTO-ONCOGENE TYROSINE-PROTEIN KINASE ABL (EC 2.7.1.112) (P150) (C-ABL).

  std::getline(fin, line); // LENGTH=1866
  graph->set_node_cnt(std::stoi(
      line.substr(line.find('=', 0) + 1, line.length())));

  std::getline(fin, line); // SOURCECOUNT=4
  graph->set_seq_cnt(std::stoi(line.substr(line.find('=', 0) + 1, line.length())));


  for (int seq_id = 0; seq_id < graph->seq_cnt(); ++seq_id) {
    std::getline(fin, line); // SOURCENAME=CRKL_HUMAN
    std::string seqName = line.substr(line.find('=', 0) + 1, line.length());
    std::getline(fin, line); // SOURCEINFO=303 0 1 -1 CRK-LIKE PROTEIN.

    std::stringstream os;
    os << line.substr(line.find('=', 0) + 1, line.length());
    int nodeCnt;
    os >> nodeCnt; // sequence node count: 303
    int firstNodeId;
    os >> firstNodeId; // id of first node: 0
    int weight;
    os >> weight; // Weight: 1
    int none;
    os >> none; // bundle id: -1 by default
    std::string title;
    std::getline(os, title); // remaining is sequence title: CRK-LIKE PROTEIN.
    graph->AddSeq(new Seq(seqName, title, nodeCnt, weight));


  }
  for (int node_id = 0; node_id < graph->node_cnt(); ++node_id) {

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
      switch (option) {
        case 'L':
          previousNodes.push_back(graph->nodes()[value]);
          break;
        case 'S':
          seqs.insert(graph->seqs()[value]);
          break;
        case 'A':
          alignedWithNodeIds.insert(value);
          break;
        default:
          delete graph;
          throw "File Format error";
      }
    }
    // stvori novi cvor

    Node *node = new Node(node_id, nucl, seqs, alignedWithNodeIds);
    graph->AddNode(node);

    for (Seq *seq : seqs) {
      if (!seq->HasStartNode()) {
        seq->set_start_node(node);
      }
    }

    // stvori veze prema svim prijasnjim cvorovima
    std::vector<Link *> *entry_links = new std::vector<Link *>();

    for (Node *previousNode : previousNodes) {
      entry_links->push_back(new Link(previousNode, node));
    }
    node->set_entry_links(*entry_links);
    if (entry_links->empty()) {
      graph->AddStart(node);
    } else {
      for (Link *entry_link : *entry_links) {
        // dodaj link sa novim u sljedece od proslog nodea
        entry_link->previous_node()->AddExitLink(entry_link);
      }
    }

  }

  fin.close();
  return graph;

}
