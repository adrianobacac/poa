//
// Created by ppx on 17.05.15..
//

#include <fstream>
#include "FastaOutputFormater.h"

void FastaOutputFormater::Format(std::string file_path, Graph *poMsa) {
  std::ofstream outfile(file_path);
  for (Seq *cons : poMsa->consensuses()) {
    outfile << ">" << cons->name() << "_" << cons->title() << std::endl;
    std::list<Node *> nodes;
    cons->GetNodes(&nodes);
    for (Node *node: nodes) {
      outfile << node->nucl();
    }
    outfile << std::endl;
  }
  outfile.close();
}
