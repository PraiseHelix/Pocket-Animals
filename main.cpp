#pragma once


// TODO seperate includes or making including file

#include <iostream>
#include "Form.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>


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
#include "Tracking.hpp"
#include "Battle.hpp"

#include "LevelOpenWorldPocketAnimals.hpp"
#include "LevelManagerPocketAnimals.hpp"
#include "LevelManagerPocketAnimalsSync.hpp"
#include "LevelFormUI.hpp"
#include "LevelBattle.hpp"

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
#include "..\BattleSystem\MoveVisualisation.hpp"

static unsigned int width;
static unsigned int tileSize;

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

//Deze functie leest de spelers index uit een save file
unsigned int readIndex(std::string saveFile) {
	std::ifstream file(saveFile);
	nlohmann::json J;
	file >> J;
	return J["data"]["player"]["position"];
}

//Deze funtie slaat de spelers index op in een save file
//De JSON structuur is echter alfabetisch geordend.
void saveIndex(unsigned int index, std::string saveFile) {
	std::ifstream in(saveFile);
	nlohmann::json J;
	in >> J;
	in.close();

	std::ofstream out(saveFile, std::ios::ate);
	J["data"]["player"]["position"] = index;
	out << std::setw(4) << J;
	out.close();
}


int main(int argc, char *argv[]) {

	
	// create window
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode{ 640, 480 }, "PocketAnimals Grid Test");

	// creation of effects:
	Effect effects[] = {
		Effect(Effect::EffectType::Multiply, 2, 1), // effect for healing
		Effect(Effect::EffectType::Add, -20, -40), // effect for normal attack
		Effect(Effect::EffectType::Add, -40, -60), // effect for large attack
		Effect(Effect::EffectType::Add, 100, 100) // restore 100 health
	};

	// creation of items
	Item items[] = {
		Item("Mend", 1, &effects[0]),
		Item("Mend", 1, &effects[0]),
		Item("Heal PocketAnimal", 1, &effects[0])
	};

	sf::Texture simpleProjectileFrames = sf::Texture();
	simpleProjectileFrames.loadFromFile("SimpleProjectile.png");
	std::shared_ptr<Animation> simpleProjectileAnimation = std::make_shared<Animation>(simpleProjectileFrames, 128, 0.5f, true);

	sf::Texture simpleExplosionFrames = sf::Texture();
	simpleExplosionFrames.loadFromFile("SimpleExplosion.png");
	std::shared_ptr<Animation> simpleExplosionAnimation = std::make_shared<Animation>(simpleExplosionFrames, 128, 1.0f);

	std::shared_ptr<MoveVisualisation> attackMoveVisualisation = std::make_shared< MoveVisualisation>(false, 180.0f, simpleProjectileAnimation, simpleExplosionAnimation);

	sf::Texture sparksFrames = sf::Texture();
	sparksFrames.loadFromFile("Sparks.png");
	std::shared_ptr<Animation> sparksAnimation = std::make_shared<Animation>(sparksFrames, 128, 1.0f);

	std::shared_ptr<MoveVisualisation> healMoveVisualisation = std::make_shared< MoveVisualisation>(true, 1.0f, sparksAnimation, sparksAnimation);

	// creation of moves:
	Move moves[] = {
		Move("normal attack", 1, 0, attackMoveVisualisation, &effects[1], 1, 1), // move for normal attack
		Move("large attack", 2, 2, attackMoveVisualisation, &effects[2], 1, 2), // move for large attack
		Move("SUPER HEAL", 3, 8, healMoveVisualisation, nullptr, 0, 0, &effects[3], 1, 1) // move for restoring health
	};

	// creation of pocketAnimals
	// >attacker animation
	sf::Texture attackerIdleFrames = sf::Texture();
	attackerIdleFrames.loadFromFile("Bob_pocketAnimal.png");
	std::shared_ptr<Animation> attackerIdleAnimation = std::make_shared<Animation>(attackerIdleFrames, 128, 0.5f, true, true);

	sf::Texture attackerAttackFrames = sf::Texture();
	attackerAttackFrames.loadFromFile("Bob_pocketAnimal_attack.png");
	std::shared_ptr<Animation> attackerAttackAnimation = std::make_shared<Animation>(attackerAttackFrames, 128, 0.5f);

	std::shared_ptr<Animation> attackerWinAnimation = std::make_shared<Animation>(attackerAttackFrames, 128, 0.5f, true);

	sf::Texture attackerDeathFrames = sf::Texture();
	attackerDeathFrames.loadFromFile("Bob_pocketAnimal_death.png");
	std::shared_ptr<Animation> attackerDeathAnimation = std::make_shared<Animation>(attackerDeathFrames, 128, 0.8f);

	PocketAnimalVisualisation attackerVisualisation = PocketAnimalVisualisation(attackerIdleAnimation, attackerAttackAnimation, attackerAttackAnimation, attackerDeathAnimation, attackerWinAnimation);
	PocketAnimal attackerPocketAnimal(moves, 3, "Aggressor", 1, 100.0f, attackerVisualisation);

	// >defender animation
	sf::Texture defenderIdleFrames = sf::Texture();
	defenderIdleFrames.loadFromFile("hans_pocketAnimal.png");
	std::shared_ptr<Animation> defenderIdleAnimation = std::make_shared<Animation>(defenderIdleFrames, 128, 0.5f, true, true);

	sf::Texture defenderAttackFrames = sf::Texture();
	defenderAttackFrames.loadFromFile("hans_pocketAnimal_attack.png");
	std::shared_ptr<Animation> defenderAttackAnimation = std::make_shared<Animation>(defenderAttackFrames, 128, 0.5f, true, true);

	sf::Texture defenderDeathFrames = sf::Texture();
	defenderDeathFrames.loadFromFile("hans_pocketAnimal_death.png");
	std::shared_ptr<Animation> defenderDeathAnimation = std::make_shared<Animation>(defenderDeathFrames, 128, 0.8f);

	PocketAnimalVisualisation defenderVisualisation = PocketAnimalVisualisation(defenderIdleAnimation, defenderAttackAnimation, defenderAttackAnimation, defenderDeathAnimation, defenderAttackAnimation);
	PocketAnimal defenderPocketAnimal(moves, 3, "Defender", 2, 100.0f, defenderVisualisation);
	// creation of the players
	std::shared_ptr<BattlePlayer> attacker = std::make_shared<BattlePlayer>("Bob the attacker", 0, &attackerPocketAnimal, items, 3, false);
	std::shared_ptr<BattlePlayer> defender = std::make_shared<BattlePlayer>("Hans the defender", 1, &defenderPocketAnimal, items, 3);

	// creation of interlevel data
	std::shared_ptr<InterLevelData> interLevelData = std::make_shared<InterLevelData>(attacker, defender);

	// creation of battleGraphics

	sf::Texture backgroundTexture = sf::Texture();
	backgroundTexture.loadFromFile("Background.png");
	std::shared_ptr<sf::Texture> buttonPressedText = std::make_shared<sf::Texture>();
	buttonPressedText->loadFromFile("Button_pressed.png");
	std::shared_ptr<sf::Texture> buttonReleasedText = std::make_shared<sf::Texture>();
	buttonReleasedText->loadFromFile("Button_released.png");
	sf::Font arialFont = sf::Font();
	arialFont.loadFromFile("arial.ttf");
	sf::Text defaultButtonText = sf::Text("", arialFont, 15);

	BattleGraphics battleGraphics = BattleGraphics(window, interLevelData, backgroundTexture, buttonReleasedText, buttonPressedText, defaultButtonText);

	// creation of the battleSystem
	BattleSystem battleSystem = BattleSystem(interLevelData, battleGraphics);
	battleGraphics.setItemButtonListener(&battleSystem);
	battleGraphics.setMoveButtonListener(&battleSystem);

	// timeManager to keep track of time
	TimeManager timeManager = TimeManager();
	srand(static_cast<unsigned>(time(0)));


	// PlayerProgress
	std::shared_ptr<PlayerProgress> pg = std::make_shared<PlayerProgress>();

	std::vector<std::string> WaterLeaderLines;
	WaterLeaderLines.push_back("Yeeet yeet!");
	WaterLeaderLines.push_back("HA YOU DARE CHALLENGE ME yeet!");
	WaterLeaderLines.push_back("We might, but only....");
	WaterLeaderLines.push_back("After you've YEET err fought");
	WaterLeaderLines.push_back("4 of those YEETING PocketAnimals");
	WaterLeaderLines.push_back("Also a random STONE..?");
	WaterLeaderLines.push_back("...for CANONICAL reasons.");
	WaterLeaderLines.push_back("Yeeet yeet!");
	WaterLeader npcW(pg, WaterLeaderLines, 0);


	std::vector<std::string> FireLeaderLines;
	FireLeaderLines.push_back("So... what do you want?");
	FireLeaderLines.push_back("You wanna fight??");
	FireLeaderLines.push_back("That's a nice conversation..");
	FireLeaderLines.push_back("starter you got there my friend");
	FireLeaderLines.push_back("But first.. I need..");
	FireLeaderLines.push_back("A FIRE EXTINGUISHER ");
	FireLeaderLines.push_back("...for CANONICAL reasons.");
	FireLeaderLines.push_back("Go find it and report back.");
	FireLeader npcFire(pg, FireLeaderLines, 1);

	std::vector<std::string> FlightLeaderLines;
	FlightLeaderLines.push_back("......");
	FlightLeaderLines.push_back(".....wait.");
	FlightLeaderLines.push_back("You're not Dave...?");
	FlightLeaderLines.push_back("Where's Dave?");
	FlightLeaderLines.push_back("What's your deal?");
	FlightLeaderLines.push_back("FIGHT??? WHY?");
	FlightLeaderLines.push_back("We'll I'm busy.");
	FlightLeaderLines.push_back("WELL EXCUSE ME PRINCESS");
	FlightLeaderLines.push_back("If you find my CAR KEYS");
	FlightLeaderLines.push_back("I might find some time");
	FlightLeaderLines.push_back("For your passive...");
	FlightLeaderLines.push_back(".. aggresive highness.");
	FlightLeaderLines.push_back("Wait you have fought");
	FlightLeaderLines.push_back("10 PocketAnimals right?");
	FlightLeader npcFlight(pg, FlightLeaderLines, 2);

	std::vector<std::string> LandLeaderLines;
	LandLeaderLines.push_back("Hey.. come here often?");
	LandLeaderLines.push_back(".....wait.");
	LandLeaderLines.push_back("How old are you?");
	LandLeaderLines.push_back("12????");
	LandLeaderLines.push_back("Hey you know what they say");
	LandLeaderLines.push_back("If her age is on the clock");
	LandLeaderLines.push_back("Wait nevermind...");
	LandLeaderLines.push_back("Why are you here...?");
	LandLeaderLines.push_back("Oh you wanna fight?");
	LandLeaderLines.push_back("It'll cost you tho. ");
	LandLeaderLines.push_back("One SWITCH BLADE.");
	LandLeaderLines.push_back("None of your business..");
	LandLeaderLines.push_back("But if you haven't fought");
	LandLeaderLines.push_back("8 PocketAnimals");
	LandLeaderLines.push_back("Don't come back.");
	LandLeader npcLand(pg, LandLeaderLines, 3);

	std::vector<std::string> EndLeaderLines;
	LandLeaderLines.push_back("Hehehe sure.");
	EndBoss endBoss(pg, LandLeaderLines, 4);



	std::vector<NPCLeader*> leaders = { &npcW, &npcLand, &npcFire, &npcFlight, &endBoss };

	// leader
	std::shared_ptr<NPCTracker> tracker = std::make_shared<NPCTracker>(leaders);


	
	// create game the listener for the start screen
	std::shared_ptr<InputHandler> inputHandler(new InputHandler());
	std::vector<sf::Keyboard::Key> keys = { sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D};
	inputHandler->addKeyBindings(keys);


	std::string filename = "grid.json";

	std::ifstream file(filename);
	nlohmann::json json;
	file >> json;
	file.close();

	width = json["data"]["grid"]["width"];
	auto tmpTileID = json["data"]["grid"]["gfx"][0]["0"];
	tileSize = static_cast<unsigned int>(tmpTileID["scale"][0]) * static_cast<unsigned int>(tmpTileID["size"][0]);


	// Initialising the tiles
	std::vector<std::string> paths = { "grid.json" };
	TextureManager tex(paths);
	TileManager tiles(paths[0], tex, width, tileSize);

	std::shared_ptr <LevelManagerPocketAnimalsSync> sync = std::make_shared<LevelManagerPocketAnimalsSync>();
	
	

	// setting the start up menu
	std::shared_ptr<InputHandler> ContinueInputHandler(new InputHandler());
	std::vector<sf::Keyboard::Key> key;
	key.push_back(sf::Keyboard::Key::Space);
	key.push_back(sf::Keyboard::Key::Return);
	ContinueInputHandler->addKeyBindings(key);
	InputHandlerWrapper inputHandlers(ContinueInputHandler, sync);



	std::shared_ptr<InputHandler> EmptyHandler(new InputHandler());
	std::vector<sf::Keyboard::Key> nokeys;
	EmptyHandler->addKeyBindings(nokeys);
	

	//Width = 56, tilSize = 64
	std::shared_ptr<PopUp> dialog = std::make_shared<PopUp>(ContinueInputHandler);
	auto gridTiles = std::make_shared<Grid>(tiles, width, tileSize, sync, dialog, tracker, pg, interLevelData, attacker);
	auto startForm = std::make_shared<Form>();
	std::shared_ptr<GraphicsSFMLGrid> graphics = std::make_shared<GraphicsSFMLGrid>(window, gridTiles);
	std::shared_ptr<GraphicsSFML> graphicsClear = std::make_shared<GraphicsSFML>(window, startForm);

	int playerID = 71;
	auto uniqueTile = tiles.getUniqueTiles();
	Tile* player = new Tile{ playerID,uniqueTile[playerID] };
	uniqueTile[playerID]->appendSprite(&player->m_sprite);
	uniqueTile[playerID]->setupSpriteTable(std::to_string(playerID));
	uniqueTile[playerID]->setAnimation("Player", true, true);

	nlohmann::json::array_t directions = json["data"]["grid"]["next_position"];

	gridTiles->appendTile(player);

	gridTiles->setPlayerIndex(13);
	gridTiles->updatePlayerIndex();
	gridTiles->setupMap(directions);

	unsigned int initIndex = readIndex("save.json");
	gridTiles->setPlayerPosition(gridTiles->convertIndextoCoords(initIndex));
	gridTiles->setPlayerIndex(initIndex);

	Player p1(gridTiles, inputHandler);

	

	std::vector<GameObject*> wrapper = {&inputHandlers};

	LevelFormUI StartScreen(wrapper, graphicsClear);


	std::vector<GameObject*> gameobjectsLevelOne = { &p1 };
	std::vector<GameObject*> empty = {  };

	LevelOpenWorldPocketAnimals OpenWorld(gameobjectsLevelOne, graphics);


	LevelBattle battleLevel(timeManager,
		battleGraphics,
		interLevelData,
		attacker,
		defender,
		battleSystem,
		sync,
		window,
		empty,
		graphicsClear);
	
	// TODO: level independent
	std::vector<Level*> RunGameEvents{ &StartScreen, &OpenWorld, &battleLevel};
	
	// level manager wants the level and a way to sync with them
	LevelManagerPocketAnimals lm(RunGameEvents, sync);
	Core c1(lm);
	std::cout << "start\n";
	
	while(window->isOpen()) {
		c1.Update();
		sf::Event event;

		while (window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				window->close();
				saveIndex(gridTiles->getPlayerIndex(), "save.json");
			}
			// catch the resize events
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, float(event.size.width), float(event.size.height));
				window->setView(sf::View(visibleArea));
			}


		}
	}


	//c1.Run();
	std::cout << "Terminating application\n";
	return 0;
}

