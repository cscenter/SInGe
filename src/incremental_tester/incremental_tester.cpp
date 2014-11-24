#include <stdexcept>
#include <google/vcencoder.h>
#include <google/vcdecoder.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>

#include "incremental_tester.hpp"

IncrementalTester::IncrementalTester(const char * folder) : folder(folder) {}

void IncrementalTester::Run(size_t documents, size_t dict_margin, bool vs_empty_dict) {
  dictionary = Dictionary();
  seen_files = 0;
  sum_score = 0;
  sum_score_vs_empty_dict = 0;

  DIR *dirp;
  if  (!(dirp = opendir(folder))) {
    throw std::invalid_argument("failed to open directory");
  }

  struct dirent *dp;
  while ((dp = readdir(dirp)) != NULL) {
    struct stat st;
    std::string path = std::string(folder) + "/" + dp->d_name;
    if (0 == stat(path.c_str(), &st)) {
      if (S_ISREG(st.st_mode)) {
        ProcessFile(path, documents, dict_margin, vs_empty_dict);
      }
    }
  }

  if  (seen_files == 0) {
    throw std::invalid_argument("provide mode valid files to test");
    return;
  }

  std::cout << "average score for " << seen_files << " documents: " << ((double) sum_score / seen_files) << std::endl;
  if  (vs_empty_dict) {
    std::cout << "average score versus empty dictionary: " << ((double) sum_score_vs_empty_dict / seen_files) << std::endl;
  }
  std::cout << "building dictionary margin was " << dict_margin << std::endl;
}

bool IncrementalTester::ProcessFile(const std::string& path, size_t documents, size_t dict_margin, bool vs_empty_dict) {
  if  (seen_files == documents) {
    return false;
  }

  std::ifstream input(path.c_str());
  std::string content;
  std::string buf;
  while (input >> buf) {
    content += buf;
  }

  if  (content.empty()) {
    return false;
  }

  std::string dict = dictionary.GetDict();
  open_vcdiff::VCDiffEncoder encoder(dict.data(), dict.size());
  encoder.SetFormatFlags(open_vcdiff::VCD_FORMAT_INTERLEAVED);
  std::string delta;
  encoder.Encode(content.data(), content.size(), &delta);

  double cur_score = (double) delta.size() / content.size();
  sum_score += cur_score;
  ++seen_files;

  std::cout << seen_files << "-th file" << std::endl;
  std::cout << "file size: " << content.size() << std::endl;
  std::cout << "score: " << cur_score << std::endl;

  if  (vs_empty_dict) {
    std::string empty_dict;
    open_vcdiff::VCDiffEncoder encoder(empty_dict.data(), empty_dict.size());
    encoder.SetFormatFlags(open_vcdiff::VCD_FORMAT_INTERLEAVED);
    std::string delta_empty;
    encoder.Encode(content.data(), content.size(), &delta_empty);
    
    double score_empty = (double) delta_empty.size() / content.size();
    sum_score_vs_empty_dict += cur_score / score_empty;
    std::cout << "score / (score empty dict): " << cur_score / score_empty << std::endl;
  }

  dictionary.AddDocumentViaStopSymbol(content);
  if  (seen_files % dict_margin == 0) {
    dictionary.BuildDict();
  }

  std::cout << std::endl;
  return true;
}

