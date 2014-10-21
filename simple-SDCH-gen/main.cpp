#include "dictionary.hpp"

#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <ctime>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cerr;

void parse_args(int argc, char ** argv) {
	if  (argc < 3) {
		cout << "two arguments are needed" << endl;
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
				cerr << "add train path: " << path << endl;
				paths.push_back(path);			
			}
		}
	}
	
	Dictionary dictionary;
	bool first_doc = true;
	for (const auto& path : paths) {
		std::ifstream file(path);
		string buf;
		bool first_line = true;
		string str;
		while (getline(file, buf)) {
//			/*
			if  (first_doc) {
				dictionary.AddDocument(buf);
				first_doc = false;
			} else if  (first_line) {
				dictionary.AddDocumentViaStopSymbol(buf);
				first_line = false;
			} else {
				dictionary.AddDocument(buf);
			}
//			*/
//			str += buf;
		}	
//		if  (first_doc) {
//			dictionary.AddDocument(str);
//			first_doc = false;
//		} else {
//			dictionary.AddDocumentViaStopSymbol(str);
//		}
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

