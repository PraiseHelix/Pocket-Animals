#pragma once
#include "Grid.hpp"
#include <memory>
#include "..\SGPE\Graphics.hpp"
#include <SFML/Graphics.hpp>
#include "PopUp.hpp"

/// \brief
/// Class GraphicsSFML
/// \details
/// The Graphics class is used to maintain the SFML implementation of SGPE graphics
class GraphicsSFML : public Graphics
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Canvas> canvas;
public:
	GraphicsSFML(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Canvas> canvas)
		 :Graphics(canvas), window(window), canvas(canvas){};

	/// \brief
	/// returns the shared pointer to a render window used for capturing UI elements
	std::shared_ptr<sf::RenderWindow> returnWindow() {
		return window;
	}

	/// \brief
	/// Unused due to side conjestion
	void Render() {
		
	};
	
};

