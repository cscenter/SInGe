/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#ifndef NODE_HPP_
#define NODE_HPP_

#include <vector>
#include <cstdlib>
#include <cstddef> // size_t

class Node {
public:
  Node();

  ~Node();

  bool HasEdgeThrough(char ch);

  size_t NextNodeThrough(char ch);

  std::vector<std::pair<char, size_t> >::iterator begin();

  std::vector<std::pair<char, size_t> >::iterator end();

  bool AddEdge(char ch, size_t to);

  size_t link;
  size_t len_actual;
  size_t len_within_document;
  size_t start_pos; 
  size_t docs_occurs_in;		
  
private:
  std::vector<std::pair<char, size_t> > edges_;
  bool sorted_;
};

#endif // NODE_HPP_
