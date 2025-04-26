#include <SFML/Graphics.hpp>
#include <iostream>
#include "LZ77.H"

std::vector<Token> encode(const std::string&);
std::string decode(const std::vector<Token>&);

int main() {

	std::string text = "Flash memory is a type of non-volatile memory that can be electronically erased and reprogrammed.";
	std::string decode_text;
	std::vector<Token> token_text;

	try {
		token_text = encode(text);
		decode_text = decode(token_text);
	}

	catch (const std::exception& error) {
		std::cout << error.what() << std::endl;
		return 1;	
	}

	print_tokens(token_text);
	std::cout << decode_text<<std::endl;

	if (decode_text == text) {
		std::cout << "texts are same" << std::endl;
	}
	else {
		std::cout << "text not same" << std::endl;
	}

	std::cout <<"original size: " << text.size() << '\n' <<"encoded size: " << token_text.size() << std::endl;
	return 0;
}