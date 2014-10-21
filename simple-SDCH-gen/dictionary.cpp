/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#include <map>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>

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

namespace {
  const double kEps = 1e-10;

  inline bool DoubleEquals(double first, double second) {
    return fabs(first - second) < kEps;
  }

  inline bool DoubleLess(double first, double second) {
    return first < second && !DoubleEquals(first, second);
  }
};

bool operator <(Substring substring1, Substring substring2) {
  return DoubleLess(substring2.score(), substring1.score());
}


const size_t Dictionary::kMaxDict = 1 << 16;
const size_t Dictionary::kMinLen = 3;
const size_t Dictionary::kMinDocsOccursIn = 2;

Dictionary::Dictionary() {}

Dictionary::~Dictionary() {}

void Dictionary::AddDocument(string& doc) {
  if (lengths_docs_.empty()) {
    starts_docs_.push_back(0);
    lengths_docs_.push_back(doc.size());
  }
  else {
    lengths_docs_.back() += doc.size();
  }
  automaton_all_.AddString(doc.data(), doc.size());
  all_docs_ += doc;
}

void Dictionary::AddDocumentViaStopSymbol(string& doc) {
  if (automaton_all_.Empty()) {
    AddDocument(doc);
    return;
  }

  all_docs_ += SuffixAutomaton::kStopSymbol;
  starts_docs_.push_back(all_docs_.size());
  lengths_docs_.push_back(doc.size());
  automaton_all_.AddStringViaStopSymbol(doc.data(), doc.size());
  all_docs_ += doc;
}

void Dictionary::BuildDict() {
  cout << "building dictionary..." << endl;
  cout << "sum of the doc's length = " << all_docs_.size() << endl;
  //	cout << all_docs_ << endl;

  for (size_t i = 0; i < starts_docs_.size(); ++i) {
    SuffixAutomaton automaton_cur;
    automaton_cur.AddString(all_docs_.data() + starts_docs_[i], lengths_docs_[i]);
    UpdateOccurences(automaton_cur);
  }

  cout << "frequences have been calculated" << endl;

  vector<Substring> substrings;
  CollectGoodSubstrings(&substrings);

  sort(substrings.begin(), substrings.end());

  cout << "good substrings have been collected and sorted" << endl;

  size_t length_dict = 0;
  for (size_t i = 0; i < substrings.size() && length_dict + kMinLen <= kMaxDict; ++i) {
    auto* node = GetNode(substrings[i].id_node());
    if (length_dict + node->len_within_document > kMaxDict) {
      continue;
    }
    //		printf("cnt = %d, len = %d\n", node->docs_occurs_in, node->len_within_document);
    length_dict += node->len_within_document;
    dict_.push_back(substrings[i]);
  }

  cout << "dict's length = " << length_dict << ", " << (100 * length_dict / all_docs_.size()) << "\% of all documents" << endl;
}

void Dictionary::UpdateOccurences(SuffixAutomaton& automaton) {
  size_t n = automaton_all_.AmountNodes();
  vector<char> was(n, false);

  queue<pair<size_t, size_t> > q;
  q.push(make_pair(automaton_all_.root(), automaton.root()));

  while (!q.empty()) {
    size_t node1, node2;
    std::tie(node1, node2) = q.front();
    q.pop();

    if (was[node1]) {
      continue;
    }
    was[node1] = true;
    ++GetNode(node1)->docs_occurs_in;

    auto it1 = GetNode(node1)->begin();
    auto it2 = automaton.GetNode(node2)->begin();
    while (it1 != GetNode(node1)->end() && it2 != automaton.GetNode(node2)->end()) {
      if (it1->first < it2->first) {
        ++it1;
      }
      else if (it1->first > it2->first) {
        ++it2;
      }
      else {
        q.push(make_pair(it1->second, it2->second));
        ++it1;
        ++it2;
      }
    }
  }
}

void Dictionary::CollectGoodSubstrings(vector <Substring>* substrings) {
  size_t n = automaton_all_.AmountNodes();
  vector<vector<size_t> > rev(n);
  vector<vector<size_t> > rev_links(n);
  vector<double> max_score_substring(n, -1e20);
  vector<double> max_score_upstring(n, -1e20);
  vector<char> can_to_dict(n, true);
  vector<Node*> order;
  order.reserve(n - 1);

  for (size_t id = 1; id < n; ++id) {
    for (const auto& it : *GetNode(id)) {
      size_t to = it.second;
      rev[to].push_back(id);
    }
    if (GetNode(id)->link) {
      rev_links[GetNode(id)->link].push_back(id);
    }
    order.push_back(GetNode(id));
  }

  sort(order.begin(), order.end(), [](Node* node1, Node* node2) { return node1->len_actual < node2->len_actual; });

  // calc max_score_substring
  for (Node* node : order) {
    size_t id = GetIdNode(node);

    double max_score = -1e20;
    if (node->link) {
      double score = max_score_substring[node->link];
      if (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    for (size_t from : rev[id]) {
      double score = max_score_substring[from];
      if (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    if (CanAffordSubstringFrom(node)) {
      double our_score = Substring(automaton_all_, id).score();
      if (DoubleLess(our_score, max_score)) {
        can_to_dict[id] = false;
      }
      else {
        max_score = our_score;
      }
    }
    else {
      can_to_dict[id] = false;
    }

    max_score_substring[id] = max_score;
  }

  // calc max_score_upstring
  reverse(order.begin(), order.end());
  for (Node* node : order) {
    size_t id = GetIdNode(node);

    double max_score = -1e20;
    for (const auto& it : *node) {
      size_t to = it.second;
      double score = max_score_upstring[to];
      if (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    for (size_t to : rev_links[id]) {
      double score = max_score_upstring[to];
      if (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    if (CanAffordSubstringFrom(node)) {
      double our_score = Substring(automaton_all_, id).score();
      if (!DoubleLess(max_score, our_score)) {
        can_to_dict[id] = false;
      }
      else {
        max_score = our_score;
      }
    }
    else {
      can_to_dict[id] = false;
    }

    max_score_upstring[id] = max_score;
  }

  // result
  for (Node* node : order) {
    size_t id = GetIdNode(node);
    if (can_to_dict[id]) {
      substrings->push_back(Substring(automaton_all_, id));
    }
  }
}

vector<pair<string, size_t> > Dictionary::GetDictSubstringsList() {
  vector<pair<string, size_t> > substrings;
  substrings.reserve(dict_.size());
  for (Substring substring : dict_) {
    Node* node = automaton_all_.GetNode(substring.id_node());
    string cur_str(all_docs_.begin() + node->start_pos, all_docs_.begin() + node->start_pos + node->len_within_document);
    substrings.push_back(make_pair(cur_str, node->docs_occurs_in));
  }

  return substrings;
}

string Dictionary::GetDict() {
  string dict_str;
  for (const Substring& substring : dict_) {
    Node* node = automaton_all_.GetNode(substring.id_node());
    string cur_str(all_docs_.begin() + node->start_pos, all_docs_.begin() + node->start_pos + node->len_within_document);
    dict_str += cur_str;
  }

  return dict_str;
}

void Dictionary::OutputDictTo(string path) {
  std::ofstream file(path);
  file << GetDict();
}

bool Dictionary::CanAffordSubstringFrom(Node* node) const {
  return node->len_within_document >= kMinLen && node->docs_occurs_in >= kMinDocsOccursIn;
}
