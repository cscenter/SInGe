#include <iostream>
#include <cstring>

#include "incremental_tester.hpp"

using std::cout;
using std::endl;

const char * kFolderParam = "-folder";
const char * kDictBuildingMarginParam = "-dict_building_margin";
const char * kDocumentsToDeal = "-documents";
const char * kNeedToCompareWithEmpty = "-versus_empty";

int main(int argc, char ** argv) {
  char * folder = nullptr;
  size_t dict_margin = 1;
  size_t documents = 1000;
  bool vs_empty_dict = false;

  for (int i = 1; i < argc; ) {
    if  (!strcmp(argv[i], kFolderParam)) {
      if  (i + 1 >= argc) {
        cout << "cannot find folder name" << endl;
        return 1;
      }
      folder = argv[i + 1];
      i += 2;
    } else if  (!strcmp(argv[i], kDictBuildingMarginParam)) {
      if  (i + 1 >= argc) {
        cout << "cannot find dictionary building margin" << endl;
        return 1;
      }
      dict_margin = std::stol(argv[i + 1]);
      i += 2;
    } else if  (!strcmp(argv[i], kDocumentsToDeal)) {
      if  (i + 1 >= argc) {
        cout << "cannot find the number of documents to deal with" << endl;
        return 1;
      }
      documents = std::stol(argv[i + 1]);
      i += 2;
    } else if  (!strcmp(argv[i], kNeedToCompareWithEmpty)) {
      vs_empty_dict = true;
      ++i;
    } else {
      cout << "cannot recognise parameter \"" << std::string(argv[i]) << "\"" << endl;
      return 1; 
    }
  }  

  IncrementalTester(folder).Run(documents, dict_margin, vs_empty_dict);
  return 0;
}

