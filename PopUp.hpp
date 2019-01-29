
#pragma once
#include "..\SGPE\GameObject.hpp"
#include <SFML/Graphics.hpp>

class PopUp : public GameObject {
private:
	std::shared_ptr<InputHandler> input;
	bool set = false;
	std::string s;
	sf::Text text;
	sf::Text subtext;
	sf::Font font;
	sf::RectangleShape rectangle;

public:
	PopUp(std::shared_ptr<InputHandler> input
	): input(input){
		font.loadFromFile("calibri.ttf");
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);
		text.setPosition(140.0f, 420.0f);


		font.loadFromFile("calibri.ttf");
		text.setFont(font);
		subtext.setCharacterSize(10);
		subtext.setFillColor(sf::Color::Black);
		subtext.setStyle(sf::Text::Bold);
		subtext.setPosition(150.0f, 420.0f);
		subtext.setString("Press Enter or Space to dismiss");

		rectangle.setFillColor(sf::Color::White);

	}



	void onUpdate() {

		std::cout << set << std::endl;
		if (set != false) {
			if (input->getKeybindings().size() != 0) {
				set = false;
			}
		}
	};
	void setString(std::string st) {
		std::cout << "SET" << std::endl;
		set = true;
		text.setString(st);
	}
	void onStart() {};
	void onCollision() {};
	void onInteract() {};
	void onCall() {};
	void onRender(std::shared_ptr<sf::RenderWindow> window) {
		if (set == true) {

			std::cout << "2";

			auto size = window->getSize();
			float width = float(size.x);
			float heightR = float(size.y / 8);
			sf::RectangleShape rectangle(sf::Vector2f(width, heightR));
			rectangle.setPosition(sf::Vector2f(0.0f, heightR * 7));
			window->draw(rectangle);
			window->draw(text);
			window->draw(subtext);
			
		}

	}

};
