#include "suffix_automata.hpp"
#include <algorithm>
#include <cstdio>
#include <string>

SuffixAutomata::SuffixAutomata() {
	node_pool_ = nullptr;
	ptr_in_node_pool_ = nullptr;
	root_ = nullptr;
}

int SuffixAutomata::amount_nodes() {
	return ptr_in_node_pool_ - node_pool_;
}

int SuffixAutomata::get_id(Node* node) const {
	return node - node_pool_;
}

Node* SuffixAutomata::get_node(int id) {
	return node_pool_ + id;
}

Node* SuffixAutomata::new_node() {
	return ptr_in_node_pool_++;
}

void SuffixAutomata::add_character(char c, int current_len, Node** last, int pos_last_stop_symbol) {
	Node* node = new_node();
	node->r = current_len + 1;
	node->l = std::max(current_len - (*last)->len, pos_last_stop_symbol + 1);
	node->len = (*last)->len + 1;

	Node* p = *last;
	while (p) {
		if  (!p->next.count(c)) {
			p->next[c] = node;
			p = p->link;
			continue;
		}

		Node* q = p->next[c];
		if  (q->len == p->len + 1) {
			node->link = q;
			*last = node;
			return; 
		}

		Node* clone = new_node();
		clone->next = q->next;
		clone->link = q->link;
		clone->r = current_len + 1;
		clone->l = std::max(current_len - p->len, pos_last_stop_symbol + 1);
		clone->len = p->len + 1;

		node->link = clone;
		q->link = clone;
		while (p && p->next[c] == q) {
			p->next[c] = clone;
			p = p->link;
		}
		*last = node;
		return;
	}

	node->link = root_;
	*last = node;
}

void SuffixAutomata::fit_string(char const * const s, int length) {
	node_pool_ = new Node[std::max(3 * 3, 3 * length)];
	ptr_in_node_pool_ = node_pool_;

	root_ = new_node();
	Node* last = root_;
	for (int i = 0; i < length; ++i) {
		add_character(s[i], i, &last, -1);
	}	
}

void SuffixAutomata::fit_string(char const * const s, int length, char STOP_SYMBOL) {
	node_pool_ = new Node[std::max(3 * 3, 3 * length)];
	ptr_in_node_pool_ = node_pool_;

	root_ = new_node();
	Node* last = root_;
	int pos_last_stop_symbol = -1;
	for (int i = 0; i < length; ++i) {
		if  (s[i] == STOP_SYMBOL) {
			pos_last_stop_symbol = i;
		}
		add_character(s[i], i, &last, pos_last_stop_symbol);
	}

	for (Node* node = node_pool_; node < ptr_in_node_pool_; ++node) {
		node->len = node->r - node->l;
	}	
}

Node* SuffixAutomata::root() {
	return root_;
}

void SuffixAutomata::output() const {
	output(root_, "");
}

void SuffixAutomata::output(Node* v, std::string s) const {
	printf("%s\n", s.c_str());
	for (auto it = v->next.begin(); it != v->next.end(); ++it) {
		output(it->second, s + it->first);
 	}	
}

SuffixAutomata::~SuffixAutomata() {
	if  (node_pool_) {
		delete[] node_pool_;
	}
}


