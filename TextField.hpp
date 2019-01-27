#pragma once

#include "InputField.hpp"
class TextField : public InputField
{
private:
	sf::RectangleShape indicator;
public:

	TextField(
		const std::string & string,
		const sf::Vector2f & position,
		const int & charactersize,
		const sf::Font & font,
		const sf::Color & fillcolor = sf::Color::Yellow,
		const sf::Color & outlinecolor = sf::Color::Blue
	);
	void DrawSelection(std::shared_ptr<sf::RenderWindow> & window);
	void EventHandler(std::shared_ptr<sf::RenderWindow> & window);
	~TextField();
};

