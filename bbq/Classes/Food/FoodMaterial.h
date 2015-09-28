#ifndef __FOOD_MATERIAL_H__
#define __FOOD_MATERIAL_H__

#include "cocos2d.h"
#include "Food.h"
#include "PRFilledPolygon.h"

class CFoodMaterial : public CFood
{
public:
    CFoodMaterial();
    virtual ~CFoodMaterial();
    CREATE_FUNC(CFoodMaterial);
    static CFoodMaterial* create(const char *pszFileName);
    static CFoodMaterial* create(MATERIAL_ID eId);
    virtual bool init();
    virtual bool isPointWithinFood(Vec2 v2Pt);
    
    void myUpdate(float fEscapeTime);
    
private:
    
};

#endif // __FOOD_MATERIAL_H__
