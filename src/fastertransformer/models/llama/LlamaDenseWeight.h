/*
 * Copyright (c) OpenMMLab. All rights reserved.
 * Copyright (c) 2019-2023, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 // Modified from https://github.com/NVIDIA/FasterTransformer/blob/main/src/fastertransformer/layers/DenseWeight.h

#pragma once

#include "src/fastertransformer/layers/FfnWeight.h"
#include "src/fastertransformer/layers/attention_layers/AttentionWeight.h"
#include "src/fastertransformer/utils/cuda_utils.h"

namespace fastertransformer {

enum class WeightType : int
{
    kFP32,
    kFP16,
    kFP8,  // not supported yet
    kINT8,
    kINT4
};

inline size_t getBitSize(WeightType type)
{
    switch (type) {
        case WeightType::kFP32:
            return 32;
        case WeightType::kFP16:
            return 16;
        case WeightType::kFP8:
            return 8;
        case WeightType::kINT8:
            return 8;
        case WeightType::kINT4:
            return 4;
    }
}

template<typename T>
struct LlamaDenseWeight {

    size_t     input_dims;
    size_t     output_dims;
    void*      kernel;
    WeightType type;
    T*         bias;
    T*         scales;
    T*         zeros;
};

template<typename T>
struct LlamaAttentionWeight {
    LlamaDenseWeight<T> qkv;
    LlamaDenseWeight<T> output;
};

template<typename T>
struct LlamaFfnWeight {
    LlamaDenseWeight<T> gating;
    LlamaDenseWeight<T> intermediate;
    LlamaDenseWeight<T> output;
};

}  // namespace fastertransformer