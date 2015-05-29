//
// Created by ppx on 17.05.15..
//

#include "FastaOutputFormater.h"

void FastaOutputFormater::format(std::string file_path, Graph *poMsa) {
    std::ofstream outfile (file_path);
    for(Seq *cons : poMsa->cons){
        outfile << ">" << cons->name << "_" << cons->title << std::endl;
        std::list<Node *> nodes;
        cons->nodes(&nodes);
        for(Node *node: nodes){
            outfile << node->nucl;
        }
        outfile << std::endl;
    }
    outfile.close();
}
