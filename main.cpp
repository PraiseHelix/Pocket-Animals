#pragma once


// TODO seperate includes or making including file

#include <iostream>
#include "..\SGPE\Graphics.hpp"
#include "GraphicsSFML.hpp"
#include "..\SGPE\GameObject.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "InputHandler.hpp"
#include "Grid.hpp"
#include "..\SGPE\Level.hpp"
#include "..\SGPE\SGPE.hpp"
#include "TileManager.hpp"
#include "Player.hpp"
#include "LevelPocketAnimals.hpp"
#include "LevelManagerPocketAnimals.hpp"


int main( int argc, char *argv[] ){

	// create window
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode{ 640, 480 }, "PocketAnimals Grid Test");


	// create game objects
	std::shared_ptr<InputHandler> inputHandler(new InputHandler());

	

	//std::shared_ptr<GraphicsSFML> graphics = std::make_shared<GraphicsSFML>(window, grid);


	std::vector<std::string> paths = { "grid.json" };

	TextureManager tex(paths);
	TileManager tiles(paths[0], tex);

	auto gridTiles = std::make_shared<Grid>(tiles);

	std::shared_ptr<GraphicsSFML> graphics = std::make_shared<GraphicsSFML>(window, gridTiles);


	Player p1(gridTiles, inputHandler);
	
	std::vector<GameObject*> gameobjectsLevelOne = {&p1};


	LevelPocketAnimals levelOne(gameobjectsLevelOne, graphics);



	std::vector<LevelPocketAnimals*> vlg{&levelOne};
	LevelManagerPocketAnimals lm(vlg);
	Core c1(lm);

	c1.Run();

	
	std::cout << "start\n";

	//c1.Run();
	std::cout << "Terminating application\n";
	return 0;
}

