/*
 * HeaviestBundle.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#include "HeaviestBundle.h"

void HeaviestBundle::ProcessBranch(Node *start) {

  Node *local_max_scorer = start;
  Node *current = start;

  while (true) {
    auto entry_link_cnt = current->entry_links().size();
    if (entry_link_cnt > 1) {
      current->MarkVisited();
      if (current->times_visited() != entry_link_cnt) {
        break;
      }
    }
    // reset for next round
    current->ClearVisited();
    if (entry_link_cnt > 0) {

      // trazimo najbolji prijasnji
      int maxWeight = -1; // sigurno nece bit
      int max_previous_score = 0; // gledamo ako imaju istu tezinu rubova
      Node *best_previous_scorer = nullptr;
      for (Link *link : current->entry_links()) {
        int weight = link->Weight();
        Node *previous_node = link->previous_node();
        if (weight > maxWeight
            || (weight == maxWeight
                && previous_node->score() > max_previous_score)) {
          maxWeight = weight;
          best_previous_scorer = previous_node;
          max_previous_score = previous_node->score();
        }
      }

      current->set_best_previous(best_previous_scorer);
      current->set_score(best_previous_scorer->score() + maxWeight);

      if (current->score() > local_max_scorer->score()) {
        local_max_scorer = current;
      }
    }
    auto exit_links = current->exit_links();
    if (exit_links.size() > 1) {
      for (unsigned int i = 1; i < exit_links.size(); ++i) {
        to_process_.push(exit_links[i]->next_node());
      }
    }
    if (exit_links.empty()) {
      ends_.push_back(current);
      break;
    }
    current = exit_links[0]->next_node();

  }
  if (top_scoring_node_ == nullptr) {
    top_scoring_node_ = local_max_scorer;
  } else if (local_max_scorer->score() > top_scoring_node_->score()) {
    top_scoring_node_ = local_max_scorer;
  }
}

Node *HeaviestBundle::BranchCompletion(Node *topScoringNode) {
  if (!topScoringNode->exit_links().empty()) {
    Node *best = ends_[0];
    for (Node *ending : ends_) {
      if (ending->score() > best->score()) {
        best = ending;
      }
    }
    top_scoring_node_ = best;
  }
  return top_scoring_node_;
}

HeaviestBundle::HeaviestBundle(Graph *poMsa) :
    graph_(poMsa),
    top_scoring_node_(nullptr),
    to_process_(std::queue<Node *>()) {
}

std::list<Node *> HeaviestBundle::FindTopScoringPath() {
  for (Node *start : graph_->starts()) {
    this->to_process_.push(start);
  }
  while (!to_process_.empty()) {
    Node *localStart = to_process_.front();
    to_process_.pop();
    ProcessBranch(localStart);
  }
  return BranchCompletion(top_scoring_node_)->Traceback();
}
