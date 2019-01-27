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
		void ButtonAction(const sf::Keyboard::Key key) {
			sync->change(3);
			std::string one_direction = "";
			switch (key) {
			case sf::Keyboard::A:
				one_direction = "left";
				
				break;
			case sf::Keyboard::W:

				one_direction = "up";

				break;
			case sf::Keyboard::S:
				one_direction = "down";


				break;
			case sf::Keyboard::D:
				one_direction = "right";
				break;
			}



			std::cout << one_direction << std::endl;

		};
		void onUpdate() {
			auto keys = input->getKeybindings();
			if (keys.size() != 0) {
				for (auto key : keys) {
					ButtonAction(key);
				}
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


	// create game objects
	std::shared_ptr<InputHandler> inputHandler(new InputHandler());

	std::vector<sf::Keyboard::Key> keys = { sf::Keyboard::W, sf::Keyboard::Key::A, sf::Keyboard::S,sf::Keyboard::D };

	inputHandler->addKeyBindings(keys);


	std::vector<std::string> paths = { "grid.json" };

	TextureManager tex(paths);
	TileManager tiles(paths[0], tex);

	std::shared_ptr <LevelManagerPocketAnimalsSync> sync = std::make_shared<LevelManagerPocketAnimalsSync>();
	auto gridTiles = std::make_shared<Grid>(tiles, 11, 64, sync);
	auto gridTiles2 = std::make_shared<Grid>();
	window->setFramerateLimit(30);
	window->setKeyRepeatEnabled(false);
	std::shared_ptr<GraphicsSFML> graphics = std::make_shared<GraphicsSFML>(window, gridTiles);
	std::shared_ptr<GraphicsSFML> graphicsClear = std::make_shared<GraphicsSFML>(window, gridTiles2);
	int playerID = 4;
	Tile* player = new Tile{ playerID,&tex,"Player" };

	std::ifstream file("grid.json");
	nlohmann::json json;
	file >> json;
	file.close();
	nlohmann::json::array_t directions = json["data"]["grid"]["next_position"];

	gridTiles->appendTile(player);

	gridTiles->setPlayerIndex(13);
	gridTiles->updatePlayerIndex();


	gridTiles->setupMap(directions);

	Player p1(gridTiles, inputHandler);

	std::vector<sf::Keyboard::Key> key;
	key.push_back(sf::Keyboard::Key::A);


	std::shared_ptr<InputHandler> inputHandlerdu(new InputHandler());
	inputHandlerdu->addKeyBindings(key);
	InputHandlerWrapper inputHandlers(inputHandlerdu, sync);


	std::vector<GameObject*> gameobjectsLevelOne = {&p1};

	std::vector<GameObject*> wrapper = {&inputHandlers };
	FormUI StartScreen(wrapper, graphicsClear);
	LevelOpenWorldPocketAnimals OpenWorld(gameobjectsLevelOne, graphics);

	
	std::vector<Level*> RunGameEvents{ &StartScreen, &OpenWorld };
	LevelManagerPocketAnimals lm(RunGameEvents, sync);
	Core c1(lm);
	std::cout << "start\n";
	c1.Run();



	
	//c1.Run();
	std::cout << "Terminating application\n";
	return 0;
}

