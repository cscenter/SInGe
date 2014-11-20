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

#include <vector>
#include <stddef.h>
#include <stdint.h>

#ifndef OPEN_VCDIFF_STATISTICS_H_
#define OPEN_VCDIFF_STATISTICS_H_
namespace open_vcdiff {

class Statistics {


public:
  Statistics(size_t dictionary_size)
      : dictionary_size_(dictionary_size),
        range_weights_(dictionary_size) {
  }


  inline size_t dictionary_size() const {
    return dictionary_size_;
  }

  void AddWeightToRange(int weight, int32_t offset, size_t size);

  std::vector<int> GetByteWeights() const;


private:
  size_t dictionary_size_;

  //weight(byte[i]) = sum(range_weights[0 .. i])
  std::vector<int> range_weights_;


};
} // open_vcdiff

#endif //OPEN_VCDIFF_STATISTICS_H_
