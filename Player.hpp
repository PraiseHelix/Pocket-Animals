#pragma once
#include "..\SGPE\GameObject.hpp"
#include "InputHandler.hpp"
class Player :
	public GameObject

{
private:
	// TODO gameobject id
	std::shared_ptr<Canvas> canvas;
	std::shared_ptr<InputHandler> input;
protected:
	int currentIndex;
public:
	Player(std::shared_ptr<Canvas> canvas, std::shared_ptr<InputHandler> input) :canvas(canvas), input(input) {};
	~Player() {};
	void ButtonAction(const sf::Keyboard::Key key) {};
	void onUpdate() {};
	void onCall() {};
	void onStart() {};
	void onCollision() {};
	void onInteract() {};
	int getCurrentIndex() {
		return currentIndex;
	}
};