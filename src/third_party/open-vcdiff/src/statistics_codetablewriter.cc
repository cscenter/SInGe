// Copyright 2008 The open-vcdiff Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Definition of an abstract class that describes the interface between the
// encoding engine (which finds the best string matches between the source and
// target data) and the code table writer.  The code table writer is passed a
// series of Add, Copy, and Run instructions and produces an output file in the
// desired format.


#include <google/output_string.h>
#include <stdint.h>
#include <assert.h>
#include "statistics_codetablewriter.h"
#include "google/format_extension_flags.h"
#include "checksum.h"
#include "logging.h"


namespace open_vcdiff {
StatisticsCodeTableWriter::StatisticsCodeTableWriter(
    CodeTableWriterInterface *coder,
    std::shared_ptr<Statistics> const &statistics) : coder_(coder), statistics_(statistics) {
  std::cout << "Statistics writer construct"  << std::endl; // TODO: remove after debug

}


StatisticsCodeTableWriter::~StatisticsCodeTableWriter() {

}

bool StatisticsCodeTableWriter::Init(size_t dictionary_size) {
  if (statistics_->dictionary_size() != dictionary_size) {
    VCD_DFATAL << "Error StatisticsCodetableWriter initilization, dictionary size not equal to statistics dictionary size " << VCD_ENDL;
    assert(statistics_->dictionary_size() == dictionary_size);
  }
  return coder_->Init(dictionary_size);
}

void StatisticsCodeTableWriter::WriteHeader(
    OutputStringInterface *out, 
    VCDiffFormatExtensionFlags format_extensions) {
  coder_->WriteHeader(out, format_extensions);
}

void StatisticsCodeTableWriter::Add(const char *data, size_t size) {
  std::cout << "Statistics Add. data ptr: " << (void *)data << " size : " << size << std::endl; // TODO: remove after debug
  coder_->Add(data, size);

}

void StatisticsCodeTableWriter::Copy(int32_t offset, size_t size) {
  std::cout << "Statistics Copy. offset: " << offset << " size : " << size << std::endl; // TODO: remove after debug
  coder_->Copy(offset, size);
  statistics_->AddWeightToRange(1, offset, size);
}

void StatisticsCodeTableWriter::Run(size_t size, unsigned char byte) {
  std::cout << "Statistics size.  byte: " << byte << " size : " << size << std::endl; // TODO: remove after debug
  coder_->Run(size, byte);
}

void StatisticsCodeTableWriter::AddChecksum(VCDChecksum checksum) {
  coder_->AddChecksum(checksum);

}

void StatisticsCodeTableWriter::Output(OutputStringInterface *out) {
  coder_->Output(out);

}

void StatisticsCodeTableWriter::FinishEncoding(OutputStringInterface *out) {
  coder_->FinishEncoding(out);

}

bool StatisticsCodeTableWriter::VerifyDictionary(const char *dictionary, size_t size) const {
  return coder_->VerifyDictionary(dictionary, size);
}

bool StatisticsCodeTableWriter::VerifyChunk(const char *chunk, size_t size) const {
  return coder_->VerifyChunk(chunk, size);
}

} //open_vcdiff
