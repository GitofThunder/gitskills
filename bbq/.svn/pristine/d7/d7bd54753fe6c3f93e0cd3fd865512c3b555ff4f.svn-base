#include "FoodCut.h"

CFoodCut::CFoodCut() : m_llBirthTime(0)
{
    
}

CFoodCut::~CFoodCut()
{
    
}

CFoodCut* CFoodCut::create(MATERIAL_ID id, int nIndex, int nCutIndex)
{
    if (id < 0 || id > MI_MAX) return NULL;
    int nSideLen = MATERIAL_CONFIG[id].nSideLen;
    Point points[4] =
    {
        Point(0, 0), Point(0, nSideLen), Point(nSideLen, nSideLen), Point(nSideLen, 0)
    };
    Vector2dVector vcPoints;
    vcPoints.clear();
    for (int i = 0; i < 4; i++)
    {
        vcPoints.push_back(Vector2d(points[i].x, points[i].y));
    }
    std::string sName = MATERIAL_CONFIG[id].sName;
    
    Texture2D* fillTexture = Director::getInstance()->getTextureCache()->addImage(sName.c_str());
    if (fillTexture == NULL) return NULL;
    
    CFoodCut *pRet = new CFoodCut();
    if(pRet && pRet->initWithPointsAndTexture(vcPoints, fillTexture))
    {
        pRet->setTextureName(sName.c_str());
        pRet->setPhysicsBody(PhysicsBody::createPolygon(points, 4));
        pRet->autorelease();
        std::vector<int> vMaterials;
        vMaterials.clear();
        vMaterials.push_back(id);
        
        int aTastes[2] = {0, 0};
        pRet->initProperty(FT_SUIPIAN, vMaterials, aTastes, nIndex);
        pRet->setTouchedIndex(nCutIndex);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CFoodCut* CFoodCut::create(MATERIAL_ID id, Vector2dVector &polygonPoints, int nIndex, int nCutIndex)
{
    if (id < 0 || id > MI_MAX) return NULL;
    const char* pszFileName = MATERIAL_CONFIG[id].sName.c_str();
    Texture2D* fillTexture = Director::getInstance()->getTextureCache()->addImage(pszFileName);
    if (fillTexture == NULL) return NULL;
    
    CFoodCut *pRet = new CFoodCut();
    if(pRet && pRet->initWithPointsAndTexture(polygonPoints, fillTexture))
    {
        pRet->setTextureName(pszFileName);
        pRet->autorelease();
        pRet->setTouchedIndex(nIndex);
        std::vector<int> vMaterials;
        vMaterials.clear();
        vMaterials.push_back(id);
        
        int aTastes[2] = {0, 0};
        pRet->initProperty(FT_SUIPIAN, vMaterials, aTastes, nIndex);
        pRet->setTouchedIndex(nCutIndex);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CFoodCut::isPointWithinFood(Vec2 v2Pt)
{
    return getBoundingBox().containsPoint(v2Pt);
}

void CFoodCut::myUpdate(float fEscapeTime)
{
    
}