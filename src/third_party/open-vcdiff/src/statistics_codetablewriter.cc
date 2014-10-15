#include <google/output_string.h>
#include <stdint.h>
#include "statistics_codetablewriter.h"
#include "google/format_extension_flags.h"
#include "checksum.h"


open_vcdiff::Statistics_CodeTableWriter::Statistics_CodeTableWriter(bool interleaved) {
    coder_.reset(new InnerCoder(interleaved));

}

open_vcdiff::Statistics_CodeTableWriter::Statistics_CodeTableWriter(bool interleaved,
        int near_cache_size,
        int same_cache_size,
        open_vcdiff::VCDiffCodeTableData const &code_table_data,
        unsigned char max_mode) {
    coder_.reset(new InnerCoder(interleaved, near_cache_size, same_cache_size, code_table_data, max_mode));
}

open_vcdiff::Statistics_CodeTableWriter::~Statistics_CodeTableWriter() {

}

bool open_vcdiff::Statistics_CodeTableWriter::Init(size_t dictionary_size) {
    return coder_->Init(dictionary_size);
}

void open_vcdiff::Statistics_CodeTableWriter::WriteHeader(open_vcdiff::OutputStringInterface *out, open_vcdiff::VCDiffFormatExtensionFlags format_extensions) {
    coder_->WriteHeader(out, format_extensions);

}

void open_vcdiff::Statistics_CodeTableWriter::Add(const char *data, size_t size) {
    coder_->Add(data, size);

}

void open_vcdiff::Statistics_CodeTableWriter::Copy(int32_t offset, size_t size) {
    coder_->Copy(offset, size);

}

void open_vcdiff::Statistics_CodeTableWriter::Run(size_t size, unsigned char byte) {
    coder_->Run(size, byte);
}

void open_vcdiff::Statistics_CodeTableWriter::AddChecksum(open_vcdiff::VCDChecksum checksum) {
    coder_->AddChecksum(checksum);

}

void open_vcdiff::Statistics_CodeTableWriter::Output(open_vcdiff::OutputStringInterface *out) {
    coder_->Output(out);

}

void open_vcdiff::Statistics_CodeTableWriter::FinishEncoding(open_vcdiff::OutputStringInterface *out) {
    coder_->FinishEncoding(out);

}

bool open_vcdiff::Statistics_CodeTableWriter::VerifyDictionary(const char *dictionary, size_t size) const {
    return coder_->VerifyDictionary(dictionary, size);
}

bool open_vcdiff::Statistics_CodeTableWriter::VerifyChunk(const char *chunk, size_t size) const {
    return coder_->VerifyChunk(chunk, size);
}
