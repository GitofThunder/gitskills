#ifndef __FRIDGE_H__
#define __FRIDGE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CFridgeFood : public Sprite
{
public:
    CFridgeFood();
    virtual ~CFridgeFood();
    CREATE_FUNC(CFridgeFood);
    static CFridgeFood* create(const char *pszFileName);
    
    CC_SYNTHESIZE(MATERIAL_ID, m_pMaterialId, MaterialId);
    CC_SYNTHESIZE(bool, m_bPressed, IsPressed);
private:
    
};

class CFridge : public Layer, public ScrollViewDelegate
{
public:
    CFridge();
    virtual ~CFridge();
    CREATE_FUNC(CFridge);
    virtual bool init();
    
    virtual void onExit();
    
    void initBackGround();
    void myUpdate(float fEscapeTime);
    
    void touchBegin(Touch *touch);
    void touchMove(Touch *touch);
    void touchEnd(Touch *touch);
    void touchCancel(Touch *touch);
    
    void dragFood(Vec2 v2Position);
    void endDragFood(Touch* pTouch);
    
    void longTouchFood(float fEscapeTime);
    CC_SYNTHESIZE(bool, m_bFoodTouched, FoodTouched);   //是否有食材被点击
    CC_SYNTHESIZE(float, m_fOldPos_Y, OldPosY);
private:
    Sprite* m_pIceBox;
    ScrollView* m_pScrollView;
    Layer* m_pContentLayer;
    
    CFridgeFood* m_aFoods[FOOD_COUNT];
    CFridgeFood* m_pCurTouchedFood;
    bool m_bTouched;
    long long m_lTouchBeginTime;
    bool m_bMoved;  // 按下后0.5s内是否移动
    bool m_bDraged;
};

struct SDragedFoodInfo
{
    Vec2 v2Global;
    MATERIAL_ID eId;
};

struct SFoodBackInfo
{
    Vec2 v2Dest;
    std::function<void()> func;
};

#endif // __FRIDGE_H__
