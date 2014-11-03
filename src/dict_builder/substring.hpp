/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#ifndef SUBSTRING_HPP_
#define SUBSTRING_HPP_

#include <cstddef> // size_t

#include "suffix_automaton.hpp"

class Substring {
public:
  Substring(SuffixAutomaton& automaton, size_t id_node);

  double score();

  size_t id_node() const;

private:
  size_t id_node_;
  double score_;	 
};

#endif // SUBSTRING_HPP_