#pragma once
#include <SFML\Graphics.hpp>

class Field: public sf::Text {
public:
	//Field() = 0;
	virtual void onRender() = 0;
	//~Field();
};

