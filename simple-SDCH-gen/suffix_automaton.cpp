#include <algorithm>
#include <cstdio>
#include <string>
#include <iostream>

#include "suffix_automaton.hpp"

using std::vector;
using std::min;
using std::max;

const char SuffixAutomaton::kStopSymbol = '#';

SuffixAutomaton::SuffixAutomaton() : len_up_to_stop_symbol_(1) {
	NewNode(); // ~ nullptr
	last_node_ = NewNode();
}

SuffixAutomaton::~SuffixAutomaton() {}

size_t SuffixAutomaton::AmountNodes() const {
	return nodes_pool_.size();
}

void SuffixAutomaton::AddString(const char* const str, size_t length) {
//	ReserveFor(length);

	for (size_t i = 0; i < length; ++i) {
		AddCharacter(str[i]);
		++len_up_to_stop_symbol_;
	}	
}

void SuffixAutomaton::AddStringViaStopSymbol(const char* const str, size_t length) {
//	ReserveFor(length + 1);

	len_up_to_stop_symbol_ = 0;
	AddCharacter(kStopSymbol);
	++len_up_to_stop_symbol_;

	for (size_t i = 0; i < length; ++i) {
		AddCharacter(str[i]);
		++len_up_to_stop_symbol_;
	}	
}

size_t SuffixAutomaton::root() const {
	return 1;
}

bool SuffixAutomaton::Empty() const {
	return last_node_ == root();
}

void SuffixAutomaton::Output() {
	Output(root(), "");
}

void SuffixAutomaton::Output(size_t v, std::string s) {
	printf("%s v = %d, occurs = %d, len = %d\n", s.c_str(), v, GetNode(v)->docs_occurs_in, GetNode(v)->len_within_document);
	for (auto it = GetNode(v)->begin(); it != GetNode(v)->end(); ++it) {
		Output(it->second, s + it->first);
 	}	
}

size_t SuffixAutomaton::NewNode() {
	nodes_pool_.push_back(Node());
	return nodes_pool_.size() - 1;
}

size_t SuffixAutomaton::NewNode(size_t from) {
	auto* new_node = GetNode(from);
	nodes_pool_.push_back(*new_node);
	return nodes_pool_.size() - 1;
}

void SuffixAutomaton::ReserveFor(size_t length) {
	nodes_pool_.reserve(nodes_pool_.size() + 3 * length);
}

void SuffixAutomaton::AddCharacter(char ch) {
	size_t current_len = GetNode(last_node_)->len_actual + 1;
	size_t start_pos_after_stop_symbol = current_len - len_up_to_stop_symbol_;

	size_t new_node = NewNode();
	GetNode(new_node)->len_actual = current_len;
	GetNode(new_node)->len_within_document = min(current_len, len_up_to_stop_symbol_);
	GetNode(new_node)->start_pos = max(current_len - GetNode(new_node)->len_within_document, start_pos_after_stop_symbol);

	size_t prev = last_node_;
	last_node_ = new_node;
	for (; prev && !GetNode(prev)->HasEdgeThrough(ch); prev = GetNode(prev)->link) {
		GetNode(prev)->AddEdge(ch, new_node);
	}

	if  (!prev) {
		GetNode(new_node)->link = root();
		return;
	}
	
	size_t next = GetNode(prev)->NextNodeThrough(ch);
	if  (GetNode(next)->len_actual == GetNode(prev)->len_actual + 1) {
		GetNode(new_node)->link = next;
		return;
	}

	size_t middle = NewNode(next);
	GetNode(middle)->len_actual = GetNode(prev)->len_actual + 1;
	GetNode(middle)->len_within_document = min(GetNode(prev)->len_actual + 1, len_up_to_stop_symbol_);
	GetNode(middle)->start_pos = max(current_len - GetNode(middle)->len_within_document, start_pos_after_stop_symbol);

	for (; prev && GetNode(prev)->NextNodeThrough(ch) == next; prev = GetNode(prev)->link) {
		GetNode(prev)->AddEdge(ch, middle);
	}
	GetNode(new_node)->link = middle;
	GetNode(next)->link = middle;
}


