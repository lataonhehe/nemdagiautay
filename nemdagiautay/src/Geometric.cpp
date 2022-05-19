#include "Geometric.h"

void Gemometric::RenderRectange(const GeometricFormat& geo_size, const ColorData& color)
{
    SDL_Rect fillRect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(Game::renderer, color.red_, color.green_, color.blue_, 0);
    SDL_RenderFillRect(Game::renderer, &fillRect );
}

void Gemometric::RenderOutline(const GeometricFormat& geo_size, const ColorData& color)
{
    SDL_Rect outlineRect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(Game::renderer, color.red_, color.green_, color.blue_, 0);
    SDL_RenderDrawRect(Game::renderer, &outlineRect );
}
