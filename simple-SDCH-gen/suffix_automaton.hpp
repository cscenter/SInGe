#ifndef SUFFIX_AUTOMATON_HPP_
#define SUFFIX_AUTOMATON_HPP_

#include <cstddef> //size_t
#include <string>
#include <vector>

#include "node.hpp"

class SuffixAutomaton {
public:
  static const char kStopSymbol;

  SuffixAutomaton();

  ~SuffixAutomaton();

  size_t AmountNodes() const;

  inline const size_t GetIdNode(Node* node) const {
    return node - nodes_pool_.data();
  }

  inline size_t GetIdNode(Node* node) {
    return node - nodes_pool_.data();
  }

  inline const Node* GetNode(size_t id) const {
    return id ? &nodes_pool_[id] : nullptr;
  }

  inline Node* GetNode(size_t id) {
    return id ? &nodes_pool_[id] : nullptr;
  }

  void AddString(const char* const str, size_t length);
    
  void AddStringViaStopSymbol(const char* const str, size_t length);

  size_t root() const;

  bool Empty() const;

  void Output();

  void Output(size_t v, std::string s);

private:
  size_t NewNode();

  size_t NewNode(size_t from);

  void ReserveFor(size_t length);

  void AddCharacter(char ch);

  std::vector<Node> nodes_pool_;
  size_t last_node_;
  size_t len_up_to_stop_symbol_;
};

#endif // SUFFIX_AUTOMATON_HPP_

