#include <iostream>
#include <fstream>
#include <sstream>
#include <tokenizers-cpp/tokenizer.h>

using namespace huggingface::tokenizers;

void test_tokenizer(Tokenizer& tokenizer) {
    auto encodings =  tokenizer.encode("HuggingFace is great!", true);
    std::cout << "Encoding: 'HuggingFace is great!' -> " << encodings->len() << " tokens:" << std::endl;
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

    std::cout << std::endl;
    std::cout << "* By loading from the Huggingface Hub:" << std::endl;
    auto tokenizer_from_hub = Tokenizer::from_pretrained("bert-base-uncased");
    test_tokenizer(tokenizer_from_hub);

    return 0;
}
