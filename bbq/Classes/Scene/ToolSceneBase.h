#ifndef __TOOL_SCENE_BASE__
#define __TOOL_SCENE_BASE__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MacroVariable.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define PARTICLE_COUNT  10
#define BOTTOM_FOOD_COUNT   5

class CFood;
class CFoodCut;
class CFoodMaterial;

class CToolSceneBase : public Layer, public ScrollViewDelegate
{
public:
    CToolSceneBase();
    virtual ~CToolSceneBase();
    static Scene* createScene();
    virtual bool init() override;
    
    virtual void createBackground();
    virtual void createScrollLayer();
    virtual void addScrollContent();
    virtual void createBtnUI();
    
    void addEventListenerForTouch();
    
    virtual void update(float dt);

    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    virtual void scrollLayerTouchBegin(Touch *touch);
    virtual void scrollLayerTouchMove(Touch *touch);
    virtual void scrollLayerTouchEnd(Touch *touch);
    virtual void scrollLayerTouchCancel(Touch *touch);
    
    /* begin 子类重载以下函数，并实现即可 */
    virtual void toolSceneTouchBegin(Touch *touch);
    virtual void toolSceneTouchMove(Touch *touch);
    virtual void toolSceneTouchEnd(Touch *touch);
    virtual void toolSceneTouchCancel(Touch *touch);
    
    virtual void dragFood(Touch *touch);
    virtual bool isTouchEndFoodBack();
    virtual void putFoodToScene(Touch* pTouch);
    /* end */
    
    void bottomBtnCallback(Ref* pSender);
    void backCallback(Ref* pSender);
    
    CREATE_FUNC(CToolSceneBase);
    
protected:
    CFood* m_aFoods[BOTTOM_FOOD_COUNT];
    
    ScrollView* m_pScrollView;
    Layer* m_pContentLayer;
    MenuItem* m_pBottomBtn;
    bool m_bShowBottom;
    bool m_bBtnClicked;
    bool m_bEnableScroll;
    bool m_bDraged;
    
    long long m_lTouchBeginTime;
    int m_nTouchedPanzi;
    bool m_bFoodTouched;
    bool m_bMoved;
    CFood* m_pCurTouchedFood;
    
    Vec2 m_v2BottomBtnShow;
    Vec2 m_v2BottonBtnHide;
    Vec2 m_v2ScrollShow;
    Vec2 m_v2ScrollHide;
};

#endif
