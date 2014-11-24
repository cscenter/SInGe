#include <map>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cassert>

#include "dictionary.hpp"
#include "suffix_automaton.hpp"

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::cerr;
using std::endl;
using std::cout;
using std::queue;
using std::map;

namespace {
  const double kEps = 1e-10;

  inline bool DoubleEquals(double first, double second) {
    return fabs(first - second) < kEps;
  }

  inline bool DoubleLess(double first, double second) {
    return first < second && !DoubleEquals(first, second);
  }
};

Dictionary::Dictionary()
    : kMaxDict(1 << 20)
    , kMinLen(20)
    , kMinDocsOccursIn(2) {}

Dictionary::Dictionary(size_t kMaxDict
      , size_t kMinLen
      , char kStopSymbol
      , size_t kMaxAutomatonSize
      , double kAutomatonCoef) 
    : kMaxDict(kMaxDict)
    , kMinLen(kMinLen)
    , kMinDocsOccursIn(2)
    , automaton_all_(SuffixAutomaton(kStopSymbol, kMaxAutomatonSize, kAutomatonCoef)) {
}

Dictionary::Dictionary(const SuffixAutomaton& automaton
      , size_t kMaxDict
      , size_t kMinLen) 
    : kMaxDict(kMaxDict)
    , kMinLen(kMinLen)
    , kMinDocsOccursIn(2)
    , automaton_all_(automaton) {
}

Dictionary::~Dictionary() {}

void Dictionary::AddDocument(string& doc) {
  last_document_ += doc;
  automaton_all_.AddString(doc.data(), doc.size());
}

void Dictionary::AddDocument(const char* doc, size_t length) {
  last_document_ += string(doc, length);
  automaton_all_.AddString(doc, length);
}

void Dictionary::AddDocumentViaStopSymbol(string& doc) {
  if  (automaton_all_.Empty()) {
    AddDocument(doc);
    return;
  }

  ResetLastDocument();

  last_document_ += doc;
  automaton_all_.AddStringViaStopSymbol(doc.data(), doc.size());
}

void Dictionary::AddDocumentViaStopSymbol(const char* doc, size_t length) {
  if  (automaton_all_.Empty()) {
    AddDocument(doc, length);
    return;
  }

  ResetLastDocument();

  last_document_ += string(doc, length);
  automaton_all_.AddStringViaStopSymbol(doc, length);
}

void Dictionary::BuildDict() {
  if  (automaton_all_.Empty()) {
    return;
  }

  ResetLastDocument();
  dict_.clear();

  cout << "automaton size = " << automaton_all_.AmountAliveNodes() << endl;
/*
  for (size_t id : automaton_all_) {
    cout << "occurs " << GetNode(id)->docs_occurs_in << " " << GetNode(id)->len_within_document << endl;
  }
*/
  cout << "building dictionary..." << endl;

  vector<size_t> substrings;
  CollectGoodSubstrings(&substrings);

  sort(substrings.begin(), substrings.end(), [&] (int id1, int id2) { return DoubleLess(automaton_all_.GetScore(id2), automaton_all_.GetScore(id1)); });

  cout << "good substrings have been collected and sorted" << endl;

  size_t length_dict = 0;
  for (size_t i = 0; i < substrings.size() && length_dict + kMinLen <= kMaxDict; ++i) {
    auto* node = GetNode(substrings[i]);
    if  (length_dict + node->len_within_document > kMaxDict) {
      continue;
    }
    length_dict += node->len_within_document;
    dict_.push_back(substrings[i]);
  }

  cout << "dict's length = " << length_dict << endl;
}

vector<pair<string, size_t> > Dictionary::GetDictSubstringsList() {
  vector<pair<string, size_t> > substrings;
  substrings.reserve(dict_.size());
  for (int id : dict_) {
    Node* node = GetNode(id);
    string str = automaton_all_.GetLongestString(id);
    substrings.push_back(make_pair(str, node->docs_occurs_in));
  }
  return substrings;
}

string Dictionary::GetDict() {
  string dict_str;
  for (size_t id : dict_) {
    dict_str += automaton_all_.GetLongestString(id);
  }
  return dict_str;
}

void Dictionary::OutputDictTo(string path) {
  std::ofstream file(path);
  file << GetDict();
}

void Dictionary::ResetLastDocument() {
  if  (last_document_.empty()) {
    return;
  }

  cout << "calculate occurences for document with length " << last_document_.size() << endl;
  size_t cur_hash = (rand() << 16) ^ rand();
  size_t id = automaton_all_.root();
  size_t pos = 0;
  while (pos < last_document_.size()) {
    id = GetNode(id)->NextNodeThrough(last_document_[pos]);
    ++pos;

    size_t cur_id = id;
    while (cur_id && GetNode(cur_id)->last_hash != cur_hash) {
      GetNode(cur_id)->last_hash = cur_hash;
      automaton_all_.AddOccurence(cur_id);
      cur_id = GetNode(cur_id)->link;
    }
    }

  last_document_.clear();
  automaton_all_.ReduceSize();
}

void Dictionary::CollectGoodSubstrings(vector <size_t>* substrings) {
  size_t nodes = automaton_all_.AmountNodes();
  vector<double> max_score_substring(nodes, -1e20);
  vector<double> max_score_upstring(nodes, -1e20);
  vector<char> can_to_dict(nodes, true);
  vector<size_t> order = automaton_all_.GetNodesInOrder();

  // calc max_score_substring
  for (size_t id : order) {
    double max_score = -1e20;
    if  (GetNode(id)->link) {
      double score = max_score_substring[GetNode(id)->link];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    for (auto it = GetNode(id)->rev_edges_begin(); it != GetNode(id)->rev_edges_end(); ++it) {
      size_t from = it->second;
      double score = max_score_substring[from];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    if  (CanAffordSubstringFrom(GetNode(id))) {
      double our_score = automaton_all_.GetScore(id);
      if  (DoubleLess(our_score, max_score)) {
        can_to_dict[id] = false;
      } else {
        max_score = our_score;
      }
    } else {
      can_to_dict[id] = false;
    }

    max_score_substring[id] = max_score;
  }

  // calc max_score_upstring
  reverse(order.begin(), order.end());
  for (size_t id : order) {
    double max_score = -1e20;
    for (auto it = GetNode(id)->edges_begin(); it != GetNode(id)->edges_end(); ++it) {
      size_t to = it->second;
      double score = max_score_upstring[to];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    for (auto it = GetNode(id)->rev_links_begin(); it != GetNode(id)->rev_links_end(); ++it) {
      size_t to = *it;
      double score = max_score_upstring[to];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    if  (CanAffordSubstringFrom(GetNode(id))) {
      double our_score = automaton_all_.GetScore(id);
      if  (!DoubleLess(max_score, our_score)) {
        can_to_dict[id] = false;
      } else {
        max_score = our_score;
      }
    } else {
      can_to_dict[id] = false;
    }

    max_score_upstring[id] = max_score;
  }

  // result
  for (size_t id : order) {
    if  (can_to_dict[id]) {
      substrings->push_back(id);
    }
  }
}

bool Dictionary::CanAffordSubstringFrom(Node* node) const {
  return node->len_within_document >= kMinLen && node->docs_occurs_in >= kMinDocsOccursIn;
}
