/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <cstdlib>
#include <cstddef> // size_t
#include <memory> //uinique_ptr
#include <automaton.pb.h>

class Node {
public:
  Node();

  ~Node();

  bool HasEdgeThrough(char ch) const;

  size_t NextNodeThrough(char ch) const;

  std::vector<std::pair<char, size_t> >::iterator edges_begin();

  std::vector<std::pair<char, size_t> >::iterator edges_end();

  std::vector<std::pair<char, size_t> >::iterator rev_edges_begin();

  std::vector<std::pair<char, size_t> >::iterator rev_edges_end();

  std::vector<size_t>::iterator rev_links_begin();

  std::vector<size_t>::iterator rev_links_end();

  bool AddEdge(char ch, size_t to);

  bool AddRevEdge(char ch, size_t from);

  bool AddRevLink(size_t from_link);

  void SortEdges();

  size_t InDegree();

  size_t OutDegree();

  bool DeleteEdge(size_t to);

  bool DeleteRevEdge(size_t from);

  bool DeleteRevLink(size_t from);

  std::unique_ptr<ProtoNode> GetProtoNode() const ;

  explicit Node(const ProtoNode & proto_node);

  size_t link;
  size_t len_actual;
  size_t len_within_document;
  size_t docs_occurs_in;
  double score_occurs_only;
  size_t last_hash;

private:
  std::vector<std::pair<char, size_t> > edges_;
  std::vector<std::pair<char, size_t> > rev_edges_;
  std::vector<size_t> rev_links_;

  friend class SerializationTest;
};

#endif // NODE_HPP_
