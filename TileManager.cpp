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



		std::string animName = gfxID["anim_name"];



		float x = static_cast<float>(index*tileSize*tileScale);

		float y = static_cast<float>(r*tileSize*tileScale);

		tileVec.push_back(new Tile{ type,&tex,animName });

		tileVec[i]->setPosition(sf::Vector2f{ x, y });



		if (index == width - 1) {

			r++;

		}

	}

	return tileVec;

}