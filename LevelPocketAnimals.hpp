#pragma once
#include "..\SGPE\Level.hpp"
#include "GraphicsSFML.hpp"
class LevelPocketAnimals : public Level
{
private:
	std::vector<GameObject*>  gameObjects;
	std::shared_ptr<GraphicsSFML> graphics;

public:
	LevelPocketAnimals(std::vector<GameObject*> gameObjects, std::shared_ptr<GraphicsSFML> graphics) :Level(gameObjects, graphics), gameObjects(gameObjects), graphics(graphics) {};
	void Update() {
		graphics->Render();
	};
	void Start() {};

	void Render() {};

	~LevelPocketAnimals() {};
};
