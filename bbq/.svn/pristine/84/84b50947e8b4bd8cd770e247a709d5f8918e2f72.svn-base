#ifndef __JUICING_SCENE__
#define __JUICING_SCENE__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCBlade.h"
#include "MacroVariable.h"
#include "ToolSceneBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define PARTICLE_COUNT  10

class CFoodCut;
class CFoodMaterial;

class CJuicingScene : public CToolSceneBase
{
public:
    CJuicingScene();
    virtual ~CJuicingScene();
    static Scene* createScene();
    virtual bool init() override;
    
    virtual void createBackground();
    virtual void addScrollContent();
    
    void setPhyWorld(PhysicsWorld* world){ _world = world; };
    
    virtual void update(float dt);
    
    //void scrollLayerTouchBegin(Touch *touch);
    //void scrollLayerTouchMove(Touch *touch);
    //void scrollLayerTouchEnd(Touch *touch);
    //void scrollLayerTouchCancel(Touch *touch);
    
    virtual void toolSceneTouchBegin(Touch *touch);
    virtual void toolSceneTouchMove(Touch *touch);
    virtual void toolSceneTouchEnd(Touch *touch);
    virtual void toolSceneTouchCancel(Touch *touch);
    
    virtual void dragFood(Touch *touch);
    virtual bool isTouchEndFoodBack();
    virtual void putFoodToScene(Touch* pTouch);
    
    
    CREATE_FUNC(CJuicingScene);
private:
    PhysicsWorld* _world;
    
};

#endif
