#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <cstddef> // size_t

struct Node {
	std::map <char, Node*> next;
	Node* link;

	// s[l, r) -- the longest corresponding substring without STOP_SYMBOL
	int l, r;
	int len; 
	int amount_unique_docs;		

	Node();

	virtual ~Node();
};

#endif // NODE_HPP
