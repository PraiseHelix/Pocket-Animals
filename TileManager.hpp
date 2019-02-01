#pragma once
#include <string>
#include <fstream>
#include "Tile.hpp"
#include "UniqueTile.hpp"
#include "TextureManager.hpp"
#include "json.hpp"

//No imagePath, TextureManager uses TileID

class TileManager {
private:
	std::string filename;
	TextureManager &tex;
	std::vector<UniqueTile*> unique;
	unsigned int width;
	unsigned int tileSize;
public:
	TileManager(std::string filename, TextureManager &tex, unsigned int width, unsigned int tileSize) : filename(filename), tex(tex), width(width), tileSize(tileSize) {
		std::ifstream file(filename);
		nlohmann::json J;
		file >> J;
		nlohmann::json::array_t gfxData = J["data"]["grid"]["gfx"];
		for (unsigned int i = 0; i < gfxData.size(); i++) {
			this->unique.push_back(new UniqueTile{ i, &tex });
			this->unique[i]->setType(gfxData[i][std::to_string(i)]["type"]);
		}
		file.close();
	};
	std::vector<Tile*> getTiles();
	std::vector<UniqueTile*> getUniqueTiles();
	std::vector<Tile*> getNpc();
	sf::Vector2f TileManager::convertIndextoCoords(unsigned int index);
};

