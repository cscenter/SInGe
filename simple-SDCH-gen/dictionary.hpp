#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include <cstddef> // size_t
#include <vector>
#include <string>
#include <cstdlib>

#include "node.hpp"
#include "suffix_automaton.hpp"
#include "substring.hpp"

class Dictionary {
public:
	static const size_t kMaxDict;
	static const size_t kMinLen;
	static const size_t kMinDocsOccursIn;

	Dictionary();

	~Dictionary();

	void AddDocument(std::string& doc);

	void AddDocumentViaStopSymbol(std::string& doc);
		
	void BuildDict();

	void UpdateOccurences(SuffixAutomaton& automaton);

	void CollectGoodSubstrings(std::vector<Substring>* substrings);

	std::vector<std::pair<std::string, size_t> > GetDictSubstringsList();

	std::string GetDict();

	void OutputDictTo(std::string path);

private:
	bool CanAffordSubstringFrom(Node* node) const;

	inline const Node* GetNode(size_t id) const {
		return automaton_all_.GetNode(id);
	}

	inline Node* GetNode(size_t id) {
		return automaton_all_.GetNode(id);
	}

	inline const size_t GetIdNode(Node* node) const {
		return automaton_all_.GetIdNode(node);
	}

	inline size_t GetIdNode(Node* node) {
		return automaton_all_.GetIdNode(node);
	}

	SuffixAutomaton automaton_all_;
	std::string all_docs_;
	std::vector<size_t> starts_docs_;
	std::vector<size_t> lengths_docs_;
	std::vector<Substring> dict_;
};

#endif // DICTIONARY_HPP_
