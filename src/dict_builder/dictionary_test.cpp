#include <gtest/gtest.h>
#include <string>
#include <cstddef> // size_t

#include "dictionary.hpp"

TEST(DictionaryTest, AddMethodTest) {
  Dictionary dict_string;
  std::string s1 = "abacaba";
  dict_string.AddDocument(s1);
  std::string s2 = "qwe_caba_rty";
  dict_string.AddDocumentViaStopSymbol(s2);
  dict_string.BuildDict();

  Dictionary dict_char;
  dict_char.AddDocument("abacaba", 7);
  dict_char.AddDocumentViaStopSymbol("qwe_caba_rty", 12);
  dict_char.BuildDict();

  ASSERT_EQ(dict_char.GetDict(), dict_string.GetDict()) << " dictionary for \"abacaba[stop]qwe_caba_rty\"";
}

TEST(DictionaryTest, MainDictionaryTest) {
  std::string s1 = "abacaba";
  std::string s2 = "qwecabarty";
  std::string s3 = "caba_cabaqwe";

  Dictionary dict(100, 3, '#', 1000, 1.0);
  dict.AddDocumentViaStopSymbol(s1);
  dict.AddDocumentViaStopSymbol(s2);
  dict.AddDocumentViaStopSymbol(s3);
  dict.BuildDict();

  std::vector<std::pair<std::string, size_t> > correct_vec;
  correct_vec.push_back(std::make_pair("caba", 3));
  correct_vec.push_back(std::make_pair("qwe", 2));

  auto aut_vec = dict.GetDictSubstringsList();

  ASSERT_EQ(correct_vec.size(), aut_vec.size()) << " in dictionary for \"abacaba[stop]qwecabarty[stop]caba_cabaqwe\"";
  for (size_t i = 0; i < correct_vec.size(); ++i) {
    ASSERT_EQ(correct_vec[i], aut_vec[i]) << " in dictionary for \"abacaba[stop]qwecabarty[stop]caba_cabaqwe\"";
  }
}

