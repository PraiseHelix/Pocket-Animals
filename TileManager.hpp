#pragma once
#include <string>
#include "Tile.hpp"
#include "TextureManager.hpp"
#include "json.hpp"

//No imagePath, TextureManager uses TileID

class TileManager {
private:
	std::string filename;
	TextureManager &tex;
public:
	TileManager(std::string filename, TextureManager &tex) : filename(filename), tex(tex) {};
	std::vector<Tile*> getTiles();

};

