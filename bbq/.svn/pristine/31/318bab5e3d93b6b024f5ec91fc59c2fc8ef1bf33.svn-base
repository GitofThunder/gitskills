#pragma once

#include "cocos2d.h"

using namespace cocos2d;

bool getDeviceType();

long long getCurTime();

void umengClick(int nRoleID);
void umengClick(const char* pEvtID);
void umengClick(const char* pEvtID, const char* pLabel);

void setSearchPaths();

Sprite* addSprite(const char* pName, Node* pParent, Vec2 v2Pt, int nZorder = 0);
Sprite* addSprite(const char* pName, Node* pParent, Vec2 v2Pt, int nZorder, Vec2 v2Anchor, float fScaleX = 1.0f, float fScaleY = 1.0f);
template<typename T>
T* addSelfSprite(const char* pName, Node* pParent, Vec2 v2Pt, int nZorder, Vec2 v2Anchor)
{
    if (pName == NULL || pParent == NULL) return NULL;
    T* pSprite = T::create(pName);
    if (pSprite != NULL)
    {
        pParent->addChild(pSprite, nZorder);
        pSprite->setPosition(v2Pt);
        pSprite->setAnchorPoint(v2Anchor);
    }
    return pSprite;
}

Sprite* addSpriteBySpriteFrame(const char* pName, Node* pParent, Vec2 v2Pt, int nZorder, Vec2 v2Anchor, float fScaleX = 1.0f, float fScaleY = 1.0f);

MenuItemSprite* createMenuItemSprite(const char *pszFileName, const ccMenuCallback& selector, Vec2 pos);
MenuItemSprite* createMenuItemSpriteBySF(const char *pszFileName, const ccMenuCallback& selector, Vec2 pos);
Menu* createMenu(Node* pParent,const char *pszFileName, const ccMenuCallback& selector, Vec2 pos, int nZOrder = 0, float fScale = 1.0f);
Menu* createMenuBySpriteFrame(Node* pParent,const char *pszFileName, const ccMenuCallback& selector, Vec2 pos, int nZOrder = 0, float fScale = 1);

CFood* createFoodByFood(CFood* pFood);

bool isSlideHorizontal(Touch* pTouch);

int Random();
int Random(int nMin, int nMax);

template<typename T>
void array_shuffle(T* pArray, int nSize)
{
    int nIndex = 0;
    T nNum;
    for(int i = 0; i < nSize - 1; i++)
    {
        nIndex = i + Random() % (nSize - i);
        if (nIndex == i) continue;
        
        nNum = pArray[i];
        pArray[i] = pArray[nIndex];
        pArray[nIndex] = nNum;
    }
}

