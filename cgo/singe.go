package singe

/*
#cgo LDFLAGS: -ldictgen_c

#include <stdlib.h>
#include "dictionary_c.h"
*/
import "C"

import "unsafe"

const (
	DefaultMinLen             = 10
	DefaultStopSymbol         = byte(0)
	DefaultAutomatonSizeLimit = 2 << 20
	DefaultScoreDecreaseCoef  = 1.0
)

func unsafeBytesToString(b []byte) string {
	return *(*string)(unsafe.Pointer(&b))
}

type Singe struct {
	singe C.SInGe
	stopSymbol byte
}

func NewCustom(
	maxDict uint,
	minLen uint,
	stopSymbol byte,
	automatonSizeLimit uint,
	scoreDecreaseCoef float64,
) Singe {
	return Singe{
		C.SInGeInit(
			C.size_t(maxDict),
			C.size_t(minLen),
			C.char(stopSymbol),
			C.size_t(automatonSizeLimit),
			C.double(scoreDecreaseCoef),
		),
		stopSymbol,
	}
}

func New(maxDict uint) Singe {
	return NewCustom(maxDict, DefaultMinLen, DefaultStopSymbol, DefaultAutomatonSizeLimit, DefaultScoreDecreaseCoef)
}

func (s Singe) Free() {
	C.SInGeFree(s.singe)
}

func (s Singe) Add(data []byte) {
	cData := C.CString(unsafeBytesToString(data))
	C.SInGeAddDocument(s.singe, cData, C.size_t(len(data)))
	C.free(unsafe.Pointer(cData))
}

func (s Singe) AddViaStopSymbolIncremental(data []byte) { //for incremental update
	cData := C.CString(unsafeBytesToString(data))
	C.SInGeAddDocumentViaStopSymbol(s.singe, cData, C.size_t(len(data)))
	C.free(unsafe.Pointer(cData))
}

func (s Singe) GetDict() (dict []byte) {
	dict_c := C.SInGeGetDict(s.singe)
	dict = C.GoBytes(unsafe.Pointer(dict_c.data), C.int(dict_c.length))
	C.free(unsafe.Pointer(dict_c.data))
	return
}



