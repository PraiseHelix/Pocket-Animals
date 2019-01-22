#pragma once
#include "..\SGPE\Canvas.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "TileManager.hpp"
#include "Tile.hpp"

//TODO:	Player als laatste renderen.

class Grid: public Canvas {
private:
	std::vector<Tile*> tileVec;
	sf::Vector2f playerPosition;
	unsigned int playerIndex;
	std::map<std::string, int> directionMap;
public:
	Grid(TileManager & tileManager);
	bool validMove(int currentIndex, int direction);
	int move(int currentIndex, int ID, int direction);
	int getType(int currentIndex, int direction);
	void Render(std::shared_ptr<sf::RenderWindow> window) {
		std::cout << __FILE__ << std::endl;
	}
	void update(float &dT);
	void draw(std::shared_ptr<sf::RenderWindow> w);
	void setPlayerPosition(sf::Vector2f pos);
	void movePlayer(sf::Vector2f delta);
	int checkDirection(std::string direction);
	void setupMap(nlohmann::json::array_t &gridData);
	int move(int currentIndex, int ID, std::string direction);
	sf::Vector2f getPlayerPos();
	~Grid();
};
