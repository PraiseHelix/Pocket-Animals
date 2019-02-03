#pragma once
#include "..\SGPE\Level.hpp"
#include "GraphicsSFMLGrid.hpp"
class LevelOpenWorldPocketAnimals : public Level
{
private:
	std::vector<GameObject*>  gameObjects;
	std::shared_ptr<GraphicsSFMLGrid> graphics;

public:
	LevelOpenWorldPocketAnimals(std::vector<GameObject*> gameObjects, std::shared_ptr<GraphicsSFMLGrid> graphics) :Level(gameObjects, graphics), gameObjects(gameObjects), graphics(graphics) {};
	
	/// \brief
	/// Calls the update function of all it's gameobject
	void Update() {
		for (auto gb : gameObjects) {
			gb->onUpdate();
		}
	};
	void Start() {
		// should have an init function if required
	};
	/// \brief
	/// Calls the graphics render mode
	void Render() {
		graphics->Render();
	};

	void Close() {}

};
