#ifndef SUFFIX_AUTOMATA_HPP
#define SUFFIX_AUTOMATA_HPP

#include "node.hpp"
#include <cstddef> //size_t
#include <string>

class SuffixAutomata {
private:
	Node* node_pool_;
	Node* ptr_in_node_pool_;

	Node* root_;

	Node* new_node();

	void add_character(char c, int current_len, Node** last, int pos_last_stop_symbol);

public:
	SuffixAutomata();

	int amount_nodes();

	int get_id(Node* node) const;

	Node* get_node(int id);

	void fit_string(char const * const s, int length);

	void fit_string(char const * const s, int length, char STOP_SYMBOL);

	Node* root();

	void output() const;

	void output(Node* v, std::string s) const;

	virtual ~SuffixAutomata();
};

#endif // SUFFIX_AUTOMATA_HPP

