//
// Created by ppx on 31.05.15..
//

#include "Conpoa.h"
#include "HeaviestBundle.h"


Conpoa::Conpoa(Graph *poMsa, SequenceBundler *bundler) : graph_(poMsa),
                                                         bundler_(bundler) {
}


int Conpoa::GenerateConsesuses(int limit,
                               OutputFormater *output) {

  HeaviestBundle *hb = new HeaviestBundle(graph_);
  int unbunbled_seq_cnt = graph_->seq_cnt();
  while (unbunbled_seq_cnt && limit != 0) {
    --limit;
    // pronadi najbolji put
    std::list<Node *> bestPath;
    bestPath = hb->FindTopScoringPath();
    // gotovo nalazenje najboljeg puta

    // stvori novu sekvencu
    Seq *new_consensus = new Seq("consensus", "", (int) bestPath.size(), 0);
    graph_->AddConsensus(new_consensus);
    graph_->CreateSeqOnPath(new_consensus, &bestPath);
    new_consensus->set_start_node(bestPath.front());
    // gotovo stvaranje nove sekvence

    // pronadi slicne sekvence
    std::vector<Seq *> bundle;
    int seqs_bundled = bundler_->AddSequencesToBundle(graph_->seqs(),
                                                      new_consensus, &bundle);
    unbunbled_seq_cnt -= seqs_bundled;
    new_consensus->set_title(std::to_string(seqs_bundled));
    if (seqs_bundled > 0) {
      for (Seq *seq : bundle) {
        seq->RescaleWeight(0);
      }
    }
    else {
      break;
    }
  }
  delete hb;
  output->Format("out.fa", graph_);
  return 0;
}

