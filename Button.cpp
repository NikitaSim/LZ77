#include "Button.h"

Button::Button (float x, float y, float width, float height, sf::Font& font, const std::string& label)
	: normalColor(50, 150, 50), hoverColor(40, 120, 40) {
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(x, y);
	background.setFillColor(normalColor);

	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(x + width / 2.0f, y + height / 2.0f - 2);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return background.getGlobalBounds().contains(mousePos);
}

void Button::update(sf::RenderWindow& window) {
	if (isMouseOver(window)) {
		background.setFillColor(hoverColor);
	}
	else {
		background.setFillColor(normalColor);
	}
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(text);
}