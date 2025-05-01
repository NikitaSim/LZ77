#include <SFML/Graphics.hpp>
#include <iostream>
#include "LZ77.H"
#include "file.h"
#include "TextBox.h"
#include "Button.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 400), "LZ77 File Compressor");
	sf::Font font;
	if (!font.loadFromFile("Arial.ttf")) {
		return EXIT_FAILURE;
	}

	// Элементы интерфейса
	Button openFileBtn(50, 70, 150, 50, font, "Open File");
	sf::Text selectedFileText;
	selectedFileText.setFont(font);
	selectedFileText.setCharacterSize(20);
	selectedFileText.setFillColor(sf::Color::Black);
	selectedFileText.setPosition(220, 85);

	Button compressBtn(50, 150, 150, 50, font, "Compress");
	Button decompressBtn(220, 150, 150, 50, font, "Decompress");

	TextBox outputBox(50, 250, 700, 50, font, true);
	outputBox.setLabel("Output File Path:");

	sf::Text statusText;
	statusText.setFont(font);
	statusText.setCharacterSize(20);
	statusText.setFillColor(sf::Color::Red);
	statusText.setPosition(50, 320);

	std::string currentFilePath;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				bool fileOperationClicked = false;

				// Первый приоритет - кнопка открытия файла
				if (openFileBtn.isMouseOver(window)) {
					currentFilePath = OpenFileDialog();
					selectedFileText.setString(currentFilePath);
					if (!currentFilePath.empty()) {
						outputBox.setText("");
						statusText.setString("");
					}
					fileOperationClicked = true;
				}

				// Обработка кнопок сжатия/распаковки
				if (!fileOperationClicked && !currentFilePath.empty()) {
					if (compressBtn.isMouseOver(window)) {
						std::string result = compress_file(currentFilePath);
						if (!result.empty()) {
							outputBox.setText(result);
							statusText.setString("File compressed successfully!");
							statusText.setFillColor(sf::Color::Green);
						}
						else {
							statusText.setString("Error: Failed to compress file!");
							statusText.setFillColor(sf::Color::Red);
						}
					}
					else if (decompressBtn.isMouseOver(window)) {
						std::string result = decompress_file(currentFilePath);
						if (!result.empty()) {
							outputBox.setText(result);
							statusText.setString("File decompressed successfully!");
							statusText.setFillColor(sf::Color::Green);
						}
						else {
							statusText.setString("Error: Failed to decompress file!");
							statusText.setFillColor(sf::Color::Red);
						}
					}
				}
			}
		}

		// Обновление состояний кнопок
		openFileBtn.update(window);
		compressBtn.update(window);
		decompressBtn.update(window);

		// Отрисовка
		window.clear(sf::Color(240, 240, 240));
		openFileBtn.draw(window);
		window.draw(selectedFileText);
		compressBtn.draw(window);
		decompressBtn.draw(window);
		outputBox.draw(window);
		window.draw(statusText);
		window.display();
	}

	return 0;
}