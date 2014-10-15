#include "dictionary.hpp"
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include "dictionary.hpp"
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

	const char * dir_dict = argv[2];
	Dictionary dictionary;
	dictionary.init(paths);
	dictionary.build();
	dictionary.output(string(dir_dict));
	cerr << "ready in " << ((double) clock() / CLOCKS_PER_SEC) << '\n';
}

int main(int argc, char ** argv) {
	parse_args(argc, argv);
	return 0;
}

