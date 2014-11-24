/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#include <cstdlib>
#include <algorithm>
#include <cstddef>

#include "node.hpp"

using std::pair;
using std::min;
using std::vector;
using std::make_pair;

Node::Node() : link(0), len_actual(0), len_within_document(0), docs_occurs_in(0), score_occurs_only(0.0), last_hash(0) {}

Node::~Node() {}

bool Node::HasEdgeThrough(char ch) const {
  for (const auto& edge : edges_) {
    if  (edge.first == ch) {
      return true;
    }
  }
  return false;
}

size_t Node::NextNodeThrough(char ch) const {
  for (const auto& edge : edges_) {
    if  (edge.first == ch) {
      return edge.second;
    }
  }
  return 0;
}

vector<pair<char, size_t> >::iterator Node::edges_begin() {
  return edges_.begin();
}

vector<pair<char, size_t> >::iterator Node::edges_end() {
  return edges_.end();
}

vector<pair<char, size_t> >::iterator Node::rev_edges_begin() {
  return rev_edges_.begin();
}

vector<pair<char, size_t> >::iterator Node::rev_edges_end() {
  return rev_edges_.end();
}

vector<size_t>::iterator Node::rev_links_begin() {
  return rev_links_.begin();
}

vector<size_t>::iterator Node::rev_links_end() {
  return rev_links_.end();
}

bool Node::AddEdge(char ch, size_t to) {
  for (auto& edge : edges_) {
    if  (edge.first == ch) {
      edge.second = to;
      return false;
    }
  }
  edges_.push_back(make_pair(ch, to));
  return true;
}

bool Node::AddRevEdge(char ch, size_t from) {
  for (auto& it : rev_edges_) {
    if  (it.second == from) {
      it.first = ch;
      return false;
    }
  }
  rev_edges_.push_back(make_pair(ch, from));
  return true;
}

bool Node::AddRevLink(size_t from_link) {
  for (auto from_link_ : rev_links_) {
    if  (from_link_ == from_link) {
      return false;
    }
  }
  rev_links_.push_back(from_link);
  return true;
}

void Node::SortEdges() {
  std::sort(edges_.begin(), edges_.end());
}

size_t Node::InDegree() {
  return rev_edges_.size();
}

size_t Node::OutDegree() {
  return edges_.size();
}

bool Node::DeleteEdge(size_t to) {
  size_t pos = edges_.size();
  for (size_t i = 0; i < edges_.size(); ++i) {
    if  (edges_[i].second == to) {
      pos = i;
      break;
    }
  }
  if  (pos < edges_.size()) {
    edges_.erase(edges_.begin() + pos);
    return true;
  }
  return false;
}

bool Node::DeleteRevEdge(size_t from) {
  size_t pos = rev_edges_.size();
  for (size_t i = 0; i < rev_edges_.size(); ++i) {
    if  (rev_edges_[i].second == from) {
      pos = i;
      break;
    }
  }
  if  (pos < rev_edges_.size()) {
    rev_edges_.erase(rev_edges_.begin() + pos);
    return true;
  }
  return false;
}

bool Node::DeleteRevLink(size_t from) {
  size_t pos = rev_links_.size();
  for (size_t i = 0; i < rev_links_.size(); ++i) {
    if  (rev_links_[i] == from) {
      pos = i;
      break;
    }
  }
  if  (pos < rev_links_.size()) {
    rev_links_.erase(rev_links_.begin() + pos);
    return true;
  }
  return false;
}

std::unique_ptr<ProtoNode> Node::GetProtoNode() const {
  auto proto_node = std::unique_ptr<ProtoNode>(new ProtoNode());
  auto *proto_repeated_ptrs_edges = proto_node->mutable_edges();
  proto_repeated_ptrs_edges->Reserve(edges_.size());
  for (const auto &edge : edges_) {
    auto *proto_edge = proto_repeated_ptrs_edges->Add();
    proto_edge->set_edge_char(edge.first);
    proto_edge->set_to_node_id(edge.second);
    assert(proto_edge->IsInitialized());
  }

  auto *proto_repeated_ptrs_rev_edges = proto_node->mutable_rev_edges();
  proto_repeated_ptrs_rev_edges->Reserve(rev_edges_.size());
  for (const auto &edge : rev_edges_) {
    auto *proto_edge = proto_repeated_ptrs_rev_edges->Add();
    proto_edge->set_edge_char(edge.first);
    proto_edge->set_to_node_id(edge.second);
    assert(proto_edge->IsInitialized());
  }

  auto *proto_repeated_rev_links = proto_node->mutable_rev_links();
  proto_repeated_rev_links->Reserve(rev_links_.size());
  for (const auto &rev_link : rev_links_) {
    proto_repeated_rev_links->AddAlreadyReserved(rev_link);
  }

  proto_node->set_link(link);
  proto_node->set_len_actual(len_actual);
  proto_node->set_len_within_document(len_within_document);
  proto_node->set_docs_occurs_in(docs_occurs_in);
  proto_node->set_score_occurs_only(score_occurs_only);
  proto_node->set_last_hash(last_hash);

  assert(proto_node->IsInitialized());
  return proto_node;
}

Node::Node(const ProtoNode& proto_node) : Node() {
  link = proto_node.link();
  len_actual = proto_node.len_actual();
  len_within_document = proto_node.len_within_document();
  docs_occurs_in = proto_node.docs_occurs_in();
  score_occurs_only = proto_node.score_occurs_only();
  last_hash = proto_node.last_hash();

  const auto& proto_repeated_ptrs_edges = proto_node.edges();
  edges_.reserve(proto_repeated_ptrs_edges.size());
  for (const auto& proto_edge : proto_repeated_ptrs_edges) {
    edges_.emplace_back(proto_edge.edge_char(), proto_edge.to_node_id());
  }
  const auto& proto_repeated_ptrs_rev_edges = proto_node.rev_edges();
  rev_edges_.reserve(proto_repeated_ptrs_rev_edges.size());
  for (const auto &proto_edge : proto_repeated_ptrs_rev_edges) {
    rev_edges_.emplace_back(proto_edge.edge_char(), proto_edge.to_node_id());
  }

  const auto& proto_repeated_rev_links = proto_node.rev_links();
  rev_links_.reserve(proto_repeated_rev_links.size());
  for (auto& rev_link : proto_repeated_rev_links) {
    rev_links_.emplace_back(rev_link);
  }
}
