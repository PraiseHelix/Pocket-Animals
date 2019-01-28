#pragma once


// TODO seperate includes or making including file

#include <iostream>
#include "..\SGPE\Graphics.hpp"
#include "GraphicsSFML.hpp"
#include "GraphicsSFMLGrid.hpp"
#include "Form.hpp"
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
#include "FormUI.hpp"
#include "LevelManagerPocketAnimals.hpp"


class InputHandlerWrapper : public GameObject {

	private:
		// TODO gameobject id
		std::shared_ptr<InputHandler> input;
		std::shared_ptr<LevelManagerPocketAnimalsSync> sync;

	public:
		InputHandlerWrapper(std::shared_ptr<InputHandler> input, std::shared_ptr<LevelManagerPocketAnimalsSync> sync): input(input), sync(sync) {};
		~InputHandlerWrapper() {};
		void onUpdate() {
			auto keys = input->getKeybindings();
			if (keys.size() != 0) {
				sync->change(3);
			}
		};
		void onCall() {};
		void onStart() {};
		void onCollision() {};
		void onInteract() {};

	};
int main(int argc, char *argv[]) {

	// create window
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode{ 640, 480 }, "PocketAnimals Grid Test");


	// create game the listener for the start screen
	std::shared_ptr<InputHandler> inputHandler(new InputHandler());
	std::vector<sf::Keyboard::Key> keys = { sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D};
	inputHandler->addKeyBindings(keys);



	// Initialising the tiles
	std::vector<std::string> paths = { "grid.json" };
	TextureManager tex(paths);
	TileManager tiles(paths[0], tex);

	std::shared_ptr <LevelManagerPocketAnimalsSync> sync = std::make_shared<LevelManagerPocketAnimalsSync>();
	auto gridTiles = std::make_shared<Grid>(tiles, 11, 64, sync);
	auto startForm = std::make_shared<Form>();
	
	std::shared_ptr<GraphicsSFMLGrid> graphics = std::make_shared<GraphicsSFMLGrid>(window, gridTiles);
	std::shared_ptr<GraphicsSFML> graphicsClear = std::make_shared<GraphicsSFML>(window, startForm);

	int playerID = 4;
	Tile* player = new Tile{ playerID,&tex,"Player" };

	std::string filename= "grid.json";

	std::ifstream file(filename);
	nlohmann::json json;
	file >> json;
	file.close();
	nlohmann::json::array_t directions = json["data"]["grid"]["next_position"];

	gridTiles->appendTile(player);

	gridTiles->setPlayerIndex(13);
	gridTiles->updatePlayerIndex();
	gridTiles->setupMap(directions);

	Player p1(gridTiles, inputHandler);




	// setting the start up menu
	std::shared_ptr<InputHandler> inputHandlerdu(new InputHandler());
	std::vector<sf::Keyboard::Key> key;
	key.push_back(sf::Keyboard::Key::Space);
	key.push_back(sf::Keyboard::Key::Return);
	inputHandlerdu->addKeyBindings(key);
	InputHandlerWrapper inputHandlers(inputHandlerdu, sync);


	std::vector<GameObject*> wrapper = {&inputHandlers };
	FormUI StartScreen(wrapper, graphicsClear);


	std::vector<GameObject*> gameobjectsLevelOne = { &p1 };
	LevelOpenWorldPocketAnimals OpenWorld(gameobjectsLevelOne, graphics);

	
	std::vector<Level*> RunGameEvents{ &StartScreen, &OpenWorld };

	// level manager wants the level and a way to sync with them
	LevelManagerPocketAnimals lm(RunGameEvents, sync);
	Core c1(lm);
	std::cout << "start\n";
	c1.Run();



	
	//c1.Run();
	std::cout << "Terminating application\n";
	return 0;
}

