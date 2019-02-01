#include "Tile.hpp"
#include "UniqueTile.hpp"

void Tile::setPosition(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
}

void Tile::setScale(sf::Vector2f scale) {
	m_sprite.setScale(scale);
}

void Tile::setGridPosition(unsigned int index) {
	gridPosition = index;
}

unsigned int Tile::getGridPosition() {
	return gridPosition;
}

std::string Tile::getType() {
	return this->m_uniqueTile->getType();
}

unsigned int Tile::getUID() {
	return UID;
}

void Tile::setPath(nlohmann::json::array_t paths, nlohmann::json::array_t pathTime) {
	for (unsigned int i = 0; i < paths.size(); i++) {
		this->path.push_back(paths[i]);
		this->time.push_back(pathTime[i]);
	}
	this->pathIndex = 0;
	this->timeIndex = 0;
	this->currentDirection = path[pathIndex];
	this->currentTime = time[pathIndex];
}

void Tile::setNextDirection() {
	if (pathIndex < path.size()-1) {
		++pathIndex;
	}
	else if(timeIndex >= time.size()-1) {
		pathIndex = 0;
	}
	currentDirection = path[pathIndex];
}

std::string Tile::getCurrentDirection() {
	return currentDirection;
}

void Tile::setNextTime() {
	if (timeIndex < time.size()-1) {
		++timeIndex;
	}
	else if (timeIndex >= time.size()-1) {
		timeIndex = 0;
	}
	currentTime = time[timeIndex];
}

unsigned int Tile::getCurrentTime() {
	return currentTime;
}