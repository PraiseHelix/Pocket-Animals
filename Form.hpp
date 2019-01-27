#pragma once
#include "..\SGPE\Canvas.hpp"
#include <SFML\Graphics.hpp>
#include "TextField.hpp"
class Form : public Canvas {

private:
	sf::Text title;
	std::vector<std::shared_ptr<TextField>> options;
	unsigned int selected_option_index;
public:
	Form();
	void Render(std::shared_ptr<sf::RenderWindow> window);
	void Update(std::shared_ptr<sf::RenderWindow> window);
	~Form();
};

