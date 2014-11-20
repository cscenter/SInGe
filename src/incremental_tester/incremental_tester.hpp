#ifndef INCREMENTAL_TESTER_HPP_
#define INCREMENTAL_TESTER_HPP_

#include <string>

#include "dictionary.hpp"

class IncrementalTester {
public:

  IncrementalTester(const char * folder);

  void Run(size_t documents, size_t dict_margin, bool vs_empty_dict);

private:

  bool ProcessFile(const std::string& path, size_t documents, size_t dict_margin, bool vs_empty_dict);

  Dictionary dictionary;
  const char * folder;
  size_t seen_files;
  double sum_score;
  double sum_score_vs_empty_dict;
};

#endif // INCREMENTAL_TESTER_HPP_
