/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#ifndef SUFFIX_AUTOMATON_HPP_
#define SUFFIX_AUTOMATON_HPP_

#include <cstddef> //size_t
#include <string>
#include <vector>
#include <set>
#include <cmath>
<<<<<<< HEAD
#include <cassert>
=======
#include <memory> //unique_ptr
#include <automaton.pb.h>

>>>>>>> upstream/master
#include "node.hpp"

struct compare_nodes {
  bool operator() (const std::pair<std::pair<double, size_t>, size_t>& node1, const std::pair<std::pair<double, size_t>, size_t>& node2) {
    double occurs1 = node1.first.first;
    double occurs2 = node2.first.first;
    size_t len1 = node1.first.second;
    size_t len2 = node2.first.second;
    size_t id1 = node1.second;
    size_t id2 = node2.second;

    if  (fabs(occurs1 - occurs2) > 1e-9) {
      return occurs2 > occurs1;
    }

    if  (len1 != len2) {
      return len2 < len1; 
    }

<<<<<<< HEAD
    return id1 > id2;
=======
    return id1 < id2;
>>>>>>> upstream/master
  }
};

class SuffixAutomaton {
public:
<<<<<<< HEAD
  // const in the past
  size_t kMaxSize;
  char kStopSymbol;
  double kCoef;
=======
  static const size_t kMaxSize;
  static const char kStopSymbol;
  static const double kCoef;
>>>>>>> upstream/master

  class iterator;

  SuffixAutomaton();

<<<<<<< HEAD
  SuffixAutomaton(char kStopSymbol, size_t kMaxSize, double kCoef);

=======
>>>>>>> upstream/master
  ~SuffixAutomaton();

  iterator begin();

  iterator end();

  size_t AmountNodes() const;

  size_t AmountAliveNodes() const;

  inline size_t GetIdNode(Node* node) const {
    return node - nodes_pool_.data();
  }

  inline size_t GetIdNode(Node* node) {
    return node - nodes_pool_.data();
  }

  inline const Node* GetNode(size_t id) const {
<<<<<<< HEAD
    return id && !is_free_node_[id] && id < nodes_pool_.size() ? &nodes_pool_[id] : nullptr;
  }

  inline Node* GetNode(size_t id) {
    return id && !is_free_node_[id] && id < nodes_pool_.size() ? &nodes_pool_[id] : nullptr;
=======
    return id ? &nodes_pool_[id] : nullptr;
  }

  inline Node* GetNode(size_t id) {
    return id ? &nodes_pool_[id] : nullptr;
>>>>>>> upstream/master
  }

  double GetScore(size_t id);

  bool AddOccurence(size_t id);

  void AddString(const char* const str, size_t length);
    
  void AddStringViaStopSymbol(const char* const str, size_t length);

  size_t root() const;

  bool Empty() const;

<<<<<<< HEAD
=======
  void Output();

  void Output(size_t v, std::string s);

>>>>>>> upstream/master
  double GetCurrentCoef();

  std::string GetLongestString(size_t id);

  bool ReduceSize();

<<<<<<< HEAD
  std::vector<size_t> GetNodesInOrder();
=======
  std::unique_ptr<ProtoAutomaton> GetProtoAutomaton() const;

  explicit SuffixAutomaton(const ProtoAutomaton& proto_automaton);
>>>>>>> upstream/master

private:
  size_t NewNode();

  bool AddLink(size_t from, size_t to);

  bool AddEdge(size_t from, size_t to, char ch);

<<<<<<< HEAD
  bool DeleteEdge(size_t from, size_t to);

=======
>>>>>>> upstream/master
  bool DeleteNode(size_t id);

  void AddCharacter(char ch);

  void AddToNodesToDelete(size_t id);

  void EraseFromNodesToDelete(size_t id);

  std::vector<Node> nodes_pool_;
  std::vector<size_t> free_nodes_;
  std::vector<bool> is_free_node_;
  size_t last_node_;
  size_t len_up_to_stop_symbol_;
  size_t amount_alive_nodes_;
  double current_coef;
  std::set<std::pair<std::pair<double, size_t>, size_t>, compare_nodes> nodes_to_delete_;
<<<<<<< HEAD
};

=======

  friend class SerializationTest;
};



>>>>>>> upstream/master
class SuffixAutomaton::iterator {
public:
  iterator(size_t id, std::vector<bool>& is_free_node);

  iterator operator++();

  size_t& operator*();

  size_t* operator->();

  bool operator ==(const iterator& other);

  bool operator !=(const iterator& other);

private:
  size_t id_;
  std::vector<bool>& is_free_node_;
};

#endif // SUFFIX_AUTOMATON_HPP_

