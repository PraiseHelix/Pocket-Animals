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
#include "LevelOpenWorldPocketAnimals.hpp"
#include "LevelManagerPocketAnimalsSync.hpp"
#include "LevelManagerPocketAnimals.hpp"


int main(int argc, char *argv[]) {

	// create window
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode{ 640, 480 }, "PocketAnimals Grid Test");


	// create game objects
	std::shared_ptr<InputHandler> inputHandler(new InputHandler());

	std::vector<sf::Keyboard::Key> keys = { sf::Keyboard::W, sf::Keyboard::Key::A, sf::Keyboard::S,sf::Keyboard::D };

	inputHandler->addKeyBindings(keys);


	std::vector<std::string> paths = { "grid.json" };

	TextureManager tex(paths);
	TileManager tiles(paths[0], tex);

	auto gridTiles = std::make_shared<Grid>(tiles, 11, 64);

	window->setFramerateLimit(30);
	window->setKeyRepeatEnabled(false);
	std::shared_ptr<GraphicsSFML> graphics = std::make_shared<GraphicsSFML>(window, gridTiles);
	int playerID = 4;
	Tile* player = new Tile{ playerID,&tex,"Player" };
	gridTiles->appendTile(player);

	gridTiles->setPlayerIndex(13);
	gridTiles->updatePlayerIndex();

	std::ifstream file("grid.json");
	nlohmann::json json;
	file >> json;
	file.close();
	nlohmann::json::array_t directions = json["data"]["grid"]["next_position"];
	gridTiles->setupMap(directions);

	Player p1(gridTiles, inputHandler);
	
	std::vector<GameObject*> gameobjectsLevelOne = {&p1};
	LevelOpenWorldPocketAnimals levelOne(gameobjectsLevelOne, graphics);
	std::shared_ptr <LevelManagerPocketAnimalsSync> sync = std::make_shared<LevelManagerPocketAnimalsSync>();


	std::vector<Level*> vlg{ &levelOne };
	LevelManagerPocketAnimals lm(vlg, sync);
	Core c1(lm);
	std::cout << "start\n";
	c1.Run();



	
	//c1.Run();
	std::cout << "Terminating application\n";
	return 0;
}

