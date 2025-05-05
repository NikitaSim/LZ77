#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdint>
#include "LZ77.h"
#include "file.h"

#pragma pack(push,1)
struct BinaryToken {
	uint16_t offset; 
	uint8_t length;  
	char next_char;
};
#pragma pack(pop)

std::string compress_file(const std::string& input_path) {
	std::ifstream input_file(input_path, std::ios::binary);
	if (!input_file) return "";

	std::string content((std::istreambuf_iterator<char>(input_file)),
		std::istreambuf_iterator<char>());
	input_file.close();

	auto tokens = encode(content);

	// Проверка эффективности сжатия
	const size_t compressed_size = tokens.size() * sizeof(BinaryToken);
	if (compressed_size >= content.size()) {
		return "";
	}

	std::string output_path = input_path + ".lz77";
	std::ofstream output_file(output_path, std::ios::binary);
	if (!output_file) return "";

	for (const auto& token : tokens) {
		if (token.get_offset() > 65535 || token.get_length() > 255) {
			return "";
		}
		BinaryToken bin_token{
			token.get_offset(),
			token.get_length(),
			token.get_char()
		};
		output_file.write(reinterpret_cast<const char*>(&bin_token), sizeof(bin_token));
	}

	return output_path;
}

std::string decompress_file(const std::string& input_path) {
	std::ifstream input_file(input_path, std::ios::binary);
	if (!input_file) return "";

	std::vector<Token> tokens;
	BinaryToken bin_token;

	while (input_file.read(reinterpret_cast<char*>(&bin_token), sizeof(BinaryToken))) {
		tokens.emplace_back(
			bin_token.offset,
			bin_token.length,
			bin_token.next_char
		);
	}

	if (!input_file.eof() && input_file.fail()) {
		return "";
	}

	std::string decompressed;
	try {
		decompressed = decode(tokens);
	}
	catch (...) {
		return "";
	}

	size_t ext_pos = input_path.find(".lz77");
	std::string output_path = input_path.substr(0, ext_pos) + "_decompressed.txt";

	std::ofstream output_file(output_path, std::ios::binary);
	if (!output_file) return "";

	output_file << decompressed;
	output_file.close();
	return output_path;
}

std::string OpenFileDialog() {
	OPENFILENAMEA ofn;
	char szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All Files\0*.*\0\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE) {
		return ofn.lpstrFile;
	}
	return "";
}