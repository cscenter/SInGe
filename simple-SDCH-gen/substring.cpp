#include "substring.hpp"
#include "suffix_automaton.hpp"

Substring::Substring(SuffixAutomaton& automaton, size_t id_node) : id_node_(id_node) {
  Node* node = automaton.GetNode(id_node);
  score_ = node->docs_occurs_in * (double) (node->len_within_document - 3) / node->len_within_document;
}

double Substring::score() {
  return score_;
}

size_t Substring::id_node() const {
  return id_node_;
}

