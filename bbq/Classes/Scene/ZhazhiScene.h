#ifndef __ZHAZHI_SCENE__
#define __ZHAZHI_SCENE__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MacroVariable.h"
#include "ToolSceneBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CFoodCut;
class CFoodMaterial;

class CZhazhiScene : public CToolSceneBase
{
public:
    CZhazhiScene();
    virtual ~CZhazhiScene();
    static Scene* createScene();
    virtual bool init() override;
    
    virtual void createBackground();
    virtual void createScrollLayer();
    virtual void createBtnUI();
    
    virtual void update(float dt);
    void scrollLayerTouchBegin(Touch *touch);
    void scrollLayerTouchMove(Touch *touch);
    void scrollLayerTouchEnd(Touch *touch);
    void scrollLayerTouchCancel(Touch *touch);
        
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    CREATE_FUNC(CZhazhiScene);
    
protected:
    ScrollView* m_pScrollView;
    Layer* m_pContentLayer;
    MenuItem* m_pBottomBtn;
    bool m_bShowBottom;
    bool m_bBtnClicked;
    bool m_bEnableScroll;
    bool m_bDraged;
    
    int m_nTouchedPanzi;
    bool m_bFoodTouched;
    bool m_bMoved;
    CFoodMaterial* m_pCurTouchedFood;
    
    Vec2 m_v2BottomBtnShow;
    Vec2 m_v2BottonBtnHide;
    Vec2 m_v2ScrollShow;
    Vec2 m_v2ScrollHide;
};

#endif
