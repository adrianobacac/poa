//
// Created by Adriano Bacac on 17.05.15.
//
// Creates fasta output containing all consensuses in graph.
//
// Example of usage:
// FastaOutputFormater formater()
// formater.Format(
//            "out.fa",   // name of output file
//            graph       // graph whose consensuses will be saved
// )
//

#ifndef POA_FASTAOUTPUTFORMATER_H
#define POA_FASTAOUTPUTFORMATER_H


#include "OutputFormater.h"

class FastaOutputFormater : public OutputFormater {

  //
  // Takes which graph to format and where to save output.
  // Generates fasta file from all consensuses in graph.
  //
  void Format(std::string file_path, Graph *graph);
};


#endif //POA_FASTAOUTPUTFORMATER_H
