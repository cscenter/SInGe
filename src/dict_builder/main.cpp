/*!
* simple-SDCH-gen
*
* Copyright 2014 Pavel Savchenkov <pavelsavchenkow@gmail.com>
* Released under the MIT license
*/

#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <ctime>

#include "dictionary.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cerr;

void parse_args(int argc, char ** argv) {
  if  (argc < 3) {
    cout << "two arguments are needed: dir_files_to_add and dir_dict" << endl;
    return;
  }

  vector <string> paths;
  const char * dir_files = argv[1];
  DIR *dirp = opendir(dir_files);
  struct dirent *dp;
  while ((dp = readdir(dirp)) != NULL) {
    struct stat st;
    string path = std::string(dir_files) + "/" + dp->d_name;
    if (0 == stat(path.c_str(), &st)) {
      if (S_ISREG(st.st_mode)) {
        paths.push_back(path);			
      }
    }
  }
  
  cerr << "building dictionary..." << endl;

  //Dictionary dictionary(1 << 18, 20, '#', 1 << 21, 1.0, false);
  Dictionary dictionary;
  for (const auto& path : paths) {
    std::ifstream file(path);
    string content;
    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(content));
    content += "#";
    // dictionary.AddDocumentViaStopSymbol(content);
    dictionary.AddDocument(content);
  }

  dictionary.BuildDict();
  
  const char * dir_dict = argv[2];
  dictionary.OutputDictTo(string(dir_dict));

  cout << "ready in " << ((double) clock() / CLOCKS_PER_SEC) << '\n';
}

int main(int argc, char ** argv) {
  parse_args(argc, argv);
  return 0;
}

