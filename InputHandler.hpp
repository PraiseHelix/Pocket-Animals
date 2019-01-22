#pragma once

#include <functional>
#include <SFML/Graphics.hpp>



class InputHandler
{

private:
	std::vector<sf::Keyboard::Key> actions;
public:
	InputHandler(std::vector<sf::Keyboard::Key> actions):actions(actions) {};
	InputHandler(std::vector<sf::Keyboard::Key> & actions) :actions(actions) {
		
	};
	InputHandler() {};
	~InputHandler() {};


	void addKeyBindings(std::vector<sf::Keyboard::Key> keys) {
		for (auto k : keys) {
			addKeyBinding(k);
		}
	}
	void addKeyBinding(sf::Keyboard::Key & newAction) {
		actions.push_back(newAction);
	};

	std::vector<sf::Keyboard::Key> getKeybindings() {
		std::vector<sf::Keyboard::Key> keys;
		for (auto key : actions) {
			if (sf::Keyboard::isKeyPressed(key)) {
				keys.push_back(key);
			}
		}
		return keys;
	}
};
