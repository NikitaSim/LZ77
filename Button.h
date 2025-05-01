#pragma once

#include <SFML/Graphics.hpp>

class Button {

private:
	sf::RectangleShape background;
	sf::Text text;
	sf::Color normalColor;
	sf::Color hoverColor;

public:
	Button(float, float, float, float, sf::Font&, const std::string&);

	bool isMouseOver(sf::RenderWindow&);
	void update(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
};