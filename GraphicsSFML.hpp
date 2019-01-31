#pragma once
#include "Grid.hpp"
#include <memory>
#include "..\SGPE\Graphics.hpp"
#include <SFML/Graphics.hpp>
#include "PopUp.hpp"

// TODO check all includes for duplicates and iostreams
// SFML window requires the renderwindow functions
class GraphicsSFML : public Graphics
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Canvas> canvas;
public:


	GraphicsSFML(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Canvas> canvas)
		 :Graphics(canvas), window(window), canvas(canvas){};

	std::shared_ptr<sf::RenderWindow> returnWindow() {
		return window;
	}

	void Render() {
		
	};
	
};

