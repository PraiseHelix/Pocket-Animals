#include "TileManager.hpp"

std::vector<Tile*> TileManager::getTiles() {
	std::ifstream file(filename);
	nlohmann::json J;
	file >> J;

	nlohmann::json::array_t tileArray = J["data"]["grid"]["tiles"];
	nlohmann::json::array_t gfxData = J["data"]["grid"]["gfx"];
	unsigned int arraySize = tileArray.size();
	std::vector<Tile*> tileVec;

	unsigned int r = 0;
	unsigned int width = J["data"]["grid"]["width"];

	for (unsigned int i = 0; i < arraySize; i++) {
		unsigned int index = i % width;

		nlohmann::json::object_t tileID = tileArray[i][std::to_string(i)];

		int type = tileID["type"];
		nlohmann::json::object_t gfxID = gfxData[type][std::to_string(type)];

		int tileSize = gfxID["size"][0];
		int tileScale = gfxID["scale"][0];

		float x = static_cast<float>(index*tileSize*tileScale);
		float y = static_cast<float>(r*tileSize*tileScale);

		tileVec.push_back(new Tile{ type,unique[type]});
		tileVec[i]->setPosition(sf::Vector2f{ x, y });

		unique[type]->appendSprite(&tileVec[i]->m_sprite);
		if (index == width - 1) {
			r++;
		}
	}

	for (unsigned i = 0; i < unique.size(); i++) {
		unique[i]->setupSpriteTable(std::to_string(i));
		unique[i]->setAnimation(gfxData[i][std::to_string(i)]["anim_name"], true, true);
	}
	file.close();
	return tileVec;
}

std::vector<Tile*> TileManager::getNpc() {
	std::ifstream file(filename);
	nlohmann::json J;
	file >> J;
	
	nlohmann::json::array_t gfxData = J["data"]["grid"]["gfx"];
	nlohmann::json::array_t npcArray = J["data"]["grid"]["npc"];
	std::vector<Tile*> v;

	for (unsigned int i = 0; i < npcArray.size(); i++) {
		nlohmann::json::object_t UID = npcArray[i][std::to_string(i)];

		int id = UID["tile_id"];
		nlohmann::json::array_t path = UID["path"];
		nlohmann::json::array_t time = UID["time"];
		if (time[0] == "None") { time[0] = 0; }
		unsigned int index = UID["position"];
		v.push_back(new Tile{ id, unique[id], i});
		v[i]->setPath(path, time);
		v[i]->setPosition(convertIndextoCoords(index));
		v[i]->setGridPosition(index);
		
		unique[id]->appendSprite(&v[i]->m_sprite);
	}
	for (unsigned int i = 0; i < unique.size(); i++) {
		unique[i]->setupSpriteTable(std::to_string(i));
		unique[i]->setAnimation(gfxData[i][std::to_string(i)]["anim_name"], true, true);
	}
	file.close();
	return v;
}

std::vector<UniqueTile*> TileManager::getUniqueTiles() {
	return unique;
}

//Deze functie converteert een std::vector index naar sf::Vector2f
sf::Vector2f TileManager::convertIndextoCoords(unsigned int index) {
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
	auto coords = sf::Vector2f{ static_cast<float>(m_index)*tileSize, static_cast<float>(c)*tileSize - tileSize};
	return coords;
}