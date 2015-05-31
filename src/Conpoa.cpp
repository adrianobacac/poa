//
// Created by ppx on 31.05.15..
//

#include "Conpoa.h"
#include "HeaviestBundle.h"


Conpoa::Conpoa(Graph *poMsa, SequenceBundler *bundler):poMsa(poMsa), bundler(bundler){
}


int Conpoa::generateConsesuses(int limit, int thread_cnt, OutputFormater *output){

    HeaviestBundle *hb = new HeaviestBundle(poMsa, thread_cnt);
    unsigned long unbunbled_seq_cnt = poMsa->seqs.size();
    while (unbunbled_seq_cnt && limit != 0){
        limit--;
        // pronadi najbolji put
        std::list<Node *> bestPath;
        bestPath = hb->findTopScoringPath();
        // gotovo nalazenje najboljeg puta

        // stvori novu sekvencu
        Seq *new_consensus = new Seq("consensus", "", (int) bestPath.size(), 0);
        poMsa->cons.push_back(new_consensus);
        poMsa->createSeqOnPath(new_consensus, bestPath);
        new_consensus->setStartNode(bestPath.front());
        // gotovo stvaranje nove sekvence

        // pronadi slicne sekvence
        std::vector<Seq *> bundle;
        int seqs_bundled = bundler->addSequencesToBundle(&poMsa->seqs, new_consensus, &bundle);
        unbunbled_seq_cnt -= seqs_bundled;
        new_consensus->title = std::to_string(seqs_bundled);
        if (seqs_bundled > 0){
            for (Seq *seq : bundle){
                seq->rescaleWeight(0);
            }
        }
        else{
            break;
        }
    }
    delete hb;
    output->format("out.fa", poMsa);
    return 0;
}

