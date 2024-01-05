#include "World.h"

World::World() {
}

void World::setMatrix(std::vector<std::vector<int>> matrix)
{
    this->matrix = matrix;
}

int World::getTileSize() {
    return TILE_SIZE;
}
int World::getHorizontalBlockNumber() {
    return HORIZONTAL_BLOCK_NUMBER;
}
int World::getVerticalBlockNumber() {
    return VERTICAL_BLOCK_NUMBER;
}

std::vector<std::vector<int>> World::getWorld() {
    return matrix;
}
