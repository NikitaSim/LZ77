#include <iostream>
#include <fstream>
#include "LZ77.h"
#include "file.h"

bool compress_file() {
    std::string input_path;
    std::cout << "Enter path to the file to compress: ";
    std::getline(std::cin, input_path);

    std::ifstream input_file(input_path, std::ios::binary);
    if (!input_file) {
        std::cerr << "Error: Cannot open input file!" << std::endl;
        return false;
    }

    std::string content((std::istreambuf_iterator<char>(input_file)),
        std::istreambuf_iterator<char>());
    input_file.close();

    auto tokens = encode(content);

    std::string output_path = input_path + ".lz77";
    std::ofstream output_file(output_path, std::ios::binary);
    if (!output_file) {
        std::cerr << "Error: Cannot create output file!" << std::endl;
        return false;
    }

    // Сериализация токенов с ASCII-кодами
    for (const auto& token : tokens) {
        output_file << token.get_offset() << " "
            << token.get_length() << " "
            << static_cast<int>(token.get_char()) << "\n";
    }

    output_file.close();
    std::cout << "File compressed to: " << output_path << std::endl;
    return true;
}

bool decompress_file() {
    std::string input_path;
    std::cout << "Enter path to the .lz77 file to decompress: ";
    std::getline(std::cin, input_path);

    std::ifstream input_file(input_path, std::ios::binary);
    if (!input_file) {
        std::cerr << "Error: Cannot open input file!" << std::endl;
        return false;
    }

    std::vector<Token> tokens;
    size_t offset, length;
    int next_char_code; // Читаем код символа как int

    while (input_file >> offset >> length >> next_char_code) {
        char next_char = static_cast<char>(next_char_code);
        tokens.emplace_back(offset, length, next_char);
    }

    std::string decompressed = decode(tokens);

    std::string output_path = input_path.substr(0, input_path.find_last_of('.')) + "_decompressed.txt";
    std::ofstream output_file(output_path, std::ios::binary);
    if (!output_file) {
        std::cerr << "Error: Cannot create output file!" << std::endl;
        return false;
    }

    output_file << decompressed;
    output_file.close();
    std::cout << "File decompressed to: " << output_path << std::endl;
    return true;
}