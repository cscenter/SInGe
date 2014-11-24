/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#include <algorithm>
#include <cstdio>
#include <string>
#include <queue>
#include <iostream>
#include <cassert>

#include "suffix_automaton.hpp"

using std::vector;
using std::min;
using std::max;
using std::string;
using std::make_pair;

SuffixAutomaton::SuffixAutomaton()
    : kMaxSize(1 << 18)
    , kStopSymbol('#')
    , kCoef(0.9)
    , len_up_to_stop_symbol_(1)
    , amount_alive_nodes_(0)
    , current_coef(1.0) {
  NewNode(); // ~ nullptr
  last_node_ = NewNode();
  AddToNodesToDelete(last_node_);
}

SuffixAutomaton::SuffixAutomaton(char kStopSymbol, size_t kMaxSize, double kCoef)
    : kStopSymbol(kStopSymbol)
    , kMaxSize(kMaxSize)
    , kCoef(kCoef)
    , len_up_to_stop_symbol_(1)
    , amount_alive_nodes_(0)
    , current_coef(1.0) {
  NewNode(); // ~ nullptr
  last_node_ = NewNode();
  AddToNodesToDelete(last_node_);
}

SuffixAutomaton::~SuffixAutomaton() {}

SuffixAutomaton::iterator SuffixAutomaton::begin() {
  return SuffixAutomaton::iterator(1, is_free_node_);
}

SuffixAutomaton::iterator SuffixAutomaton::end() {
  return SuffixAutomaton::iterator(AmountNodes(), is_free_node_);
}

size_t SuffixAutomaton::AmountNodes() const {
  return nodes_pool_.size();
}

size_t SuffixAutomaton::AmountAliveNodes() const {
  return amount_alive_nodes_;
}

double SuffixAutomaton::GetScore(size_t id) {
  if  (!GetNode(id)) {
    return -1e20;
  }
  size_t len = GetNode(id)->len_within_document;
  if  (len <= 3) {
    return 0.0;
  } else {
    return ((double) (len - 3) / len) * GetNode(id)->score_occurs_only * current_coef;
  }
}

bool SuffixAutomaton::AddOccurence(size_t id) {
  if  (!GetNode(id)) {
    return false;
  }
  if  (GetNode(id)->OutDegree() == 0) {
    EraseFromNodesToDelete(id);
  }
  ++GetNode(id)->docs_occurs_in;
  GetNode(id)->score_occurs_only += 1.0 / current_coef;
  if  (GetNode(id)->OutDegree() == 0) {
    AddToNodesToDelete(id);
  }

  return true;
}

void SuffixAutomaton::AddString(const char* const str, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    AddCharacter(str[i]);
    ++len_up_to_stop_symbol_;
  }
}

void SuffixAutomaton::AddStringViaStopSymbol(const char* const str, size_t length) {
  current_coef *= kCoef;

  len_up_to_stop_symbol_ = 0;
  AddCharacter(kStopSymbol);
  ++len_up_to_stop_symbol_;

  for (size_t i = 0; i < length; ++i) {
    AddCharacter(str[i]);
    ++len_up_to_stop_symbol_;
  }
}

size_t SuffixAutomaton::root() const {
  return 1;
}

bool SuffixAutomaton::Empty() const {
  return last_node_ == root();
}

double SuffixAutomaton::GetCurrentCoef() {
  return current_coef;
}

string SuffixAutomaton::GetLongestString(size_t id) {
  string str;
  while (GetNode(id)->len_within_document > 0) {
    size_t max_len = 0;
    size_t max_id = 0;
    char max_ch = 0;
    for (auto it = GetNode(id)->rev_edges_begin(); it != GetNode(id)->rev_edges_end(); ++it) {
      size_t cur_id = it->second;
      char cur_ch = it->first;
      size_t cur_len = GetNode(cur_id)->len_within_document;
      if  (cur_len >= max_len) {
        max_len = cur_len;
        max_id = cur_id;
        max_ch = cur_ch;
      }
    }
    str += max_ch;
    id = max_id;
  }
  reverse(str.begin(), str.end());
  return str;
}

bool SuffixAutomaton::ReduceSize() {
  if  (AmountAliveNodes() > 2 * kMaxSize) {
    while (AmountAliveNodes() > kMaxSize) {
      auto min_node = *nodes_to_delete_.begin();
      DeleteNode(min_node.second);
    }
    return true;
  }
  return false;
}

vector<size_t> SuffixAutomaton::GetNodesInOrder() {
  std::queue<size_t> q_nodes;
  vector<char> was_in_q(AmountNodes(), false);
  vector<size_t> order;

  q_nodes.push(root());
  was_in_q[root()] = true;
  while (!q_nodes.empty()) {
    size_t id = q_nodes.front();
    q_nodes.pop();
    order.push_back(id);

    for (auto it = GetNode(id)->edges_begin(); it != GetNode(id)->edges_end(); ++it) {
      size_t to = it->second;
      if  (!was_in_q[to]) {
        was_in_q[to] = true;
        q_nodes.push(to);
      }
    }
  }

  return order;
}

size_t SuffixAutomaton::NewNode() {
  if  (nodes_pool_.empty()) {
    is_free_node_.push_back(false);
    nodes_pool_.push_back(Node());
    return 0;
  }

  ++amount_alive_nodes_;
  size_t id = 0;
  if  (free_nodes_.empty()) {
    nodes_pool_.push_back(Node());
    is_free_node_.push_back(false);
    id = nodes_pool_.size() - 1;
  } else {
    id = free_nodes_.back();
    free_nodes_.pop_back();
    is_free_node_[id] = false;
    nodes_pool_[id] = Node();
  }
  return id;
}

bool SuffixAutomaton::AddLink(size_t from, size_t to) {
  if  (!GetNode(from) || !GetNode(to)) {
    return false;
  }
  size_t old_to = GetNode(from)->link;
  if  (GetNode(old_to)) {
    GetNode(old_to)->DeleteRevLink(from);
  }
  GetNode(from)->link = to;
  GetNode(to)->AddRevLink(from);
  return true;
}

bool SuffixAutomaton::AddEdge(size_t from, size_t to, char ch) {
  GetNode(from)->AddEdge(ch, to);
  GetNode(to)->AddRevEdge(ch, from);
  if  (GetNode(from)->OutDegree() == 1) {
    EraseFromNodesToDelete(from);
  }
  return true;
}

bool SuffixAutomaton::DeleteEdge(size_t from, size_t to) {
  GetNode(from)->DeleteEdge(to);
  GetNode(to)->DeleteRevEdge(from);
  if  (GetNode(from)->OutDegree() == 0) {
    AddToNodesToDelete(from);
  }
  return true;
}

bool SuffixAutomaton::DeleteNode(size_t id) {
  if  (id == last_node_) {
    size_t new_last_node_ = 0;
    for (auto it = GetNode(id)->rev_edges_begin(); it != GetNode(id)->rev_edges_end(); ++it) {
      if  (!new_last_node_ || GetNode(it->second)->len_actual > GetNode(new_last_node_)->len_actual) {
        new_last_node_ = it->second;
      }
    }
    last_node_ = new_last_node_;
  }

  // redirect incoming links
  for (auto it = GetNode(id)->rev_links_begin(); it != GetNode(id)->rev_links_end(); ++it) {
    size_t from = *it;
    GetNode(from)->link = GetNode(id)->link;
    GetNode(GetNode(id)->link)->AddRevLink(from);
  }

  // delete incoming edges
  for (auto it = GetNode(id)->rev_edges_begin(); it != GetNode(id)->rev_edges_end(); ++it) {
    GetNode(it->second)->DeleteEdge(id);
    if  (GetNode(it->second)->OutDegree() == 0) {
      AddToNodesToDelete(it->second);
    }
  }

  // delete outcoming links (actually, exactly one link)
  GetNode(GetNode(id)->link)->DeleteRevLink(id);

  vector<size_t> to_delete;
  // delete outgoing edges
  for (auto it = GetNode(id)->edges_begin(); it != GetNode(id)->edges_end(); ++it) {
    size_t to = it->second;
    GetNode(to)->DeleteRevEdge(id);
    if  (GetNode(to)->InDegree() == 0) {
      to_delete.push_back(to);
    }
  }

  EraseFromNodesToDelete(id);
  --amount_alive_nodes_;
  is_free_node_[id] = true;
  free_nodes_.push_back(id);

  for (size_t to : to_delete) {
    DeleteNode(to);
  }
  return true;
}

void SuffixAutomaton::AddCharacter(char ch) {
  size_t current_len = GetNode(last_node_)->len_actual + 1;

  size_t new_node = NewNode();
  GetNode(new_node)->len_actual = current_len;
  GetNode(new_node)->len_within_document = min(current_len, len_up_to_stop_symbol_);
  AddToNodesToDelete(new_node);

  size_t prev = last_node_;
  last_node_ = new_node;
  for (; prev && !GetNode(prev)->HasEdgeThrough(ch); prev = GetNode(prev)->link) {
    AddEdge(prev, new_node, ch);
  }

  if  (!prev) {
    AddLink(new_node, root());
    return;
  }

  size_t next = GetNode(prev)->NextNodeThrough(ch);
  if  (GetNode(next)->len_actual == GetNode(prev)->len_actual + 1) {
    AddLink(new_node, next);
    return;
  }

  size_t middle = NewNode();
  GetNode(middle)->len_actual = GetNode(prev)->len_actual + 1;
  GetNode(middle)->len_within_document = min(GetNode(prev)->len_actual + 1, len_up_to_stop_symbol_);
  GetNode(middle)->score_occurs_only = GetNode(next)->score_occurs_only;
  GetNode(middle)->docs_occurs_in = GetNode(next)->docs_occurs_in;
  AddLink(middle, GetNode(next)->link);
  AddToNodesToDelete(middle);
  for (auto it = GetNode(next)->edges_begin(); it != GetNode(next)->edges_end(); ++it) {
    AddEdge(middle, it->second, it->first);
  }

  for (; prev && GetNode(prev)->NextNodeThrough(ch) == next; prev = GetNode(prev)->link) {
    DeleteEdge(prev, next);
    AddEdge(prev, middle, ch);
  }
  AddLink(new_node, middle);
  AddLink(next, middle);
}

void SuffixAutomaton::AddToNodesToDelete(size_t id) {
  assert(GetNode(id)->OutDegree() == 0);
  nodes_to_delete_.insert(make_pair(make_pair(GetNode(id)->score_occurs_only, GetNode(id)->len_within_document), id));
}

void SuffixAutomaton::EraseFromNodesToDelete(size_t id) {
  nodes_to_delete_.erase(make_pair(make_pair(GetNode(id)->score_occurs_only, GetNode(id)->len_within_document), id));
}

SuffixAutomaton::iterator::iterator(size_t id, vector<bool>& is_free_node) : id_(id), is_free_node_(is_free_node) {}

SuffixAutomaton::iterator SuffixAutomaton::iterator::operator++() {
  iterator prev = *this;
  ++id_;
  while (id_ < is_free_node_.size() && is_free_node_[id_]) ++id_;
  return prev;
}

size_t& SuffixAutomaton::iterator::operator*() {
  return id_;
}

size_t* SuffixAutomaton::iterator::operator->() {
  return &id_;
}

bool SuffixAutomaton::iterator::operator ==(const iterator& other) {
  return id_ == other.id_;
}

bool SuffixAutomaton::iterator::operator !=(const iterator& other) {
  return id_ != other.id_;
}

std::unique_ptr<ProtoAutomaton> SuffixAutomaton::GetProtoAutomaton() const {
  assert(is_free_node_.size() == nodes_pool_.size());
  auto proto_automaton = std::unique_ptr<ProtoAutomaton>(new ProtoAutomaton());  
  proto_automaton->set_last_node(last_node_);
  proto_automaton->set_len_up_to_stop_symbol(len_up_to_stop_symbol_);
  proto_automaton->set_current_coef(current_coef);
  auto* proto_nodes_pool = proto_automaton->mutable_nodes_pool();
  proto_nodes_pool->Reserve(nodes_pool_.size());
  for (auto& node : nodes_pool_) {
    //ownership transfer
    proto_nodes_pool->AddAllocated(node.GetProtoNode().release());
  }
  assert(proto_nodes_pool->size() == (int) nodes_pool_.size());
  auto* proto_is_free_node = proto_automaton->mutable_is_free_node();
  proto_is_free_node->Reserve(is_free_node_.size());
  for (bool is_free : is_free_node_) {
    proto_is_free_node->AddAlreadyReserved(is_free);
  }
  assert(proto_automaton->IsInitialized());
  return proto_automaton;
}

SuffixAutomaton::SuffixAutomaton(const ProtoAutomaton& proto_automaton) {
  last_node_ = proto_automaton.last_node();
  len_up_to_stop_symbol_ = proto_automaton.len_up_to_stop_symbol();
  current_coef = proto_automaton.current_coef();
  const auto& proto_is_free_node = proto_automaton.is_free_node();
  is_free_node_.resize(proto_is_free_node.size());
  const auto& proto_nodes_pool = proto_automaton.nodes_pool();
  nodes_pool_.reserve(proto_nodes_pool.size());
  assert(proto_is_free_node.size() == proto_nodes_pool.size());
  nodes_pool_.emplace_back(proto_nodes_pool.Get(0)); // zero node
  for (size_t i_node = 1; i_node < is_free_node_.size(); ++i_node) {
    const auto& proto_node = proto_nodes_pool.Get(i_node);
    nodes_pool_.emplace_back(proto_node);
    const Node& current_node = nodes_pool_.back();
    if (proto_is_free_node.Get(i_node)) {
      is_free_node_[i_node] = true;
      free_nodes_.push_back(i_node);
    } else {
      nodes_to_delete_.insert(
          make_pair(
              make_pair(
                  current_node.score_occurs_only,
                  current_node.len_within_document
              ),
              i_node
          )
      );
    }
    amount_alive_nodes_ = nodes_to_delete_.size();
    // 1 is for zero node
    assert(amount_alive_nodes_ + free_nodes_.size() + 1 == nodes_pool_.size());
  }
}
