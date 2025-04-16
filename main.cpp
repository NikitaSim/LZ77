#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct LZ77_Token {
    size_t offset;
    size_t length;
    char next_char;
};

std::vector<LZ77_Token> encode(const std::string&, size_t ,size_t);

int main()
{
   
    std::string text = "ABABABABABBABABBABABABABABBAABABBABAAABABAABABABABABBABABABABAB";
    std::string zipText = "";


    return 0;
}

std::vector<LZ77_Token> encode(const std::string& text, size_t window_size = 4096, size_t lookahead = 16) {

    std::vector<LZ77_Token> tokens;
    size_t pos = 0;

    while (pos < text.size()) {
        size_t best_offset = 0;
        size_t best_length = 0;
        char best_char = text[pos];

        size_t search_start = (pos > window_size) ? pos - window_size : 0;
        size_t max_pos = (pos + lookahead > text.size()) ? text.size() : pos + lookahead;// min(pos + lookahead, input.size());

        for (size_t i = search_start; i < pos; i++) {
            size_t j;
            while(pos+j < max_pos && text[i + j] == text[pos + j]) {
                j++;
                if (i + j >= pos) break; // Не выходить за пределы словаря
            }
        }
    }

}