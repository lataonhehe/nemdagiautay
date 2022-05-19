#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include "Texture.h"
#include "commonFunc.h"

class Map
{
public:
    Map();
    ~Map();

    void loadMap(std::string path);
    void drawMap();
    int tileMap[maxX][maxY];
private:
    //SDL_Rect src,dest;

    Texture tile[maxTiles];



};

#endif // GAMEMAP_H_INCLUDED
