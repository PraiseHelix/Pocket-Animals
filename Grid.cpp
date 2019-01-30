#include "Grid.hpp"
#include <iostream>
#include "PopUp.hpp"
//#include "GameObjectsDefault.hpp"

Grid::Grid(TileManager & tileManager, unsigned int width, unsigned int tileSize, std::shared_ptr<LevelManagerPocketAnimalsSync> levelSync, std::shared_ptr<PopUp> dialog):
	unique(tileManager.getUniqueTiles()), tileVec(tileManager.getTiles()), width(width), tileSize(tileSize), levelSync(levelSync), dialog(dialog), npcVec(tileManager.getNpc())
{	
	minimap.zoom(0.9f);

}

void Grid::Render(std::shared_ptr<sf::RenderWindow> w) {
	std::cout << __FILE__ << std::endl;
}

void Grid::update(float &dT) {
	for (auto &i : unique) {
		i->updateFrame(dT);
	}
	dialog->onUpdate();
}

Grid::~Grid() {
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> w) {


	auto gridPlayer = w->getView();
	gridPlayer.setCenter(getPlayerPos());
	w->setView(gridPlayer);
	for (auto &i : unique) {
		i->draw(w);
	}
	dialog->onRender(w, getPlayerPos());

	w->setView(minimap);
	minimap.setViewport(sf::FloatRect(0.60f, 0.20f, 0.25f, 0.25f));
	minimap.setCenter(getPlayerPos());
	
	for (auto &i : unique) {;
		i->draw(w);
	}

	w->setView(w->getDefaultView());
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

		// TODO needs optimize with unordered map, look up times are too large

		int futureIndex = static_cast<int>(currentIndex) + tmp;
		if (futureIndex < 0 || futureIndex >= static_cast<int>(tileVec.size())) { return currentIndex; }
		for (auto &i : npcVec) {
			unsigned int npcIndex = i->getGridPosition();
			if (futureIndex == npcIndex || futureIndex == npcIndex + checkDirection("up")) {
				
				// PocketAnimal means fighting regardless
				if (i->getType() == "pocket_animal") {
					levelSync->change(3);
				}
				else if(i->getType() == "npc"){
					dialog->setString("WOW watch where you're going buddy.");
				}
				// PocketAnimal
				return currentIndex;
			}
		}
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