#include "TextBox.h"
#include <string>

TextBox::TextBox(float x, float y, float width, float height, sf::Font& font, bool readOnly = false)
	: isReadOnly(readOnly) {
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(x, y);
	background.setFillColor(sf::Color::White);
	background.setOutlineThickness(2);
	background.setOutlineColor(sf::Color(128, 128, 128));

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(x + 10, y + 5);

	label.setFont(font);
	label.setCharacterSize(20);
	label.setFillColor(sf::Color(70, 70, 70));
	label.setPosition(x + 5, y - 25);
}

void TextBox::setLabel(const std::string& text) {
	label.setString(text);
}

void TextBox::handleEvent(sf::Event event) {
	if (isReadOnly) return;

	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		if (background.getGlobalBounds().contains(mousePos)) {
			isActive = true;
			background.setOutlineColor(sf::Color::Blue);
		}
		else {
			isActive = false;
			background.setOutlineColor(sf::Color(128, 128, 128));
		}
	}

	if (isActive && event.type == sf::Event::TextEntered) {
		if (event.text.unicode == '\b') {
			if (!str.empty()) str.pop_back();
		}
		else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n') {
			str += static_cast<char>(event.text.unicode);
		}
		text.setString(str);
	}
}

void TextBox::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(text);
	window.draw(label);
}

void TextBox::setText(const std::string& s) {
	str = s;
	text.setString(str);
}