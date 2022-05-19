#include "Map.h"
#include "Texture.h"
#include <fstream>

Map::Map()
{
    for(int i=0; i<maxTiles; i++){
        tile[i].loadFromFile("media/map/"+std::to_string(i)+".png");
    }
}

Map::~Map()
{}

void Map::loadMap(std::string path)
{
    std::ifstream file(path);

    for(int i=0; i < maxX; i++){
        for(int j=0; j < maxY; j++)
            file>>tileMap[i][j];
    }
}

void Map::drawMap()
{
    for(int i=0; i < maxX; i++){
        for(int j=0; j < maxY; j++){
            tile[tileMap[i][j]].setRect(j*TILE_SIZE, i*TILE_SIZE);
            tile[tileMap[i][j]].renderTexture(NULL);
        }
    }

}
