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

#include "statistics.h"

namespace open_vcdiff {

void Statistics::AddWeightToRange(int weight, int32_t offset, size_t size) {
  range_weights_[offset] += weight;
  range_weights_[offset + size] -= weight;
}

std::vector<int> Statistics::GetByteWeights() const {
  std::vector<int> byte_weights(dictionary_size_);
  int prefix_sum = 0;
  for (size_t byte_index = 0; byte_index < dictionary_size_; ++byte_index) {
    prefix_sum += range_weights_[byte_index];
    byte_weights[byte_index] = prefix_sum;
  }
  return byte_weights;
}

}//open_vcdiff