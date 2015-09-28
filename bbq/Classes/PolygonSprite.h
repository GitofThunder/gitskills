#ifndef __PolygonSprite_H__
#define __PolygonSprite_H__

#include "cocos2d.h"
#include "PRFilledPolygon.h"

#define PTM_RATIO 32

class CPolygonSprite : public PRFilledPolygon
{
public:
    CPolygonSprite();
    virtual ~CPolygonSprite();
    
    CREATE_FUNC(CPolygonSprite);
    virtual bool init();
    
private:
    std::string m_sTexture;

};

#endif