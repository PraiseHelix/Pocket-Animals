#pragma once


// TODO seperate includes or making including file

#include <iostream>
#include "Form.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <ctime>


#include <SFML/Graphics.hpp>

#include "..\SGPE\Graphics.hpp"
#include "..\SGPE\GameObject.hpp"
#include "..\SGPE\Level.hpp"
#include "..\SGPE\SGPE.hpp"

#include "GraphicsSFML.hpp"
#include "GraphicsSFMLGrid.hpp"
#include "PopUp.hpp"
#include "Player.hpp"
#include "InputHandler.hpp"
#include "Grid.hpp"
#include "TileManager.hpp"
#include "LevelOpenWorldPocketAnimals.hpp"
#include "LevelManagerPocketAnimals.hpp"

#include "LevelManagerPocketAnimalsSync.hpp"
#include "FormUI.hpp"
#include "BattleLevel.hpp"

#include "..\BattleSystem\Effect.hpp"
#include "..\BattleSystem\Move.hpp"
#include "..\BattleSystem\Item.hpp"
#include "..\BattleSystem\PocketAnimal.hpp"
#include "..\BattleSystem\BattlePlayer.hpp"
#include "..\BattleSystem\BattleSystem.hpp"
#include "..\BattleSystem\PocketAnimalVisualisation.hpp"
#include "..\BattleSystem\BattleGraphics.hpp"
#include "..\BattleSystem\TimeManager.hpp"
#include "..\BattleSystem\Animation.hpp"


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




	// creation of effects:
	Effect effects[] = {
		Effect(Effect::EffectType::Multiply, 2, 1), // effect for healing
		Effect(Effect::EffectType::Add, -10, -20), // effect for normal attack
		Effect(Effect::EffectType::Add, -20, -30), // effect for large attack
		Effect(Effect::EffectType::Add, 100, 100) // restore 100 health
	};

	// creation of items
	Item items[] = {
		Item("Mend", 1, &effects[0]),
		Item("Mend the second", 1, &effects[3])
	};

	// creation of moves:
	Move moves[] = {
		Move("normal attack", 1, 0, &effects[1], 1, 1), // move for normal attack
		Move("large attack", 2, 2, &effects[2], 1, 2), // move for large attack
		Move("SUPER HEAL", 3, 8, nullptr, 0, 0, &effects[3], 1, 1) // move for restoring health
	};

	// creation of pocketAnimals
	// >attacker animation
	sf::Texture attackerIdleFrames = sf::Texture();
	attackerIdleFrames.loadFromFile("Bob_pocketAnimal.png");
	std::shared_ptr<Animation> attackerIdleAnimation = std::make_shared<Animation>(attackerIdleFrames, 128, 0.5f, true, true);
	PocketAnimalVisualisation attackerVisualisation = PocketAnimalVisualisation(attackerIdleAnimation, attackerIdleAnimation, attackerIdleAnimation);
	PocketAnimal attackerPocketAnimal(moves, 3, "Aggressor", 1, 100.0f, attackerVisualisation);

	// >defender animation
	sf::Texture defenderIdleFrames = sf::Texture();
	defenderIdleFrames.loadFromFile("hans_pocketAnimal.png");
	std::shared_ptr<Animation> defenderIdleAnimation = std::make_shared<Animation>(defenderIdleFrames, 128, 0.5f, true, true);
	PocketAnimalVisualisation defenderVisualisation = PocketAnimalVisualisation(defenderIdleAnimation, defenderIdleAnimation, defenderIdleAnimation);
	PocketAnimal defenderPocketAnimal(moves, 3, "Defender", 2, 100.0f, defenderVisualisation);
	// creation of the players
	std::shared_ptr<BattlePlayer> attacker = std::make_shared<BattlePlayer>("Bob the attacker", 0, &attackerPocketAnimal, items, 2, false);
	std::shared_ptr<BattlePlayer> defender = std::make_shared<BattlePlayer>("Hans the defender", 1, &defenderPocketAnimal, items, 2);

	// creation of interlevel data
	InterLevelData interLevelData = InterLevelData(attacker, defender);


	sf::Texture backgroundTexture = sf::Texture();
	backgroundTexture.loadFromFile("Background.png");
	std::shared_ptr<sf::Texture> buttonPressedText = std::make_shared<sf::Texture>();
	buttonPressedText->loadFromFile("Button_pressed.png");
	std::shared_ptr<sf::Texture> buttonReleasedText = std::make_shared<sf::Texture>();
	buttonReleasedText->loadFromFile("Button_released.png");
	sf::Font arialFont = sf::Font();
	arialFont.loadFromFile("calibri.ttf");
	sf::Text defaultButtonText = sf::Text("", arialFont, 15);

	BattleGraphics battleGraphics = BattleGraphics(window, interLevelData, backgroundTexture, buttonReleasedText, buttonPressedText, defaultButtonText);

	// creation of the battleSystem
	BattleSystem battleSystem = BattleSystem(interLevelData, battleGraphics);
	battleGraphics.setItemButtonListener(&battleSystem);
	battleGraphics.setMoveButtonListener(&battleSystem);

	// timeManager to keep track of time
	TimeManager timeManager = TimeManager();

	//CommandLineOutputManager output = CommandLineOutputManager(battleSystem);

	srand(static_cast<unsigned>(time(0)));



	
	// create game the listener for the start screen
	std::shared_ptr<InputHandler> inputHandler(new InputHandler());
	std::vector<sf::Keyboard::Key> keys = { sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D};
	inputHandler->addKeyBindings(keys);



	// Initialising the tiles
	std::vector<std::string> paths = { "grid.json" };
	TextureManager tex(paths);
	TileManager tiles(paths[0], tex);

	std::shared_ptr <LevelManagerPocketAnimalsSync> sync = std::make_shared<LevelManagerPocketAnimalsSync>();
	
	

	// setting the start up menu
	std::shared_ptr<InputHandler> ContinueInputHandler(new InputHandler());
	std::vector<sf::Keyboard::Key> key;
	key.push_back(sf::Keyboard::Key::Space);
	key.push_back(sf::Keyboard::Key::Return);
	ContinueInputHandler->addKeyBindings(key);
	InputHandlerWrapper inputHandlers(ContinueInputHandler, sync);

	std::shared_ptr<PopUp> dialog = std::make_shared<PopUp>(ContinueInputHandler);
	auto gridTiles = std::make_shared<Grid>(tiles, 11, 64, sync, dialog);
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





	std::vector<GameObject*> wrapper = {&inputHandlers};
	FormUI StartScreen(wrapper, graphicsClear);


	std::vector<GameObject*> gameobjectsLevelOne = { &p1 };
	std::vector<GameObject*> empty = {  };

	LevelOpenWorldPocketAnimals OpenWorld(gameobjectsLevelOne, graphics);


	BattleLevel battleLevel(timeManager,
		battleGraphics,
		interLevelData,
		attacker,
		defender,
		battleSystem,
		sync,
		window,
		empty,
		graphicsClear);

	
	std::vector<Level*> RunGameEvents{&StartScreen, &OpenWorld, &battleLevel};
	
	// level manager wants the level and a way to sync with them
	LevelManagerPocketAnimals lm(RunGameEvents, sync);
	Core c1(lm);
	std::cout << "start\n";

	while (window->isOpen()) {

		sf::Event event;
		while (window->pollEvent(event))
		{
			c1.Update();
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				window->close();
			}

		}

	}
	


	
	//c1.Run();
	std::cout << "Terminating application\n";
	return 0;
}

