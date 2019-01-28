#pragma once
#include "Grid.hpp"
#include <memory>
#include "..\SGPE\Graphics.hpp"
#include <SFML/Graphics.hpp>


// TODO check all includes for duplicates and iostreams
// SFML window requires the renderwindow functions
class GraphicsSFMLGrid : public Graphics
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Grid> grid;
	// TODO: std::shared_ptr<Settings> settings;
public:
	GraphicsSFMLGrid(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid) :Graphics(grid), window(window), grid(grid) {};

	void Render() {
		window->clear();

		float dT = 25.f;
		grid->update(dT);
		grid->draw(window);
		window->display();
	};
};

