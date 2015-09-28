#include "FoodMaterial.h"

CFoodMaterial::CFoodMaterial()
{
    m_eFoodType = FT_ORIGIN;
}

CFoodMaterial::~CFoodMaterial()
{
    
}

CFoodMaterial* CFoodMaterial::create(const char *pszFileName)
{
    CFoodMaterial* pRet = new (std::nothrow) CFoodMaterial();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

CFoodMaterial* CFoodMaterial::create(MATERIAL_ID eId)
{
    if (eId < 0 || eId >= MI_MAX) return NULL;
    const char* pszFileName = MATERIAL_CONFIG[eId].sName.c_str();
    CFoodMaterial* pRet = new (std::nothrow) CFoodMaterial();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool CFoodMaterial::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    schedule(schedule_selector(CFoodMaterial::myUpdate));
    return true;
}

bool CFoodMaterial::isPointWithinFood(Vec2 v2Pt)
{
    return getBoundingBox().containsPoint(v2Pt);
}

void CFoodMaterial::myUpdate(float fEscapeTime)
{
    
}

