#pragma once
#include "..\SGPE\Level.hpp"
#include "GraphicsSFMLGrid.hpp"
class LevelOpenWorldPocketAnimals : public Level
{
private:
	bool loop = true;
	std::vector<GameObject*>  gameObjects;
	std::shared_ptr<GraphicsSFMLGrid> graphics;

public:
	LevelOpenWorldPocketAnimals(std::vector<GameObject*> gameObjects, std::shared_ptr<GraphicsSFMLGrid> graphics) :Level(gameObjects, graphics), gameObjects(gameObjects), graphics(graphics) {};
	void Update() {
		for (auto gb : gameObjects) {
			gb->onUpdate();
		}
	};
	void Start() {
		// should have an init function if required
	};

	void Render() {
		graphics->Render();
	};

	void Close() {}

};
