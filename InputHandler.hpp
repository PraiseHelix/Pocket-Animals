#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

/// \brief
/// Class InputHandler
/// \details
/// The InputHandler class is used to detect any key's pressed that are explicitly asked for

class InputHandler
{

private:
	std::vector<sf::Keyboard::Key> actions;
	bool set = false;
public:
	InputHandler(std::vector<sf::Keyboard::Key> actions):actions(actions) {};
	InputHandler(std::vector<sf::Keyboard::Key> & actions) :actions(actions) {
		
	};
	InputHandler() {};


	/// \brief
	/// Adding the keybindings to an inputHandler to see if it registered any presses, vector implementation
	void addKeyBindings(std::vector<sf::Keyboard::Key> keys) {
		for (auto k : keys) {
			addKeyBinding(k);
		}
	}
	

	// TODO: Implement
	void KeyBindingsSet() {

	}

	/// \brief
	/// Adding the keybindings to an inputHandler to see if it registered any presses
	void addKeyBinding(sf::Keyboard::Key newAction) {
		actions.push_back(newAction);
	};
	/// \brief
	/// returning the addedKeybindings that were found based on the keybindings that were set on the initial value
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
