#pragma once
#include "..\SGPE\Level.hpp"
#include "GraphicsSFML.hpp"
class FormUI : public Level
{
private:
	bool loop = true;
	std::vector<GameObject*>  gameObjects;
	std::shared_ptr<GraphicsSFML> graphics;

public:
	FormUI(std::vector<GameObject*> gameObjects, std::shared_ptr<GraphicsSFML> graphics) :Level(gameObjects, graphics), gameObjects(gameObjects), graphics(graphics) {};
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

	~FormUI() {};
};

