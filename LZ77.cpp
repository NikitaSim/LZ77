#include <iostream>
#include <algorithm>
#include <cstdint>
#include "LZ77.h"

std::vector<Token> encode(const std::string& text) {
	const size_t window_size = 4096;  // 4KB
	const size_t lookahead = 18;	//5
	std::vector<Token> tokens;
	size_t pos = 0;
	const size_t size_text = text.size();

	while (pos < size_text) {
		uint16_t best_offset = 0;
		uint8_t best_length = 0;
		char best_char = text[pos];
		
		// Границы окна истории
		const size_t search_start = (pos > window_size) ? pos - window_size : 0;
		const size_t max_length = std::min(lookahead, size_text - pos);

		// Корректный перебор в окне истории
		for (size_t i = search_start; i < pos; ++i) {
			size_t current_length = 0;
			// Сравниваем символы, не выходя за пределы окна и текста
			while (current_length < max_length &&
				(i + current_length) < pos &&       // Не выходим за пределы окна истории
				(pos + current_length) < size_text && // Не выходим за строку
				text[i + current_length] == text[pos + current_length]) {
				current_length++;
			}

			if (current_length > best_length) {
				best_offset = static_cast<uint16_t>(pos - i);
				best_length = static_cast<uint8_t>(current_length);
				best_char = (pos + best_length < size_text) ? text[pos + best_length] : '\0';
			}
		}

		tokens.push_back(Token(best_offset, best_length, best_char));
		pos += (best_length > 0) ? best_length + 1 : 1;
	}

	return tokens;
}

std::string decode(const std::vector<Token>& tokens) {
	std::string text;

	for (const Token& token : tokens) {
		if (token.get_length() > 0) {
			//std::cout<<"text "<< text << std::endl;
			if (token.get_offset() > text.size() || token.get_offset() == 0) {
				throw std::runtime_error("Invalid offset in token");
			}
			const size_t copy_pos = text.size() - token.get_offset();
			for (size_t i = 0; i < token.get_length(); i++) {
				//std::cout <<"text[i] " << text[copy_pos + (i % token.get_offset())] << std::endl;
				text += text[copy_pos + i];
			}
		}

		if (token.get_char() != '\0') {
			text += token.get_char();
		}
	}

	return text;

}

void print_tokens(const std::vector<Token>& tokens) {
	for (const Token& tok : tokens) {
		std::cout << "(" << tok.get_offset() << "," << tok.get_length() << ",";
		if (std::isprint(tok.get_char())) {
			std::cout << tok.get_char();
		}
		else {
			std::cout << "\\0";
		}
		std::cout << ") ";
	}
	std::cout << std::endl;
}