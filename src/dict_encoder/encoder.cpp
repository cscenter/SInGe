#include <fstream>
#include <iostream>
#include <sstream>
#include <gflags/gflags.h>
#include <google/vcencoder.h>
#include <google/vcdecoder.h>

using std::string;
using std::cout;
using std::endl;


DEFINE_string(dictionary, "", "path to the dictionary");
DEFINE_string(document, "", "document for encode by dictionary");
DEFINE_string(delta, "delta", "encoded document name");
DEFINE_string(output, "out.html", "decoded document name");

void read(const string& path, string& content) {
    std::ifstream doc(path.c_str());
    if (doc.is_open()) {
        std::ostringstream ss;
        ss << doc.rdbuf();
        content = ss.str();
    }
    else cout << "Unable to read file " << path << endl;
}
void write(const string& path, const string& content) {
  std::ofstream myfile(path.c_str());
  if (myfile.is_open())
  {
    myfile << content;
    myfile.close();
  }
  else cout << "Unable to open file " << path << endl;
}

int main(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    cout << FLAGS_dictionary << endl;
    cout << FLAGS_document << endl;
    string document, dictionary;
    read(FLAGS_dictionary, dictionary);
    read(FLAGS_document, document);
    cout << "len doc = " << document.length() << endl;
    cout << "len dict = " << dictionary.length() << endl;
    open_vcdiff::VCDiffEncoder encoder(dictionary.data(), dictionary.size());
    encoder.SetFormatFlags(open_vcdiff::VCD_FORMAT_INTERLEAVED);
    std::string delta, output;
    encoder.Encode(document.data(), document.size(), &delta);
    cout << "len delta = " << delta.length() << endl;
    open_vcdiff::VCDiffDecoder decoder;
    decoder.Decode(dictionary.data(), dictionary.size(), delta, &output);
    write(FLAGS_delta, delta);
    write(FLAGS_output, output);
}
