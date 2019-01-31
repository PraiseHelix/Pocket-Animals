#pragma once
#include "..\SGPE\GameObject.hpp"
#include "Grid.hpp"
#include "InputHandler.hpp"
#include <iostream>
class Player :
	public GameObject

{
private:
	// TODO gameobject id
	std::shared_ptr<Grid> grid;
	std::shared_ptr<InputHandler> input;
	unsigned int currentIndex = 0;
	int ticker = 0;
	bool tickerPermissionSet = false;

public:
	Player(std::shared_ptr<Grid> grid, std::shared_ptr<InputHandler> input) :grid(grid), input(input) {};
	~Player() {};
	void ButtonAction(const sf::Keyboard::Key key) {

		std::string one_direction = "";
		switch (key) {
			case sf::Keyboard::A:
				one_direction = "left";
				grid->movePlayer(one_direction);
				break;
			case sf::Keyboard::W:

				one_direction = "up";
				grid->movePlayer(one_direction);
				break;
			case sf::Keyboard::S:
				one_direction = "down";
				grid->movePlayer(one_direction);
	
				break;
			case sf::Keyboard::D:
				one_direction = "right";
				grid->movePlayer(one_direction);
				break;
			}

		
	
		//std::cout << one_direction << std::endl;

	};
	void onUpdate() {
		//TicketUpdate();
		auto keys = input->getKeybindings();
		if (keys.size() != 0) {
			//if (tickerPermissionSet) {
				for (auto key : keys) {
					ButtonAction(key);
				}
			//}
		}
	};
	void onCall() {};
	void onStart() {};
	void onCollision() {};
	void onInteract() {};
	int getCurrentIndex() {
		return currentIndex;
	}

	void TicketUpdate() {
		if (ticker == 100) {
			tickerPermissionSet = true;
			ticker = 0;
		}
		else {
			tickerPermissionSet = false;
			ticker++;
		}
	}
};