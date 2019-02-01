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
	enum status {EMPTY, INPUT_GIVEN, WAITING_INPUT, SWITCH_MESSAGE};
	status STATE = EMPTY;

public:
	PopUp(std::shared_ptr<InputHandler> input
	): input(input){
		font.loadFromFile("arial.ttf");
		text.setFont(font);
		text.setCharacterSize(18);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);

		text.setString("NOTHING TO PRINT");

		font.loadFromFile("arial.ttf");
		subtext.setFont(font);
		subtext.setCharacterSize(10);
		subtext.setFillColor(sf::Color::Black);
		subtext.setStyle(sf::Text::Regular);
		subtext.setString("Press Enter or Space to dismiss");

		rectangle.setFillColor(sf::Color::White);

	}

	bool stringsSet() {

		if(STATE != EMPTY){
			return true;
		}

		return false;
	}


	void onUpdate() {
		// if a key input has been given and we're waiting on it
		if (input->getKeybindings().size() != 0) {	
			STATE = INPUT_GIVEN;
		}
	};

	void scheduleMessages(std::vector<std::string> str) {
		for (auto s : str) {
			setString(s);
		}
	}

	bool messageRemaining() {
		return !strings.empty();
	}
	void setString(std::string st) {
		STATE = WAITING_INPUT;
		strings.push(st);
		
	}
	void onStart() {};
	void onCollision() {};
	void onInteract() {};
	void onCall() {};
	void onRender(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f playerPos) {

		bool redo;
		do
		{
			redo = false;
				switch (STATE) {
				case EMPTY:
					toqueue = "";
					break;

				case INPUT_GIVEN:
				
					if (messageRemaining()) {
						STATE = WAITING_INPUT;
						toqueue = strings.front();
						strings.pop();
						redo = true;// can crash entire game
		
					}
					else {
						STATE = EMPTY;
					}

					break;

				case SWITCH_MESSAGE:

					break;
				
				case WAITING_INPUT:
					if (toqueue == "") {
						toqueue = strings.front();
						strings.pop();

					}
					sf::Time t = sf::milliseconds(1000);
					sf::sleep(t);
			
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
				
					break;

				}

		} while (redo);

	}

};
