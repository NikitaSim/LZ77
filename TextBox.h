#pragma once
#include <SFML/Graphics.hpp>

class TextBox {
private:
	sf::RectangleShape background;
	sf::Text text;
	sf::Text label;
	std::string str;
	bool isActive = false;
	bool isReadOnly;

public:
	TextBox(float, float, float, float, sf::Font&, bool);

	void setLabel(const std::string&);
	void handleEvent(sf::Event);
	void draw(sf::RenderWindow&);
	void setText(const std::string&);

	std::string getText() const { return str; }
};