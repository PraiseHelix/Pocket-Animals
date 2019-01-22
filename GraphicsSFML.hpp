#pragma once
#include "..\SGPE\Canvas.hpp"
#include <memory>
#include "..\SGPE\Graphics.hpp"
#include <SFML/Graphics.hpp>


// TODO check all includes for duplicates and iostreams

// SFML window requires the renderwindow functions
class GraphicsSFML : public Graphics
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Canvas> canvas;
public:
	GraphicsSFML(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Canvas> Canvas) :window(window), canvas(canvas) {};

	void Render() {
	};
	~GraphicsSFML() {
		
	};
};

