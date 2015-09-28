#ifndef __Cut_Scene__
#define __Cut_Scene__

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

class CCutScene : public CToolSceneBase
{
public:
    CCutScene();
    virtual ~CCutScene();
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
    
    bool slice(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);
    void clipPoly(PhysicsShapePolygon* shape, Point normal, float distance);
    
    void checkFoodSliced();
    
    CREATE_FUNC(CCutScene);
private:
    PhysicsWorld* _world;
    Sprite* _bg;
    
    Blade* _blade;
    Vector<Blade*> _blades;
    Point _startPoint;
    Point _endPoint;
    Size _visibleSize;
    float _deltaRemainder;
    int _sliceTag;
    Vec2 m_v2Delta;
    long long m_lLastSlice;
    int m_nSliceCount;
    
    bool m_bHasFood;
    
    ParticleSystemQuad* m_pEmitter[PARTICLE_COUNT];
    
    std::vector<CFoodCut*> m_vCutFoods;
};

#endif
