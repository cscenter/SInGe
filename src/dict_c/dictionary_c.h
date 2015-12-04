//
// Created by  Vladimir Skipor on 03/12/15.
//

#ifndef SINGE_DICTIONARY_C_H
#define SINGE_DICTIONARY_C_H

// foo.h
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* SInGe;

struct SInGeDict {
    const char * data;
    const size_t length;
};

SInGe SInGeInit(size_t kMaxDict, size_t kMinLen, char kStopSymbol, size_t kMaxAutomatonSize, double kAutomatonCoef);

void SInGeFree(SInGe gen);

void SInGeAddDocument(SInGe gen, char* doc, size_t length);

void SInGeAddDocumentViaStopSymbol(SInGe gen, char* doc, size_t length);

struct SInGeDict SInGeGetDict(SInGe gen);



#ifdef __cplusplus
}
#endif

#endif //SINGE_DICTIONARY_C_H
