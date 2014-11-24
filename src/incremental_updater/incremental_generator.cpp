#include <iostream>
#include <fstream>
#include <vector>
#include <google/vcencoder.h>
#include <google/vcdecoder.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <unistd.h>
#include <fcntl.h>
#include <dictionary.hpp>
#include <statistics.h>
#include <sstream>
#include <gflags/gflags.h>

using std::string;
using std::vector;
using open_vcdiff::Statistics;
using std::cout;
using std::endl;
using std::cerr;

DEFINE_string(automaton_proto, "automaton.pb", "path to the serialized automaton");
DEFINE_string(new_documents, "",
                 "comma-separated list of documents to update the dictionary");
DEFINE_int64(max_size, 10000, "max allowable number of nodes in the automaton");
DEFINE_string(output_path, "dictionary",
                 "name of the file to be recorded new dictionary");
#define PROTOBUF_AUTOMATON_CONST 8867856

void split(vector<string>&, const string&, const string&);
bool serializeAutomatonToDisk(
      const SuffixAutomaton& automaton,
      const string& automatonPath);
bool deserializeAutomatonFromDisk(
      SuffixAutomaton& automaton,
      const string& automatonPath);

int main(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    vector<std::string> docs;
    split(docs,FLAGS_new_documents, ",");
    char cStopSymbol = '#';
    double automatonCoef = 0.9;
    SuffixAutomaton automaton = 
            SuffixAutomaton(cStopSymbol, FLAGS_max_size, automatonCoef);
    if (deserializeAutomatonFromDisk(automaton, FLAGS_automaton_proto))
    {
        cout << "Automation loaded." << endl;
    } else {
        cerr << "Failed to open: " << FLAGS_automaton_proto << endl;
    }
    for (auto it = docs.begin(); it != docs.end(); ++it) {
        std::ifstream doc(*it);
        cout << *it << " loaded." << endl;
        if (doc.is_open()) {
            std::ostringstream ss;
            ss << doc.rdbuf();
            const string str(ss.str());
            automaton.AddStringViaStopSymbol(str.c_str(), str.length());
            cout<< *it << " is added to automaton." << endl;
        }
    }
    Dictionary dictionary = Dictionary(automaton, 100, 3);
    dictionary.BuildDict();
    dictionary.OutputDictTo(FLAGS_output_path);
    cout << "Save dictionary." << endl;
    if (serializeAutomatonToDisk(automaton, FLAGS_automaton_proto)) {
        cout << "Automation saved." << endl;
    }
    return 0;
    }

void split(std::vector<string> & result,
      const std::string  & str,
      const std::string  & delimiter) {
    size_t  start = 0, end = 0;
    while (end != string::npos) {
        end = str.find(delimiter, start);
        result.push_back(str.substr( start,
                       (end == string::npos) ? string::npos : end - start));
        start = ((end > (string::npos - delimiter.size()))
                  ?  string::npos : end + delimiter.size());
    }
}

bool serializeAutomatonToDisk(
      const SuffixAutomaton& automaton,
      const string& automatonPath)
{
    int fd = open(automatonPath.c_str(), O_WRONLY | O_CREAT | O_TRUNC,
                             S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        cerr << "Can't create \'" << automatonPath << "\'." << endl;
        return false;
    }
    google::protobuf::io::ZeroCopyOutputStream* raw_output = 
            new google::protobuf::io::FileOutputStream(fd);
    google::protobuf::io::CodedOutputStream* coded_output = 
            new google::protobuf::io::CodedOutputStream(raw_output);

    auto proto_automaton_ptr = automaton.GetProtoAutomaton();
    std::ostringstream output_stream;
    proto_automaton_ptr->SerializeToOstream(&output_stream);
    string output_str(output_stream.str());
    coded_output->WriteLittleEndian32(PROTOBUF_AUTOMATON_CONST);
    coded_output->WriteVarint32(output_str.length());
    coded_output->WriteRaw(output_str.c_str(), output_str.length());

    delete coded_output;
    delete raw_output;
    close(fd);
    return true;
}

bool deserializeAutomatonFromDisk(
      SuffixAutomaton& automaton,
      const string& automatonPath) {
    int fd = open(automatonPath.c_str(), O_RDONLY);
    if (fd < 0) {
        cerr << "Can't open " << automatonPath << " fd = " << fd << endl;
        return false;
    }
    google::protobuf::io::ZeroCopyInputStream* raw_input = 
            new google::protobuf::io::FileInputStream(fd);
    google::protobuf::io::CodedInputStream* coded_input = 
            new google::protobuf::io::CodedInputStream(raw_input);

    uint32_t magic_number = 0;
    coded_input->ReadLittleEndian32(&magic_number);
    if (magic_number != PROTOBUF_AUTOMATON_CONST) {
        cerr << "File \'"<< automatonPath << "\' not in expected format." << endl;
        return false;
    }

    uint32_t sizeToRead = 0;
    coded_input->ReadVarint32(&sizeToRead);
    char* buffer = new char[sizeToRead];
    coded_input->ReadRaw(buffer, sizeToRead);
    ProtoAutomaton proto_automaton_ptr;
    proto_automaton_ptr.ParseFromArray((void*)buffer, sizeToRead);
    automaton = SuffixAutomaton(proto_automaton_ptr);
    delete coded_input;
    delete raw_input;
    close(fd);
    return true;
}