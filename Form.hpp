#pragma once
#include "..\SGPE\Canvas.hpp"
#include <SFML\Graphics.hpp>
#include "TextField.hpp"
#include "..\SGPE\GameObject.hpp"

class Form : public Canvas {

private:
public:
	Form(){};
	void Render(std::shared_ptr<sf::RenderWindow> window);
	void Update();
	~Form();
};

