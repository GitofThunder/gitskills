#include "PolygonSprite.h"

CPolygonSprite::CPolygonSprite()
{
    
}

CPolygonSprite::~CPolygonSprite()
{
    
}

bool CPolygonSprite::init()
{
    if (!PRFilledPolygon::init()) return false;
    
    return true;
}