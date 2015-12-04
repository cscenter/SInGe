//
// Created by  Vladimir Skipor on 03/12/15.
//

#include "dictionary_c.h"
#include "dictionary.hpp"

namespace {

}

extern "C" {

SInGe SInGeInit(size_t kMaxDict, size_t kMinLen, char kStopSymbol, size_t kMaxAutomatonSize, double kAutomatonCoef) {
  return static_cast<SInGe> (new Dictionary(kMaxDict, kMinLen, kStopSymbol, kMaxAutomatonSize, kAutomatonCoef));
};

void SInGeFree(SInGe gen) {
  delete static_cast<Dictionary*>(gen);

};

void SInGeAddDocument(SInGe gen, char* doc, size_t length) {
  static_cast<Dictionary*>(gen)->AddDocument(doc, length);
};

void SInGeAddDocumentViaStopSymbol(SInGe gen, char* doc, size_t length) {
  static_cast<Dictionary*>(gen)->AddDocumentViaStopSymbol(doc, length);
};

SInGeDict SInGeGetDict(SInGe gen) {
  auto dict_str = static_cast<Dictionary*>(gen)->GetDict();
  auto data = new char[dict_str.size()];
  strncpy(data, dict_str.data(), dict_str.size());
  return SInGeDict{data, dict_str.size()};
};


}
