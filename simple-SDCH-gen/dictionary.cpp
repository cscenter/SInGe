#include "dictionary.hpp"
#include "suffix_automata.hpp"
#include <map>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::cerr;
using std::endl;

const double Dictionary::EPS = 1e-10;
const int Dictionary::MAX_DICT = 1 << 16;
const char Dictionary::STOP_SYMBOL = '#';
const int Dictionary::MIN_LEN = 3;
const int Dictionary::MIN_AMOUNT_UNIQUE_DOCS = 2;

bool Dictionary::double_equals(double a, double b) {
	return fabs(a - b) < EPS;
}

bool Dictionary::double_less(double a, double b) {
	return !double_equals(a, b) && a < b; 
}

double Dictionary::score_substring(int occurences, int length) {
	return occurences * double(length - 3) / length; 
}

bool Dictionary::compare_substrings(const pair<double, Node*>& substring1, const pair<double, Node*>& substring2) {
	return double_less(substring2.first, substring1.first);
}

Dictionary::Dictionary() {
	s = nullptr;
	length_s = 0;

	dict = nullptr;
	length_dict = 0;
}

void Dictionary::init(const vector <string>& paths) {
	cerr << "initializing dictionary..." << endl;
	
	starts_docs = vector <int>(paths.size(), 0);
	lengths_docs = vector <int>(paths.size(), 0);
	string std_s;
	for (int i = 0; i < (int) paths.size(); ++i) {
		if  (!std_s.empty()) {
			std_s += STOP_SYMBOL;
		}
		starts_docs[i] = std_s.size();

		std::ifstream file(paths[i]);
		string buf;
		while (getline(file, buf)) {
			std_s += buf;
			lengths_docs[i] += buf.size();
		}
	}

	length_s = std_s.size();
	s = new char[length_s];
	for (int i = 0; i < length_s; ++i) {
		s[i] = std_s[i];
	}

	cerr << "dictionary has been initialized" << endl;
}

void Dictionary::build() {
	cerr << "building dictionary..." << endl;
	cerr << "sum of the doc's length = " << length_s << endl;

	SuffixAutomata automata_all;
	automata_all.fit_string(s, length_s, STOP_SYMBOL);

	for (int i = 0; i < (int) starts_docs.size(); ++i) {
		SuffixAutomata automata_cur;
		automata_cur.fit_string(s + starts_docs[i], lengths_docs[i]);
		bfs_automatons(&automata_all, &automata_cur, i);
	}

	cerr << "frequences have been calced" << endl;

	vector <pair<double, Node*> > substrings; 
	bfs_collect(&automata_all, starts_docs.size(), &substrings);

	sort(substrings.begin(), substrings.end(), compare_substrings);

	cerr << "good substrings has been collected and sorted" << endl;

	vector <Node*> dict_nodes;
	for (int i = 0; i < (int) substrings.size(); ++i) {
		Node* node = substrings[i].second;
		if  (length_dict + node->len > MAX_DICT) {
			continue;
		} 
		length_dict += node->len;
		dict_nodes.push_back(node);
	}

	cerr << "dict's length = " << length_dict << ", " << (100 * length_dict / length_s) << " persents of all documents" << endl;

	dict = new char[length_dict];
	int pos_dict = 0;
	for (Node* node : dict_nodes) {
		for (int j = node->l; j < node->r; ++j) {
			dict[pos_dict++] = s[j];
		}
	}

	cerr << "dictionary has been built" << endl;
}

void Dictionary::bfs_collect(SuffixAutomata* automata, int fake_doc_id, vector <pair<double, Node*> >* substrings) {
	int n = automata->amount_nodes();
	vector <vector<Node*> > prev(n);
	vector <vector<Node*> > rev_links(n);
	vector <double> max_score_substring(n, -1e20);
	vector <double> max_score_upstring(n, -1e20);
	vector <char> can_to_dict(n, true);

	for (int i = 0; i < n; ++i) {
		Node* node = automata->get_node(i);
		for (auto it = node->next.begin(); it != node->next.end(); ++it) {
			Node* to = it->second;
			prev[automata->get_id(to)].push_back(node);
		}
		if  (node->link) {
			rev_links[automata->get_id(node->link)].push_back(node);
		}
	}

	vector <Node*> order(n);
	for (int i = 0; i < n; ++i) {
		order[i] = automata->get_node(i);
	}

	sort(order.begin(), order.end(), [] (Node* node1, Node* node2) { return node1->len < node2->len; });
	
	// calc max_score_substring
	for (int i = 0; i < n; ++i) {
		Node* node = order[i];

		if  (node->len < MIN_LEN || node->amount_unique_docs < MIN_AMOUNT_UNIQUE_DOCS) {
			continue;
		}

		double max_score = -1e20;
		if  (node->link) {
			double score = max_score_substring[automata->get_id(node->link)];
			if  (double_less(max_score, score)) {
				max_score = score;
			}
		}

		for (Node* from : prev[i]) {
			double score = max_score_substring[automata->get_id(from)];
			if  (double_less(max_score, score)) {
				max_score = score;
			}
		}

		double our_score = score_substring(node->amount_unique_docs, node->len);
		if  (double_less(our_score, max_score)) {
			can_to_dict[i] = false;
		} else {
			max_score = our_score;
		}

		max_score_substring[i] = max_score;
	}

	
	// calc max_score_upstring
	for (int i = n - 1; i >= 0; --i) {
		Node* node = automata->get_node(i);

		if  (node->len < MIN_LEN || node->amount_unique_docs < MIN_AMOUNT_UNIQUE_DOCS) {
			continue;
		}

		double max_score = -1e20;
		for (auto it = node->next.begin(); it != node->next.end(); ++it) {
			Node* to = it->second;
			double score = max_score_upstring[automata->get_id(to)];
			if  (double_less(max_score, score)) {
				max_score = score;
			}
		}

		for (Node* to : rev_links[i]) {
			double score = max_score_upstring[automata->get_id(to)];
			if  (double_less(max_score, score)) {
				max_score = score;
			}			
		}

		double our_score = score_substring(node->amount_unique_docs, node->len);
		if  (!double_less(max_score, our_score)) {
			can_to_dict[i] = false;
		} else {
			max_score = our_score;
		}

		max_score_upstring[i] = max_score;
	}

	// result
	for (int i = 0; i < n; ++i) {
		if  (can_to_dict[i]) {
			Node* node = automata->get_node(i);
			substrings->push_back(make_pair(score_substring(node->amount_unique_docs, node->len), node));
		}
	} 
}

void Dictionary::bfs_automatons(SuffixAutomata* automata1, SuffixAutomata* automata2, int doc_id) {
	int n = automata1->amount_nodes();
	vector <char> was(n, false);
	
	std::queue <pair<Node*, Node*> > q;
	q.push(make_pair(automata1->root(), automata2->root()));
	
	while (!q.empty()) {
		Node* node1 = q.front().first;
		Node* node2 = q.front().second;
		q.pop();

		if  (was[automata1->get_id(node1)]) {
			continue;
		}	
		was[automata1->get_id(node1)] = true;
		++node1->amount_unique_docs;
	
		auto it1 = node1->next.begin();
		auto it2 = node2->next.begin();
		while (it1 != node1->next.end() && it2 != node2->next.end()) {
			if  (it1->first < it2->first) {
				++it1;
			} else if  (it1->first > it2->first) {
				++it2;
			} else {
				q.push(make_pair(it1->second, it2->second));
				++it1;
				++it2;
			}
		}
	}
}

void Dictionary::output(string path) {
	std::ofstream file(path);
	for (int i = 0; i < length_dict; ++i) {
		file << dict[i];
	}
}

Dictionary::~Dictionary() {
	if  (s) {
		delete[] s;
	}
	if  (dict) {
		delete[] dict;
	}
}
