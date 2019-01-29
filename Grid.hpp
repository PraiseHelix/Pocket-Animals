#pragma once
#include "..\SGPE\Canvas.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "TileManager.hpp"
#include "Tile.hpp"
#include "LevelManagerPocketAnimalsSync.hpp"
#include "PopUp.hpp"

//TODO:	Player als laatste renderen.

class Grid : public Canvas {
private:
	std::vector<Tile*> tileVec;
	std::vector<Tile*> npcVec;
	sf::Vector2f playerPosition;
	unsigned int playerIndex;
	unsigned int playerTileIndex;
	unsigned int width;
	unsigned int tileSize;
	std::map<std::string, int> directionMap;
	std::shared_ptr<LevelManagerPocketAnimalsSync> levelSync;
	std::shared_ptr<PopUp> dialog;

public:
	Grid(TileManager & tileManager, unsigned int width, unsigned int tileSize, std::shared_ptr<LevelManagerPocketAnimalsSync> levelSync, std::shared_ptr<PopUp> dialog);
	Grid() {};
	bool validMove(int currentIndex, int direction);
	int move(int currentIndex, int ID, int direction);
	int getType(int currentIndex, int direction);
	void Render(std::shared_ptr<sf::RenderWindow> w);
	void update(float &dT);
	void draw(std::shared_ptr<sf::RenderWindow> w);
	void movePlayer(std::string direction);
	int checkDirection(std::string direction);
	void setupMap(nlohmann::json::array_t &gridData);
	unsigned int move(unsigned int currentIndex, int ID, std::string direction);
	sf::Vector2f getPlayerPos();
	unsigned int getPlayerIndex();
	sf::Vector2f convertIndextoCoords(unsigned int index);
	void setPlayerIndex(unsigned int index);
	void setPlayerPosition(sf::Vector2f pos);
	void appendTile(Tile* toAdd) {
		tileVec.push_back(toAdd);
	}
	void updatePlayerIndex();
	~Grid();
};
