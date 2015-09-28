#include "DBCCRenderHeaders.h"
#include "DragonBones.h"
#include "Food.h"
#include "FoodMaterial.h"
#include "FoodPiece.h"
#include "GlobalData.h"
#include "GlobalFunction.h"

USING_NS_DB;

bool getDeviceType()
{
    bool bHigh = false;
/*
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    bHigh = C3rdManager::getDeviceType();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
#endif
 */
    bHigh = CGlobalData::getSingleton()->getIsHighRes();
    return bHigh;
}

long long getCurTime()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    
    return (long long)now.tv_sec * 1000 + now.tv_usec / 1000;
}

void umengClick(int nRoleID)
{
    std::string sEventID = "0";
    if (strcmp(sEventID.c_str(), "0") != 0)
    {
#ifndef COCOS2D_DEBUG
        umeng::MobClickCpp::event(sEventID.c_str());
#else
        log("%s clicked+++++++++++++", sEventID.c_str());
#endif
    }

}

void umengClick(const char* pEvtID)
{
#ifndef COCOS2D_DEBUG
    umeng::MobClickCpp::event(pEvtID);
#else
    log("%s clicked+++++++++++++", pEvtID);
#endif
}

void umengClick(const char* pEvtID, const char* pLabel)
{
#ifndef COCOS2D_DEBUG
    umeng::MobClickCpp::event(pEvtID, pLabel);
#else
    log("%s -- %s clicked+++++++++++++", pEvtID, pLabel);
#endif
}

Sprite* addSprite(const char* pName, Node* pParent, Vec2 v2Pt, int nZorder)
{
    if (pName == NULL || pParent == NULL) return NULL;
    Sprite* pSprite = Sprite::create(pName);
    if (pSprite != NULL)
    {
        pParent->addChild(pSprite, nZorder);
        pSprite->setPosition(v2Pt);
        pSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    }
    return pSprite;
}

Sprite* addSprite(const char* pName, Node* pParent, Vec2 v2Pt, int nZorder, Vec2 v2Anchor, float fScaleX, float fScaleY)
{
    if (pName == NULL || pParent == NULL) return NULL;
    Sprite* pSprite = Sprite::create(pName);
    if (pSprite != NULL)
    {
        pParent->addChild(pSprite, nZorder);
        pSprite->setPosition(v2Pt);
        pSprite->setAnchorPoint(v2Anchor);
        pSprite->setScaleX(fScaleX);
        pSprite->setScaleY(fScaleY);
    }
    return pSprite;
}

Sprite* addSpriteBySpriteFrame(const char* pName, Node* pParent, Vec2 v2Pt, int nZorder, Vec2 v2Anchor, float fScaleX, float fScaleY)
{
    if (pName == NULL || pParent == NULL) return NULL;
    Sprite* pSprite = Sprite::createWithSpriteFrameName(pName);
    if (pSprite != NULL)
    {
        pParent->addChild(pSprite, nZorder);
        pSprite->setPosition(v2Pt);
        pSprite->setAnchorPoint(v2Anchor);
        pSprite->setScaleX(fScaleX);
        pSprite->setScaleY(fScaleY);
    }
    return pSprite;
}

MenuItemSprite* createMenuItemSprite(const char *pszFileName, const ccMenuCallback& selector, Vec2 pos)
{
    if (pszFileName == NULL) return NULL;
    Sprite *select = Sprite::create(pszFileName);
    Sprite *selected = Sprite::create(pszFileName);
    selected->setScale(1.1f);
    selected->setPosition(Vec2(select->boundingBox().size.width/2 - selected->boundingBox().size.width/2, select->boundingBox().size.height/2 - selected->boundingBox().size.height/2));
    MenuItemSprite* Item = MenuItemSprite::create(select, selected, selector);
    Item->setPosition(pos);
    return Item;
}

MenuItemSprite* createMenuItemSpriteBySF(const char *pszFileName, const ccMenuCallback& selector, Vec2 pos)
{
    if (pszFileName == NULL) return NULL;
    Sprite *select = Sprite::createWithSpriteFrameName(pszFileName);
    Sprite *selected = Sprite::createWithSpriteFrameName(pszFileName);
    selected->setScale(1.1f);
    selected->setPosition(Vec2(select->boundingBox().size.width/2 - selected->boundingBox().size.width/2, select->boundingBox().size.height/2 - selected->boundingBox().size.height/2));
    MenuItemSprite* Item = MenuItemSprite::create(select, selected, selector);
    Item->setPosition(pos);
    return Item;
}

Menu* createMenu(Node* pParent,const char *pszFileName, const ccMenuCallback& selector, Vec2 pos, int nZOrder, float fScale)
{
    if (pszFileName == NULL || pParent==NULL) return NULL;
    Sprite *select = Sprite ::create(pszFileName);
    Sprite *selected = Sprite ::create(pszFileName);
    selected->setScale(1.1f);
    selected->setPosition( Vec2(select->boundingBox().size.width/2 - selected->boundingBox().size.width/2, select->boundingBox().size.height/2 - selected->boundingBox().size.height/2));
    MenuItemSprite* pSprite = MenuItemSprite::create(select, selected, selector);
    pSprite->setScale(fScale);
    Menu* pMenu = CCMenu::create(pSprite,NULL);
    if (pMenu)
    {
        pMenu->setPosition(pos);
        pParent->addChild(pMenu, nZOrder);
    }
    
    return pMenu;
}

Menu* createMenuBySpriteFrame(Node* pParent,const char *pszFileName, const ccMenuCallback& selector, Vec2 pos, int nZOrder, float fScale)
{
    if (pszFileName == NULL || pParent==NULL) return NULL;
    Sprite *select = Sprite ::createWithSpriteFrameName(pszFileName);
    Sprite *selected = Sprite ::createWithSpriteFrameName(pszFileName);
    selected->setScale(1.1f);
    selected->setPosition( Vec2(select->boundingBox().size.width/2 - selected->boundingBox().size.width/2, select->boundingBox().size.height/2 - selected->boundingBox().size.height/2));
    MenuItemSprite* pSprite = MenuItemSprite::create(select, selected, selector);
    pSprite->setScale(fScale);
    Menu* pMenu = CCMenu::create(pSprite,NULL);
    if (pMenu)
    {
        pMenu->setPosition(pos);
        pParent->addChild(pMenu, nZOrder);
    }
    
    return pMenu;
}

CFood* createFoodByFood(CFood* pFood)
{
    if (pFood == NULL) return NULL;
    
    CFood* pRet = NULL;
    if (pFood->getMaterials().size() > 0)
    {
        FOOD_TYPE eType = pFood->getFoodType();
        switch (eType)
        {
            case FT_ORIGIN:
            {
                pRet = CFoodMaterial::create((MATERIAL_ID)pFood->getMaterials()[0]);
                break;
            }
            case FT_SUIPIAN:
            {
                pRet = CFoodPiece::create((MATERIAL_ID)pFood->getMaterials()[0]);
                break;
            }
            case FT_CHUAN:
            {
                break;
            }
            case FT_TANG:
            {
                break;
            }
            case FT_SHALA:
            {
                break;
            }
            case FT_YINLIAO:
            {
                break;
            }
            default:
                break;
        }
        
        if (pRet != NULL)
        {
            std::vector<int> vMaterials;
            vMaterials.clear();
            for (int i = 0; i < pFood->getMaterials().size(); i++)
            {
                vMaterials.push_back(pFood->getMaterials()[i]);
            }
            
            int aTastes[2] = {0, 0};
            pRet->initProperty(eType, vMaterials, aTastes, pFood->getPanziIndex());
        }
    }
    
    return pRet;
}

bool isSlideHorizontal(Touch* pTouch)
{
    bool bHorizontal = false;
    Vec2 v2Delta = pTouch->getDelta();
    
    float fAngle = v2Delta.getAngle() * 180 / 3.1415926f;
    if ((fAngle >= -180 && fAngle <= -135) || (fAngle >= -45 && fAngle <= 45) || (fAngle >= 135 && fAngle <= 180))
    {
        bHorizontal = true;
    }
    
    return bHorizontal;
}

int Random()
{
    struct timeval start;
    gettimeofday(&start,0);
    
    srand(start.tv_usec / 1000);
    return rand();
}

int Random(int nMin, int nMax)
{
    struct timeval start;
    gettimeofday(&start,0);
    
    srand(start.tv_usec);
    return nMin + ((nMax == nMin) ? 0 : rand() % (nMax - nMin));
}
