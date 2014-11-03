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

Node::Node() : link(0), len_actual(0), len_within_document(0), docs_occurs_in(0), sorted_(true) {}

Node::~Node() {}

bool Node::HasEdgeThrough(char ch) {
  for (const auto& edge : edges_) {
    if  (edge.first == ch) {
      return true;
    }
  }
  return false;
}

size_t Node::NextNodeThrough(char ch) {
  for (const auto& edge : edges_) {
    if  (edge.first == ch) {
      return edge.second;
    }
  }	
  return 0;
}

vector<pair<char, size_t> >::iterator Node::begin() {
  if  (!sorted_) {
    sort(edges_.begin(), edges_.end());
    sorted_ = true;
  }
  return edges_.begin();
}

vector<pair<char, size_t> >::iterator Node::end() {
  if  (!sorted_) {
      sort(edges_.begin(), edges_.end());
      sorted_ = true;
    }
    return edges_.end();
}

bool Node::AddEdge(char ch, size_t to) {
  sorted_ = false;

  for (auto& edge : edges_) {
    if  (edge.first == ch) {
      edge.second = to;
      return false;
    }
  }

  edges_.push_back(make_pair(ch, to));
  return true;
}
