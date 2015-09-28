#include "Pineapple.h"

CPolygonSprite* CPineapple::initWithWorld(b2World* world)
{
    b2Vec2 points[4] =
    {
        b2Vec2(0 / PTM_RATIO, 0 / PTM_RATIO), b2Vec2(0 / PTM_RATIO, 256 / PTM_RATIO),
        b2Vec2(256 / PTM_RATIO, 256 / PTM_RATIO), b2Vec2(256 / PTM_RATIO, 0 / PTM_RATIO)
    };
    
    b2Body *body = createBodyForWorld(world, b2Vec2(500 / PTM_RATIO, 300 / PTM_RATIO), 0, points, 4, 5.0f, 0.2f, 0.2f);
    return initWithFile("pineapple.png", body, true);
}

