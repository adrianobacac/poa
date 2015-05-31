/*
 * Node.h
 *
 *  Created on: Apr 2, 2015
 *      Author: ppx10
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <set>

#include "Link.h"
#include "Seq.h"

class Link;

class Seq;

class Node {

public:
  int index_;

  int times_visited_;

  std::vector<Link *> entry_links_;
  std::vector<Link *> exit_links_;

  std::set<int> aligned_with_node_ids_;


  std::set<Seq *> seqs_;

  char nucl_;
  Node *best_previous_;
  int score_;

  const std::set<Seq *> &seqs() const { return seqs_; }

  void set_seqs(const std::set<Seq *> &seqs) { Node::seqs_ = seqs; }

  Node *best_previous() const { return best_previous_; }

  void set_best_previous(Node *best_previous) { Node::best_previous_ = best_previous; }

  int score() const { return score_; }

  void set_score(int score) { Node::score_ = score; }

  int times_visited() const { return times_visited_; }

  void ClearVisited() { times_visited_ = 0; }

  void MarkVisited() { ++times_visited_; }

  char nucl() const { return nucl_; }


  const std::vector<Link *> &entry_links() const { return entry_links_; }

  void set_entry_links(
      const std::vector<Link *> &entry_links) { Node::entry_links_ = entry_links; }

  const std::vector<Link *> &exit_links() const { return exit_links_; }

  void set_exit_links(
      const std::vector<Link *> &exit_links) { Node::exit_links_ = exit_links; }


  Node(int index, char nucl, std::set<Seq *> seqs, std::set<int> aln_nodes_id2);

  virtual ~Node();

  /**
 * Adds Node to list of next nodes.
 * @param next Node to add.
 */
  void AddExitLink(Link *next);


  void AddSeq(Seq *seq);

  bool HasSeq(Seq *seq);

  /**
   * Follow best previous nodes to Create path.
   * @return Best path to this node.
   */
  std::list<Node *> Traceback();


  Link *LinkTo(Node *queryNode);

  Link *LinkTo(Seq *seq);

  std::string DotFormat();
};

#endif /* NODE_H_ */
