//
// Created by  Vladimir Skipor on 03/12/15.
//

#include "dictionary_c.h"
#include "dictionary.hpp"
//#include <iostream>

namespace {
//  std::ostream & Log() {
//    return std::cout << std::endl << "SInGe: ";
//  }

  Dictionary * ToDict(SInGe gen) {
    return static_cast<Dictionary*>(gen);
  }
}

extern "C" {

SInGe SInGeInit(size_t kMaxDict, size_t kMinLen, char kStopSymbol, size_t kMaxAutomatonSize, double kAutomatonCoef) {
//  Log() << "Init";
  return static_cast<SInGe> (new Dictionary(kMaxDict, kMinLen, kStopSymbol, kMaxAutomatonSize, kAutomatonCoef));
};

void SInGeFree(SInGe gen) {
//  Log() << "Free";
  delete ToDict(gen);

};

void SInGeAddDocument(SInGe gen, const char* doc, size_t length) {
//  Log() << "AddDocument";
  ToDict(gen)->AddDocument(doc, length);
};

void SInGeAddDocumentViaStopSymbol(SInGe gen, const char* doc, size_t length) {
//  Log() << "AddDocumentViaStopSymol";
  ToDict(gen)->AddDocumentViaStopSymbol(doc, length);
};

SInGeDict SInGeGetDict(SInGe gen) {
//  Log() << "GetDict";
  auto * dict_ptr = ToDict(gen);
  dict_ptr->BuildDict();
  auto dict_str = dict_ptr->GetDict();
  auto data = new char[dict_str.size()];
  strncpy(data, dict_str.data(), dict_str.size());
  return SInGeDict{data, dict_str.size()};
};


}
