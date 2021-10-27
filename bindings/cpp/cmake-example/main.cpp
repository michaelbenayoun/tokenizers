#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tokenizers-cpp/tokenizer.h>
#include <tokenizers-cpp/input_sequence.h>

using namespace huggingface::tokenizers;

void test_tokenizer(Tokenizer& tokenizer) {
    auto encodings =  tokenizer.encode("HuggingFace is great!", true);
    std::cout << "Encoding: 'Hugging Face is great!' -> " << encodings->len() << " tokens:" << std::endl;
    std::cout << "Tokens: ";
    for(const auto &item: encodings.get_tokens())
        std::cout << item << " ";
    std::cout << std::endl;
    std::cout << "Ids: ";
    for(const auto &item: encodings.get_ids())
        std::cout << item << " ";
    std::cout << std::endl;
}

int main() {
    std::cout << "Bert Tokenizer example:" << std::endl;

    std::cout << "* By proceeding step by step:" << std::endl;
    auto builder = WordPieceBuilder::from_file("data/vocab.txt");
    auto tokenizer = Tokenizer(builder->build());
    tokenizer.with_normalizer(Normalizer::bert())
            .with_pre_tokenizer(PreTokenizer::bert())
            .with_post_processor(
                    PostProcessor::bert("[SEP]", 101, "[CLS]", 102));
    test_tokenizer(tokenizer);


    std::cout << std::endl;
    std::cout << "* By loading from file directly:" << std::endl;
    auto tokenizer_from_file = Tokenizer::from_file("data/tokenizer.json");
    test_tokenizer(tokenizer_from_file);

    std::cout << std::endl;
    std::cout << "* By loading from a string:" << std::endl;
    std::ifstream t("data/tokenizer.json");
    std::stringstream buffer;
    buffer << t.rdbuf();
    auto tokenizer_from_string = Tokenizer::from_str(buffer.str());
    test_tokenizer(tokenizer_from_string);

    /*
    std::cout << std::endl;
    std::cout << "* By loading from the Hugging Face Hub:" << std::endl;
    auto tokenizer_from_hub = Tokenizer::from_pretrained("bert-base-uncased");
    test_tokenizer(tokenizer_from_hub);
    */

    std::cout << std::endl;
    std::cout << "* For Question Answering:" << std::endl;
    auto question_and_context = InputSequencePair {"Who am I?", "I am Michael from Hugging Face!"};

    auto max_length = 384;
    auto pad_id = 0;

    auto truncation_params = TruncationParams {};
    truncation_params.with_strategy(TruncationStrategy::LongestFirst).with_max_length(max_length);

    auto padding_params = PaddingParams {};
    padding_params.with_pad_id(pad_id)
        .with_fixed_length(max_length);

    tokenizer_from_string.with_truncation(truncation_params);
    tokenizer_from_string.with_padding(padding_params);

    auto input_encodings = tokenizer_from_string.encode_pair(question_and_context, true);
    std::cout << "Tokens: ";
    for(const auto &item: input_encodings.get_tokens())
        std::cout << item << " ";
    std::cout << std::endl;
    std::cout << "Ids: ";
    for(const auto &item: input_encodings.get_ids())
        std::cout << item << " ";
    std::cout << std::endl;

    return 0;
}
