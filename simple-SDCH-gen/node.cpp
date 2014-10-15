#include "node.hpp"

Node::Node() {
	link = nullptr;
	l = 0;
	r = 0;
	len = 0;

	amount_unique_docs = 0;
}

Node::~Node() {}

