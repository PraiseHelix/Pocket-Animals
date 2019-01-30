
#pragma once
#include "..\SGPE\GameObject.hpp"
#include <SFML/Graphics.hpp>

class PopUp : public GameObject {
private:
	std::shared_ptr<InputHandler> input;
	bool set = false;
	std::vector<std::string> strings;
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
		if (strings.size() != 0) {
			return true;
		}
		return false;
	}


	void onUpdate() {
		if (set != false) {
			if (input->getKeybindings().size() != 0) {
				set = false;
			}
		}
	};
	void setString(std::string st) {
		set = true;
		text.setString(st);
	}
	void onStart() {};
	void onCollision() {};
	void onInteract() {};
	void onCall() {};
	void onRender(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f playerPos) {
		if (set == true) {

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
			
			set = stringsSet();
		}

	}

};
