#ifndef GEOMETRIC_H_INCLUDED
#define GEOMETRIC_H_INCLUDED

#include "Game.h"
#include "commonFunc.h"

class Gemometric
{
public:
   static void RenderRectange(const GeometricFormat& geo_size, const ColorData& color);
   static void RenderOutline(const GeometricFormat& geo_size, const ColorData& color);
};



#endif // GEOMETRIC_H_INCLUDED
