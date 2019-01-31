#pragma once
#include "..\SGPE\Level.hpp"
#include "..\SGPE\GameObject.hpp"
#include "GraphicsSFML.hpp"

#include "..\BattleSystem\TimeManager.hpp"
#include "..\BattleSystem\BattleGraphics.hpp"
#include "..\BattleSystem\BattleSystem.hpp"
#include "..\BattleSystem\InterLevelData.hpp"
#include "..\BattleSystem\BattlePlayer.hpp"

class LevelBattle : public Level
{

private:
	TimeManager & timeManager;
	BattleGraphics & battleGraphics;
	std::shared_ptr <InterLevelData>  interLevelData;
	std::shared_ptr<BattlePlayer> attacker;
	std::shared_ptr<BattlePlayer> defender;
	BattleSystem & battleSystem;
	std::shared_ptr<LevelManagerPocketAnimalsSync> sync;
	std::shared_ptr<sf::RenderWindow> window;
	std::vector<GameObject*>  gameObjects;
	std::shared_ptr<GraphicsSFML> graphics;

public:


	LevelBattle(
		TimeManager & timeManager,
		BattleGraphics & battleGraphics,
		std::shared_ptr <InterLevelData> interLevelData,
		std::shared_ptr<BattlePlayer> attacker,
		std::shared_ptr<BattlePlayer> defender,
		BattleSystem & battleSystem,
		std::shared_ptr<LevelManagerPocketAnimalsSync> sync,
		std::shared_ptr<sf::RenderWindow> window,
		std::vector<GameObject*>  gameObjects,
		std::shared_ptr<GraphicsSFML> graphics) :
		Level(gameObjects, graphics),
		timeManager(timeManager),
		battleGraphics(battleGraphics),
		interLevelData(interLevelData),
		attacker(attacker),
		defender(defender),
		battleSystem(battleSystem),
		sync(sync),
		window(window), // TODO need to fix this priority level: jezus christ.
		gameObjects(gameObjects),
		graphics(graphics) {}

	void Update() {

		timeManager.onUpdate();

		// update all graphics
		window->clear();

		battleGraphics.onUpdate();

		window->display();

		// update pocketAnimals
		attacker->pocketAnimal->onUpdate();
		defender->pocketAnimal->onUpdate();

		// update the battleSystem
		battleSystem.onUpdate();



		// check for a winner:
		if (interLevelData->winner != nullptr) {
			// shared space
			sync->change(2); // previous level

		}

	};
	void Start() {

		battleSystem.onStart();
		battleGraphics.onStart();

		window->clear();
		battleGraphics.onUpdate();
		window->display();

		// should have an init function if required
	};

	void Render() {
	};

	void Close() {}

	~LevelBattle() {};
};
