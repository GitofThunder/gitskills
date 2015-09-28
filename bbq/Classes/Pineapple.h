#ifndef __Pineapple_H__
#define __Pineapple_H__

#include "PolygonSprite.h"

class CPineapple : public CPolygonSprite
{
public:
    CREATE_FUNC(CPineapple);
    virtual bool init() { return true; }
    virtual CPolygonSprite* initWithWorld(b2World* world);
};

#endif
