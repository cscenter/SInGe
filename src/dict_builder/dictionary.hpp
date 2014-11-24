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
  // const in the past
  size_t kMaxDict;
  size_t kMinLen;
  size_t kMinDocsOccursIn;

  Dictionary();

  Dictionary(size_t kMaxDict
          , size_t kMinLen
          , char kStopSymbol
          , size_t kMaxAutomatonSize
          , double kAutomatonCoef);

  Dictionary(const SuffixAutomaton& automaton
          , size_t kMaxDict
          , size_t kMinLen);

  ~Dictionary();

  void AddDocument(std::string& doc);

  void AddDocument(const char* doc, size_t length);

  void AddDocumentViaStopSymbol(std::string& doc);

  void AddDocumentViaStopSymbol(const char* doc, size_t length);
    
  void BuildDict();

  std::vector<std::pair<std::string, size_t> > GetDictSubstringsList();

  std::string GetDict();

  void OutputDictTo(std::string path);

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
};

#endif // DICTIONARY_HPP_
