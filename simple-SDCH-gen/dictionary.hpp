#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "node.hpp"
#include "suffix_automata.hpp"
#include <cstddef> // size_t
#include <vector>
#include <string>
#include <cstdlib>

class Dictionary {
	static const char STOP_SYMBOL;	
	static const int MAX_DICT;
	static const double EPS;
	static const int MIN_LEN;
	static const int MIN_AMOUNT_UNIQUE_DOCS;

	char* s;
	int length_s;
	std::vector <int> starts_docs;
	std::vector <int> lengths_docs;

	char* dict;
	int length_dict;

	static bool double_less(double a, double b);

	static bool double_equals(double a, double b);

	static double score_substring(int occurences, int length);

	static bool compare_substrings(const std::pair <double, Node*>& substring1, const std::pair <double, Node*>& substring2);

public:
	Dictionary();

	void init(const std::vector <std::string>& paths);
	
	void build();

	void bfs_automatons(SuffixAutomata* automata1, SuffixAutomata* automata2, int doc_id);

	void bfs_collect(SuffixAutomata* automata, int fake_doc_id, std::vector <std::pair<double, Node*> >* substrings);

	void output(std::string path);

	virtual ~Dictionary();
};

#endif // DICTIONARY_HPP
