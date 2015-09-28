#ifndef __FOOD_H__
#define __FOOD_H__

#include "cocos2d.h"
#include "MacroVariable.h"

USING_NS_CC;

class CFood : public Sprite
{
public:
    CFood();
    virtual ~CFood();
    virtual bool init();
    
    void initProperty(FOOD_TYPE eType, std::vector<int>& vMaterials, int aTastes[], int nIndex = -1);
    
    std::vector<int>& getMaterials() {  return m_vMaterials; };
    int getTastes(TASTE_TYPE eType) { return m_aTastes[eType]; }
    
    virtual bool isPointWithinFood(Vec2 v2Pt);
    
    CC_SYNTHESIZE(FOOD_TYPE, m_eFoodType, FoodType);
    CC_SYNTHESIZE(int, m_nPanziIndex, PanziIndex);
    
protected:
    int m_aTastes[TT_MAX];   //酸 辣
    std::vector<int> m_vMaterials;
    
private:
    
};

#endif // __FOOD_H__
