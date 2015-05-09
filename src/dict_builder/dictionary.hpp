#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include <cstddef> // size_t
#include <vector>
#include <string>
#include <cstdlib>

#include "node.hpp"
#include "suffix_automaton.hpp"

class Dictionary {
public:
  // were const in the past
  size_t kMaxDict;
  size_t kMinLen;
  size_t kMinDocsOccursIn;

  Dictionary();

  Dictionary(size_t kMaxDict, size_t kMinLen, char kStopSymbol, size_t kMaxAutomatonSize, double kAutomatonCoef, bool consider_as_one_string);

  Dictionary(size_t kMaxDict, size_t kMinLen, SuffixAutomaton& automaton, bool consider_as_one_string);

  ~Dictionary();

  void AddDocument(std::string& doc);

  void AddDocument(const char* doc, size_t length);

  void AddDocumentViaStopSymbol(std::string& doc);

  void AddDocumentViaStopSymbol(const char* doc, size_t length);
    
  void BuildDict();

  std::vector<std::pair<std::string, size_t> > GetDictSubstringsList();

  std::string GetDict();

  SuffixAutomaton& GetAutomaton();

  void OutputDictTo(std::string path);

  // last document was added to automaton, here we are to update occurrences corresponds to substring of the last_document
  void ResetLastDocument();

private:
  void CollectGoodSubstrings(std::vector<size_t>* substrings);

  bool CanAffordSubstringFrom(Node* node) const;

  inline const Node* GetNode(size_t id) const {
    return automaton_all_.GetNode(id);
  }

  inline Node* GetNode(size_t id) {
    return automaton_all_.GetNode(id);
  }

  inline size_t GetIdNode(Node* node) const {
    return automaton_all_.GetIdNode(node);
  }

  inline size_t GetIdNode(Node* node) {
    return automaton_all_.GetIdNode(node);
  }

  std::string last_document_;
  SuffixAutomaton automaton_all_;
  std::vector<int> dict_;
  bool consider_as_one_string_;
};

#endif // DICTIONARY_HPP_
