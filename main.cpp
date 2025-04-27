#include <SFML/Graphics.hpp>
#include <iostream>
#include "LZ77.H"
#include "file.h"

void print_help() {
    std::cout << "Usage:\n"
        << "1. Compress file\n"
        << "2. Decompress file\n"
        << "3. Exit\n";
}


int main() {
    int choice;
    do {
        print_help();
        std::cout << "Select an option (1-3): ";
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера

        switch (choice) {
        case 1:
            compress_file();
            break;
        case 2:
            decompress_file();
            break;
        case 3:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cerr << "Invalid option!" << std::endl;
            break;
        }
    } while (choice != 3);

    return 0;
}