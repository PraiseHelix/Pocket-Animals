#pragma once
#include "..\SGPE\Graphics.hpp"
#include "..\SGPE\Canvas.hpp"

#include <SFML/Graphics.hpp>
#include <memory>


// TODO check all includes for duplicates and iostreams

// SFML window requires the renderwindow functions
class GraphicsSFML : public Graphics
{
private:
	std::shared_ptr<sf::Window> window;
	std::shared_ptr<Canvas> canvas;
public:
	GraphicsSFML(std::shared_ptr<sf::Window> window, std::shared_ptr<Canvas> Canvas) :window(window), canvas(canvas) {};

	void Render() {
	};
	~GraphicsSFML() {

	};
};

