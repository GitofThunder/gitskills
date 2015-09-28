#include "Food.h"
#include "FoodCut.h"
#include "FoodMaterial.h"
#include "FoodPiece.h"
#include "GlobalData.h"
#include "GlobalFunction.h"
#include "Kitchen.h"
#include "ToolSceneBase.h"

enum EM_CUTSCENE_Z
{
    CSZ_BACKGROUND = 0,
    CSZ_SCROLL,
    CSZ_PANZI,
    CSZ_FOOD,
    CSZ_OVER,
    CSZ_UI,
    CSZ_MAX
};

#define CONTENT_HEIGHT  300
//Vec2 PANZI_POSITION[5];

CToolSceneBase::CToolSceneBase() :
m_pBottomBtn(NULL),
m_bShowBottom(false),
m_bBtnClicked(false),
m_bEnableScroll(false),
m_bFoodTouched(false),
m_nTouchedPanzi(0),
m_pCurTouchedFood(NULL),
m_bDraged(false),
m_bMoved(false)
{
    
}

CToolSceneBase::~CToolSceneBase()
{
    _eventDispatcher->removeEventListenersForTarget(this);
}

Scene* CToolSceneBase::createScene()
{
	auto scene = Scene::create();
    
	auto layer = CToolSceneBase::create();
	scene->addChild(layer);
	return scene;
}

bool CToolSceneBase::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    createBackground();
    createScrollLayer();
    createBtnUI();
    addEventListenerForTouch();
    scheduleUpdate();
    return true;
}

void CToolSceneBase::createBackground()
{

}

void CToolSceneBase::createScrollLayer()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    m_v2BottonBtnHide = Vec2(visibleSize.width, 0) + Vec2(-100, 100);
    m_v2BottomBtnShow = m_v2BottonBtnHide + Vec2(0, 200);
    
    m_v2ScrollHide = Vec2::ZERO + Vec2(0, -CONTENT_HEIGHT);
    m_v2ScrollShow = Vec2::ZERO;
    
    //首先创建scrollView
    m_pContentLayer = Layer::create();//创建scrollView中的容器层
    m_pContentLayer->setPosition(Point::ZERO);
    m_pContentLayer->setAnchorPoint(Point::ZERO);
    m_pContentLayer->setContentSize(Size(3000, CONTENT_HEIGHT));//设置容器层大小
    
    m_pScrollView = ScrollView::create(Size(visibleSize.width, CONTENT_HEIGHT), m_pContentLayer);//创建scrollView，显示窗口大小为(400,300)
    m_pScrollView->setDelegate(this);//设置委托
    m_pScrollView->setDirection(ScrollView::Direction::HORIZONTAL);//设置滚动方向为水平
    m_pScrollView->setPosition(m_v2ScrollHide);
    this->addChild(m_pScrollView, CSZ_SCROLL);
    m_pScrollView->setContentOffset(Vec2(0, 0), false);
    
    addScrollContent();
}

void CToolSceneBase::addScrollContent()
{
    
}

void CToolSceneBase::createBtnUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_pBottomBtn = createMenuItemSprite("ButtonHome1.png", CC_CALLBACK_1(CToolSceneBase::bottomBtnCallback, this), m_v2BottonBtnHide);
    
    MenuItem* pItem = createMenuItemSprite("ButtonHome1.png", CC_CALLBACK_1(CToolSceneBase::backCallback, this), Vec2(100, visibleSize.height - 100));
    
    Menu* pMenu = Menu::create(m_pBottomBtn, pItem, NULL);
    if (pMenu != NULL)
    {
        this->addChild(pMenu, CSZ_UI);
        pMenu->setPosition(Vec2::ZERO);
    }
}

void CToolSceneBase::addEventListenerForTouch()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(CToolSceneBase::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(CToolSceneBase::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CToolSceneBase::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(CToolSceneBase::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void CToolSceneBase::update(float dt)
{

}

bool CToolSceneBase::onTouchBegan(Touch *touch, Event *unused_event)
{
    Vec2 location = touch->getLocation();

    if (m_bShowBottom && location.y < 300)
    {
        m_bEnableScroll = true;
        scrollLayerTouchBegin(touch);
    }
    else
    {
        toolSceneTouchBegin(touch);
    }
    return true;
}

void CToolSceneBase::onTouchMoved(Touch *touch, Event *unused_event)
{
    if (m_bEnableScroll)
    {
        scrollLayerTouchMove(touch);
    }
    else
    {
        toolSceneTouchMove(touch);
    }
}

void CToolSceneBase::onTouchEnded(Touch *touch, Event *unused_event)
{
    if (m_bEnableScroll)
    {
        scrollLayerTouchEnd(touch);
    }
    else
    {
        toolSceneTouchEnd(touch);
    }
    //TODO:排查在哪里置位
    m_bEnableScroll = false;
    
    m_bFoodTouched = false;
    m_bMoved = false;
    m_bDraged = false;

}

void CToolSceneBase::onTouchCancelled(Touch *touch, Event *unused_event)
{
    if (m_bEnableScroll)
    {
        scrollLayerTouchCancel(touch);
    }
    else
    {
        toolSceneTouchCancel(touch);
    }
    m_bEnableScroll = false;
}

void CToolSceneBase::scrollLayerTouchBegin(Touch *touch)
{
    m_pScrollView->setScrollEnabled(false);
    m_bDraged = false;
    
    Vec2 v2Local = m_pContentLayer->convertTouchToNodeSpace(touch);
    m_lTouchBeginTime = getCurTime();
    for (int i = 0; i < BOTTOM_FOOD_COUNT; i++)
    {
        CFood* pFood = m_aFoods[i];
        if (pFood == NULL) continue;
        
        if (pFood->isPointWithinFood(v2Local))
        {
            m_bFoodTouched = true;
            m_nTouchedPanzi = i;
            return;
        }
    }
    
    m_pScrollView->setScrollEnabled(true);
}

void CToolSceneBase::scrollLayerTouchMove(Touch *touch)
{
    Vec2 v2Delta = touch->getDelta();
    
    if (m_bFoodTouched)
    {
        long long lCurTime = getCurTime();
        if (lCurTime - m_lTouchBeginTime > 500)
        {
            if (!m_bMoved || m_bDraged)
            {
                // 拖起食材
                dragFood(touch);
            }
        }
        else
        {
            Vec2 v2Moved = touch->getLocation() - touch->getStartLocation();
            if (v2Moved.length() >= 10.0f)
            {
                m_bMoved = true;
                if (!isSlideHorizontal(touch))
                {
                    // 拖起食材
                    if (!m_pScrollView->getScrollEnabled())
                        dragFood(touch);
                }
                else
                {
                    if (!m_bDraged)
                        m_pScrollView->setScrollEnabled(true);
                }
            }
        }
    }
    else
    {
        
    }
}

void CToolSceneBase::scrollLayerTouchEnd(Touch *touch)
{
    m_pScrollView->setScrollEnabled(true);
    
    if (m_bFoodTouched)
    {
        m_bFoodTouched = false;
        
        if (m_pCurTouchedFood == NULL || !m_bDraged) return;
            
        Vec2 v2Pt = convertTouchToNodeSpace(touch);
        //todo: 抽象一下
        if (v2Pt.y <= CONTENT_HEIGHT || isTouchEndFoodBack())
        {
            if (m_nTouchedPanzi < 0 || m_nTouchedPanzi >= 5) return;
            if (m_aFoods[m_nTouchedPanzi] == NULL) return;
            
            float fSpeed = 1000;
            Vec2 v2Dest = convertToNodeSpace(m_pContentLayer->convertToWorldSpace(m_aFoods[m_nTouchedPanzi]->getPosition()));
            float fDis = m_pCurTouchedFood->getPosition().distance(v2Dest);
            m_pCurTouchedFood->runAction(Sequence::create(MoveTo::create(fDis / fSpeed, v2Dest),
                                                          CallFunc::create([this](){
                if (m_pCurTouchedFood != NULL)
                {
                    m_pCurTouchedFood->removeFromParent();
                    m_pCurTouchedFood = NULL;
                }
                log("m_nTouchedPanzi is %d", m_nTouchedPanzi);
                m_aFoods[m_nTouchedPanzi]->setVisible(true);
                m_nTouchedPanzi = -1;
            }), NULL));
        }
        else    //如果不在 创建并放置在案板上，m_aFoods[i]删除？
        {
            if (m_nTouchedPanzi < 0 || m_nTouchedPanzi >= 5) return;
            
            if (m_aFoods[m_nTouchedPanzi] != NULL)
            {
                m_aFoods[m_nTouchedPanzi]->removeFromParent();
                m_aFoods[m_nTouchedPanzi] = NULL;
            }
            
            putFoodToScene(touch);
            
            if (m_pCurTouchedFood != NULL)
            {
                m_pCurTouchedFood->removeFromParent();
                m_pCurTouchedFood = NULL;
            }
            m_nTouchedPanzi = -1;
            
        }
        
    }
    else
    {
        if (m_pCurTouchedFood != NULL)
        {
            m_pCurTouchedFood->removeFromParent();
            m_pCurTouchedFood = NULL;
        }
    }
    
    m_bDraged = false;
}

void CToolSceneBase::scrollLayerTouchCancel(Touch *touch)
{
    //todo:触摸取消的逻辑
}

void CToolSceneBase::toolSceneTouchBegin(Touch *touch)
{
    
}

void CToolSceneBase::toolSceneTouchMove(Touch *touch)
{
    
}

void CToolSceneBase::toolSceneTouchEnd(Touch *touch)
{
    
}

void CToolSceneBase::toolSceneTouchCancel(Touch *touch)
{
    
}

void CToolSceneBase::dragFood(Touch *touch)
{
    m_bDraged = true;
    if (m_pCurTouchedFood == NULL)
    {
        if (m_nTouchedPanzi < 0 || m_nTouchedPanzi >= 5) return;
        if (m_aFoods[m_nTouchedPanzi] == NULL) return;
        
        m_pCurTouchedFood = createFoodByFood(m_aFoods[m_nTouchedPanzi]);
        if (m_pCurTouchedFood != NULL)
        {
            this->addChild(m_pCurTouchedFood, CSZ_OVER);
        }
        
        m_aFoods[m_nTouchedPanzi]->setVisible(false);
    }
    
    m_pCurTouchedFood->setPosition(convertTouchToNodeSpace(touch));
}

bool CToolSceneBase::isTouchEndFoodBack()
{
    return true;
}

void CToolSceneBase::putFoodToScene(Touch* pTouch)
{
    
}

void CToolSceneBase::bottomBtnCallback(Ref *pSender)
{
    if (m_bBtnClicked) return;
    
    float fTime = 0.4f;
    if (m_bShowBottom)
    {
        m_pScrollView->runAction(Sequence::create(MoveTo::create(fTime, m_v2ScrollHide),
                                                  CallFunc::create([this](){
            m_bShowBottom = false;
            m_bBtnClicked = false;
        }), NULL));
        m_pBottomBtn->runAction(MoveTo::create(fTime, m_v2BottonBtnHide));
    }
    else
    {
        m_pScrollView->runAction(Sequence::create(MoveTo::create(fTime, m_v2ScrollShow),
                                                  CallFunc::create([this](){
            m_bShowBottom = true;
            m_bBtnClicked = false;
        }), NULL));
        m_pBottomBtn->runAction(MoveTo::create(fTime, m_v2BottomBtnShow));
    }
}

void CToolSceneBase::backCallback(Ref *pSender)
{
    CGlobalData::getSingleton()->setSceneConvert(SC_CUT2MAKE);
    Director::getInstance()->replaceScene(CKitchen::createScene());
}

