#pragma once
#include "..\SGPE\GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <queue>

class PopUp : public GameObject {
private:
	std::shared_ptr<InputHandler> input;
	bool havingSet = false;
	bool waitingInput = false;
	std::queue<std::string> strings;
	std::string toqueue;
	sf::Text text;
	sf::Text subtext;
	sf::Font font;
	sf::RectangleShape rectangle;

public:
	PopUp(std::shared_ptr<InputHandler> input
	): input(input){
		font.loadFromFile("calibri.ttf");
		text.setFont(font);
		text.setCharacterSize(18);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);

		text.setString("NOTHING TO PRINT");

		font.loadFromFile("calibri.ttf");
		subtext.setFont(font);
		subtext.setCharacterSize(10);
		subtext.setFillColor(sf::Color::Black);
		subtext.setStyle(sf::Text::Regular);
		subtext.setString("Press Enter or Space to dismiss");

		rectangle.setFillColor(sf::Color::White);

	}

	bool stringsSet() {
		return waitingInput;
	}


	void onUpdate() {
		
		if (input->getKeybindings().size() != 0 && waitingInput) {
			waitingInput = false;
		}

		if (strings.empty() == true) {
			havingSet = false;
		}
		else {
			havingSet = true;
		}
	};

	void scheduleMessages(std::vector<std::string> str) {
		for (auto s : str) {
			setString(s);
		}
	}
	void setString(std::string st) {
		waitingInput = true;
		havingSet = true;
		strings.push(st);
	}
	void onStart() {};
	void onCollision() {};
	void onInteract() {};
	void onCall() {};
	void onRender(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f playerPos) {
		if (havingSet == true) {
			toqueue = strings.front();
		}
		if (havingSet == true && waitingInput == true) {

			text.setString(toqueue);
			auto view = window->getView();
			auto size = view.getSize();
			float width = float(size.x);
			float heightR = float(size.y / 16);
			sf::RectangleShape rectangle(sf::Vector2f(width, heightR * 2));
			rectangle.setPosition(sf::Vector2f(playerPos.x - width / 2, playerPos.y + heightR * 6));

			text.setPosition(rectangle.getPosition().x + width / 8, rectangle.getPosition().y + heightR / 2);
			subtext.setPosition(rectangle.getPosition().x + width / 8, rectangle.getPosition().y + heightR / 0.75f);
			window->draw(rectangle);
			window->draw(text);
			window->draw(subtext);
		}
	}

};
