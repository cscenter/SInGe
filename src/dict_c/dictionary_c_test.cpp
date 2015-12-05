#include <gtest/gtest.h>
#include <string>
#include <cstddef> // size_t

#include "dictionary_c.h"
#include "dictionary.hpp"

using namespace std;

namespace {
  typedef unique_ptr<SInGe> SInGePtr;
  constexpr size_t kMaxDict = 2 << 17;
  constexpr size_t kMinLen  = 3;
  constexpr char kStopSymbol  = '#';
  constexpr size_t kMaxAutomatonSize =  2 << 17;
  constexpr double kAutomatonCoef = 1.0;

}

TEST(DictionaryTest, AddMethodTest) {

  std::string s1 = "abacaba";
  std::string s2 = "qwe_caba_rty";

  Dictionary dict_string(100, 3, '#', 1000, 1.0);
  dict_string.AddDocument(s1);
  dict_string.AddDocumentViaStopSymbol(s2);
  dict_string.BuildDict();

  auto singe = SInGeInit(100, 3, '#', 1000, 1.0);
  SInGeAddDocument(singe, s1.c_str(), s1.length());
  SInGeAddDocumentViaStopSymbol(singe, s2.c_str(), s2.length());
  auto dataC = SInGeGetDict(singe);
  std::string dataCStr(dataC.data, dataC.length);

  ASSERT_EQ(dataCStr, dict_string.GetDict()) << " dictionary for \"abacaba[stop]qwe_caba_rty\"";
  SInGeFree(singe);
}


TEST(DictionaryTest, MainDictionaryTest) {
  std::string s1 = "abacaba";
  std::string s2 = "qwecabarty";
  std::string s3 = "caba_cabaqwe";

  auto singe = SInGeInit(100, 3, '#', 1000, 1.0);
  for (auto s : std::vector<std::string>{s1, s2, s3}) {
    SInGeAddDocumentViaStopSymbol(singe, s.c_str(), s.length());
  }
//  SInGeAddDocumentViaStopSymbol(singe, s1.c_str(), s1.length());
//  SInGeAddDocumentViaStopSymbol(singe, s2.c_str(), s2.length());
//  SInGeAddDocumentViaStopSymbol(singe, s3.c_str(), s3.length());

  Dictionary & dict = *(static_cast<Dictionary*>(singe));
  auto dataC = SInGeGetDict(singe);
  auto dataCPP = dict.GetDict();


  std::vector<std::pair<std::string, size_t> > correct_vec;
  correct_vec.push_back(std::make_pair("caba", 3));
  correct_vec.push_back(std::make_pair("qwe", 2));

  auto aut_vec = dict.GetDictSubstringsList();


  ASSERT_EQ(correct_vec.size(), aut_vec.size()) << " in dictionary for \"abacaba[stop]qwecabarty[stop]caba_cabaqwe\"";
  for (size_t i = 0; i < correct_vec.size(); ++i) {
    ASSERT_EQ(correct_vec[i], aut_vec[i]) << " in dictionary for \"abacaba[stop]qwecabarty[stop]caba_cabaqwe\"";
  }
  SInGeFree(singe);
}

