#pragma once

#include "tokenizers-cpp/common.h"
#include "tokenizers-cpp/processors.rs.h"

#include <string>
// for std::pair
#include <utility>

namespace huggingface {
namespace tokenizers {
struct Encoding {
    HFT_FFI_WRAPPER(Encoding);

public:
};

struct BertProcessing {
    HFT_FFI_WRAPPER(BertProcessing);

public:
    BertProcessing(std::pair<nonstd::string_view, uint32_t> sep,
                   std::pair<nonstd::string_view, uint32_t> cls)
        : inner_(ffi::bert_post_processor(
              {to_rust_string(sep.first), sep.second},
              {to_rust_string(cls.first), cls.second})){};

    HFT_RESULT(Encoding)
    process(const Encoding& encoding, bool add_special_tokens) {
        HFT_TRY(Encoding,
                {ffi::process_bert(*inner_, *encoding, add_special_tokens)});
    }

    HFT_RESULT(Encoding)
    process(const Encoding& encoding, const Encoding& pair_encoding,
            bool add_special_tokens) {
        HFT_TRY(Encoding,
                {ffi::process_pair_bert(*inner_, *encoding, *pair_encoding,
                                        add_special_tokens)});
    }
};

}  // namespace tokenizers
}  // namespace huggingface