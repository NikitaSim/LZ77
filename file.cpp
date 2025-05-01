#include <iostream>
#include <fstream>
#include <Windows.h>
#include "LZ77.h"
#include "file.h"

std::string compress_file(const std::string& input_path) {
	std::ifstream input_file(input_path, std::ios::binary);
	if (!input_file) return "";

	std::string content((std::istreambuf_iterator<char>(input_file)),
		std::istreambuf_iterator<char>());
	input_file.close();

	auto tokens = encode(content);

	std::string output_path = input_path + ".lz77";
	std::ofstream output_file(output_path, std::ios::binary);
	if (!output_file) return "";

	for (const auto& token : tokens) {
		output_file << token.get_offset() << " "
			<< token.get_length() << " "
			<< static_cast<int>(token.get_char()) << "\n";
	}

	return output_path;
}

std::string decompress_file(const std::string& input_path) {
	std::ifstream input_file(input_path, std::ios::binary);
	if (!input_file) return "";

	std::vector<Token> tokens;
	size_t offset, length;
	int char_code;

	while (input_file >> offset >> length >> char_code) {
		tokens.emplace_back(offset, length, static_cast<char>(char_code));
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