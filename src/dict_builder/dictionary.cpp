#include <map>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cassert>
#include <map>

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

const size_t Dictionary::kMaxDict = 1 << 16;
const size_t Dictionary::kMinLen = 3;
const size_t Dictionary::kMinDocsOccursIn = 2;

Dictionary::Dictionary() {}

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
//    printf("occurs = %d, len = %d\n", node->docs_occurs_in, node->len_within_document);
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
  size_t n = automaton_all_.AmountNodes();
  vector<vector<size_t> > rev(n);
  vector<vector<size_t> > rev_links(n);
  vector<double> max_score_substring(n, -1e20);
  vector<double> max_score_upstring(n, -1e20);
  vector<char> can_to_dict(n, true);
  vector<Node*> order;
  order.reserve(n - 1);

  for (size_t id : automaton_all_) {
    for (auto it = GetNode(id)->edges_begin(); it != GetNode(id)->edges_end(); ++it) {
      size_t to = it->second;
      rev[to].push_back(id);
    }
    if  (GetNode(id)->link) {
      rev_links[GetNode(id)->link].push_back(id);
    }
    order.push_back(GetNode(id));
  }
  
  sort(order.begin(), order.end(), [] (Node* node1, Node* node2) { return node1->len_actual < node2->len_actual; } );
    
  // calc max_score_substring
  for (Node* node : order) {
    size_t id = GetIdNode(node);

    double max_score = -1e20;
    if  (node->link) {
      double score = max_score_substring[node->link];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    for (size_t from : rev[id]) {
      double score = max_score_substring[from];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    if  (CanAffordSubstringFrom(node)) {
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
  for (Node* node : order) {
    size_t id = GetIdNode(node);

    double max_score = -1e20;
    for (auto it = node->edges_begin(); it != node->edges_end(); ++it) {
      size_t to = it->second;
      double score = max_score_upstring[to];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }
    }

    for (size_t to : rev_links[id]) {
      double score = max_score_upstring[to];
      if  (DoubleLess(max_score, score)) {
        max_score = score;
      }			
    }

    if  (CanAffordSubstringFrom(node)) {
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
  for (Node* node : order) {
    size_t id = GetIdNode(node);
    if  (can_to_dict[id]) {
      substrings->push_back(id);
    }
  }
}

bool Dictionary::CanAffordSubstringFrom(Node* node) const {
  return node->len_within_document >= kMinLen && node->docs_occurs_in >= kMinDocsOccursIn;
}
