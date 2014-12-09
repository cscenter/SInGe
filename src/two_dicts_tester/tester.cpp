#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <google/vcencoder.h>
#include <google/vcdecoder.h>
#include <dirent.h>
#include <sys/stat.h>

using std::cout;
using std::endl;
using std::string;

const char * kOldDictFileNameParam = "-file_name_old";
const char * kNewDictFileNameParam = "-file_name_new";
const char * kDocumentsFolderParam = "-folder_documents";
const char * kResultFileNameParam = "-result_file_name";  

double CalcScore(const string& path, const string& dict) {
  std::ifstream input(path.c_str());

  if  (!input.is_open()) {
    throw std::invalid_argument("cannot open file \'" + path + "\'");
  }

  string content;
  string buf;
  while (input >> buf) {
    content += buf;
  }

  if  (content.empty()) {
    return 0.0;
  }

  open_vcdiff::VCDiffEncoder encoder(dict.data(), dict.size());
//  encoder.SetFormatFlags(open_vcdiff::VCD_FORMAT_INTERLEAVED);
  std::string delta;
  encoder.Encode(content.data(), content.size(), &delta);
  return (double) delta.size() / content.size();
}

string ReadDict(const char * dict_file_name) {
  std::ifstream input(dict_file_name);

  if  (!input.is_open()) {
    throw std::invalid_argument("cannot read from file \'" + string(dict_file_name) + "\'");
  }

  string dict;
  input >> dict;
  return dict;
}

double CalcScore(const char * dict_file_name, const char * documents_folder) {
  double score = 0.0;
  size_t cnt_docs = 0;

  string dict = ReadDict(dict_file_name);

  DIR *dirp;
  if  (!(dirp = opendir(documents_folder))) {
    throw std::invalid_argument("failed to open directory");
  }

  struct dirent *dp;
  while ((dp = readdir(dirp)) != NULL) {
    struct stat st;
    std::string path = string(documents_folder) + "/" + dp->d_name;
    if (0 == stat(path.c_str(), &st)) {
      if (S_ISREG(st.st_mode)) {
        score += CalcScore(path, dict);
        ++cnt_docs;
      }
    }
  }

  if  (!cnt_docs) {
    return 0.0;
  }
  return score / cnt_docs;
}

int main(int argc, char ** argv) {
  char * old_dict_file_name = nullptr;
  char * new_dict_file_name = nullptr;
  char * documents_folder = nullptr;
  char * result_file_name = nullptr;

  for (int i = 1; i < argc; ) {
    if  (!strcmp(argv[i], kOldDictFileNameParam)) {
      if  (i + 1 >= argc) {
        cout << "cannot find old dictionary's file name" << endl;
        return 1;
      }
      old_dict_file_name = argv[i + 1];
      i += 2;
    } else if  (!strcmp(argv[i], kNewDictFileNameParam)) {
      if  (i + 1 >= argc) {
        cout << "cannot find new dictionary's file name" << endl;
        return 1;
      }    
      new_dict_file_name = argv[i + 1];
      i += 2;
    } else if  (!strcmp(argv[i], kDocumentsFolderParam)) {
      if  (i + 1 >= argc) {
        cout << "cannot find documents' folder name" << endl;
        return 1;
      }
      documents_folder = argv[i + 1];
      i += 2;
    } else if  (!strcmp(argv[i], kResultFileNameParam)) {
      if  (i + 1 >= argc) {
        cout << "cannot find result's file name" << endl;
        return 1;
      }
      result_file_name = argv[i + 1];
      i += 2;
    } else {
      cout << "unrecognized parameter \'" << string(argv[i]) << "\'" << endl;
      return 1;
    }
  }  

  if  (!old_dict_file_name) {
    cout << "old dictionary's file name must be specified with \'" << string(kOldDictFileNameParam) << "\'" << endl;
    return 1;
  }

  if  (!new_dict_file_name) {
    cout << "new dictionary's file name must be specified with \'" << string(kNewDictFileNameParam) << "\'" << endl;
    return 1;
  }

  if  (!documents_folder) {
    cout << "documents' folder must be specified with \'" << string(kDocumentsFolderParam) << "\'" << endl;
    return 1;
  }

  if  (!result_file_name) {
    cout << "result's file name must be specified with \'" << string(kResultFileNameParam) << "\'" << endl;
    return 1;
  }

  std::ofstream output(result_file_name);
  try {
    // smaller result is better
    output << CalcScore(new_dict_file_name, documents_folder) / CalcScore(old_dict_file_name, documents_folder) << endl;
  } catch (const std::exception& ex) {
    cout << "an exception was thrown " << ex.what() << endl;
    return 1; 
  }
  return 0;
}

