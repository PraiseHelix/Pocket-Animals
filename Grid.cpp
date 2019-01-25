#include "Grid.hpp"
#include <iostream>
//#include "GameObjectsDefault.hpp"





Grid::Grid(TileManager & tileManager, unsigned int width, unsigned int tileSize):tileVec(tileManager.getTiles()), width(width), tileSize(tileSize)
{}



void Grid::Render(std::shared_ptr<sf::RenderWindow> w) {
	std::cout << __FILE__ << std::endl;
}

void Grid::update(float &dT) {
	for (auto &i : tileVec) {
		i->updateFrame(dT);
	}
}

Grid::~Grid() {
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> w) {
	for (auto &i : tileVec) {
		i->draw(w);
	}
}

void Grid::setPlayerPosition(sf::Vector2f pos) {
	playerPosition = pos;
	tileVec[playerTileIndex]->setPosition(playerPosition);
}

void Grid::movePlayer(std::string direction) {
	auto step = this->move(playerIndex, 4, direction);
	setPlayerPosition(convertIndextoCoords(playerIndex));
	tileVec[playerTileIndex]->setPosition(playerPosition);
}

int Grid::checkDirection(std::string direction) {
	auto tmp = directionMap.find(direction);
	if (tmp != directionMap.end()) {
		return tmp->second;
	}
	return -2;		//Left is always -1
}

unsigned int Grid::move(unsigned int currentIndex, int ID, std::string direction) {
	auto tmp = checkDirection(direction);
	if (tmp != -2) {
		int futureIndex = static_cast<int>(currentIndex) + tmp;
		if (futureIndex < 0 || futureIndex >= static_cast<int>(tileVec.size())) { return currentIndex; }
		if (tileVec[futureIndex]->getType() != "solid") {
			currentIndex = futureIndex;
			playerIndex += tmp;
		}
	}
	return static_cast<unsigned int>(currentIndex);
}

void Grid::setupMap(nlohmann::json::array_t &gridData) {
	directionMap.emplace("left", gridData[0]["left"]);
	directionMap.emplace("right", gridData[1]["right"]);
	directionMap.emplace("up", gridData[2]["up"]);
	directionMap.emplace("down", gridData[3]["down"]);
}

sf::Vector2f Grid::getPlayerPos() {
	return playerPosition;
}

unsigned int Grid::getPlayerIndex() {
	return playerIndex;
}

//Deze functie converteert een std::vector index naar sf::Vector2f
sf::Vector2f Grid::convertIndextoCoords(unsigned int index) {
	//TODO:	make map width + scaling private vars
	int m_index = static_cast<int>(index);
	int c = 0;
	while (m_index >= 0) {
		if ((m_index -= width) < 0) {
			m_index += width;
			break;
		}
		else {
			c++;
		}
	}
	return sf::Vector2f{ static_cast<float>(m_index)*tileSize, static_cast<float>(c)*tileSize - tileSize };
}


void Grid::setPlayerIndex(unsigned int index) {
	playerIndex = index;
	
}

void Grid::updatePlayerIndex() {
	playerTileIndex = tileVec.size() - 1;
}