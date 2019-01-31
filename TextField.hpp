#pragma once

#include <iostream>
#include "InputField.hpp"
#include "..\SGPE\GameObject.hpp"
class TextField : public GameObject
{
private:
	bool set = false;
	sf::Text text;
	// rectangle
	// shared pointers to the settings
public:

	// TODO get the appr. values
	TextField(
		const std::string & string,
		const sf::Vector2f & position,
		const sf::Font & font
	);
	
	void onUpdate() {
		// check if this object is selected
		// check if the inputHandler has your input
		// toggle set
		// call trigger
	}

	void onRender(std::shared_ptr<sf::RenderWindow> window) {
		window->draw(text);
	}

	void Trigger() {

	}
	
	~TextField();
};

