//
// Created by ppx on 13.05.15..
//

#include "InternalGapLength.h"
#include <cassert>

InternalGapLength::~InternalGapLength() {

}



InternalGapLength::InternalGapLength(int limit):_limit(limit), _gap_length(0), _temp_gap_length(0), _was_first_match(false) {
    assert(limit >= 0);
}


bool InternalGapLength::check(Seq *seq, Seq *cons) {
    assert(seq!= nullptr && cons != nullptr);
    std::list<Node *> nodes;

    seq->nodes(&nodes);
    int largest_gap = 0;
    int temp_cons_gap = 0;
    int temp_seq_gap = 0;
    Node *match = nullptr;
    for(Node *node: nodes){
        if (!node->hasSeq(cons) && !match){
            // preskoci sve dok nema nekog zajednickog
            continue;
        }

        if (!node->hasSeq(cons) && match){
            ++temp_seq_gap;
            continue;
        }

        if (node->hasSeq(cons)){
            match = node;
            if (temp_cons_gap > largest_gap || temp_seq_gap > largest_gap) {
                largest_gap = temp_cons_gap > temp_seq_gap ? temp_cons_gap : temp_seq_gap;
            }
            temp_seq_gap = 0;
            temp_cons_gap = 0;
        }

        if  (node->LinkTo(seq) != node->LinkTo(cons) && match){

            // u ovom cvoru se racvaju putevi
            // pronadi duljinu rupe u konsenzusu
            if (!node->LinkTo(cons)){

                continue;
            }
            Node *cons_node = node->LinkTo(cons)->next;
            while(cons_node && !cons_node->hasSeq(seq)){

                ++temp_cons_gap;
                if(cons_node->LinkTo(cons)) {
                    cons_node = cons_node->LinkTo(cons)->next;
                }else{
                    break;
                }
            }
        }


    }

    return largest_gap <= _limit;
}
