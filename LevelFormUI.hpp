#pragma once
#include "..\SGPE\Level.hpp"
#include "GraphicsSFML.hpp"
class LevelFormUI : public Level
{
private:
	bool loop = true;
	std::vector<GameObject*>  gameObjects;
	std::shared_ptr<GraphicsSFML> graphics;

public:
	LevelFormUI(std::vector<GameObject*> gameObjects, std::shared_ptr<GraphicsSFML> graphics) :Level(gameObjects, graphics), gameObjects(gameObjects), graphics(graphics) {};
	void Update() {
		for (auto gb : gameObjects) {
			gb->onUpdate();
		}
	};
	void Start() {
		// should have an init function if required
	};

	void Render() {
		
		auto window = graphics->returnWindow();
		window->clear(sf::Color(204, 204, 204, 1));
		window->setView(sf::View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)));

		sf::Text text;
		sf::Text subtext;
		sf::Font font;

		auto view = window->getView();
		auto size = view.getSize();
		float width = float(size.x);
		float heightR = float(size.y / 16);

		font.loadFromFile("PokemonSolid.ttf");
		text.setFont(font);
		text.setCharacterSize(45);		
		text.setFillColor(sf::Color::Yellow);
		text.setOutlineColor(sf::Color::Blue);
		text.setStyle(sf::Text::Regular);
		text.setString("PocketAnimals");
		text.setPosition(width / 4 * 0.5, heightR / 2);
	
		// TODO add sprite of default logo

		sf::Image image;
		sf::Texture texture;
		if (!texture.loadFromFile("Logo.png"))
		{
			// error...
		}


		texture.setSmooth(true);// update a texture from a sf::Image
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.25f, 0.25f));
	

		subtext.setFont(font);
		subtext.setCharacterSize(30);
		subtext.setFillColor(sf::Color::Yellow);
		subtext.setOutlineColor(sf::Color::Blue);
		subtext.setStyle(sf::Text::Bold);
		subtext.setString("Press SPACE or RETURN to Start!");
		subtext.setPosition(width / 4 * 0.5, heightR * 10);
		
		sprite.setPosition(width / 4 * 1, heightR * 4);

		window->draw(sprite);

		window->draw(text);
		window->draw(subtext);

		window->display();

		//graphics->Render();
	};

	void Close() {

	}

	~LevelFormUI() {};
};

