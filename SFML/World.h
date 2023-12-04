#pragma once

#include <iostream>
#include <vector>

class World {
	private:
		int TILE_SIZE = 64;
		int HORIZONTAL_BLOCK_NUMBER = 40;
		int VERTICAL_BLOCK_NUMBER = 10;
	public:
		World();
		std::vector<std::vector<int>> matrix;
		void setMatrix(std::vector<std::vector<int>> matrix);
		int getTileSize();
		int getHorizontalBlockNumber();
		int getVerticalBlockNumber();
		std::vector<std::vector<int>> getWorld();
};