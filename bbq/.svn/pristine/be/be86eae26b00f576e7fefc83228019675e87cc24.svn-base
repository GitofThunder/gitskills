//
//  FruitCutNinjaScene.cpp
//  RockChipmunk2D
//
//  Created by ChildhoodAndy on 14-4-16.
//
//

#include "CutScene.h"
#include "Food.h"
#include "FoodCut.h"
#include "FoodMaterial.h"
#include "FoodPiece.h"
#include "GlobalData.h"
#include "GlobalFunction.h"
#include "HelloWorldScene.h"
#include "Kitchen.h"
#include "PEShapeCache_X3_0.h"
#include "PolygonSprite.h"
#include "PRFilledPolygon.h"

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

CCutScene::CCutScene() :
_blade(NULL),
m_lLastSlice(0),
m_nSliceCount(0),
m_bHasFood(false)
{
    _blades.clear();
    for (int i = 0; i < 5; i++)
    {
        m_aFoods[i] = NULL;
    }
    m_vCutFoods.clear();
}

CCutScene::~CCutScene()
{

}

Scene* CCutScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -1));
    scene->getPhysicsWorld()->setSpeed(8);
    //scene->getPhysicsWorld()->set
    
	auto layer = CCutScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool CCutScene::init()
{
    if (!CToolSceneBase::init())
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _deltaRemainder = 0.0f;
    _sliceTag = 1;
    
    //加入封闭的盒子，用作墙壁
    auto body = PhysicsBody::createEdgeBox(_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto wallNode = Node::create();
    wallNode->setPosition(_visibleSize.width/2, _visibleSize.height/2);
    wallNode->setPhysicsBody(body);
    this->addChild(wallNode);
    
    auto texture = Director::getInstance()->getTextureCache()->addImage("streak.png");
    
    for (int i = 0; i < 3; i++)
    {
        Blade* blade = Blade::createWithMaximumPoint(50);
        blade->setAutoDim(false);
        blade->setTexture(texture);
        
        addChild(blade, 100);
        _blades.pushBack(blade);
    }
    
    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        m_pEmitter[i] = ParticleSystemQuad::create("pineapple_splurt.plist");
        this->addChild(m_pEmitter[i], 100);
        m_pEmitter[i]->setAutoRemoveOnFinish(false);
        m_pEmitter[i]->setDuration(0.1f);
        m_pEmitter[i]->setScale(1.5f);
    }
    
    return true;
}

void CCutScene::createBackground()
{
    
    Point points[4] =
    {
        Point(0, 0), Point(0, 2048), Point(2048, 2048), Point(2048, 0)
    };
    Vector2dVector vcPoints;
    vcPoints.clear();
    for (int i = 0; i < 4; i++)
    {
        vcPoints.push_back(Vector2d(points[i].x, points[i].y));
    }
    
    PRFilledPolygon *filledPolygon = PRFilledPolygon::filledPolygonWithPointsAndTexture(vcPoints, "daanban.png");
    //filledPolygon->setPhysicsBody(PhysicsBody::createPolygon(points, 4));
    filledPolygon->setPosition(Vec2::ZERO + Vec2(0, (1536 - 2048) / 2));
    addChild(filledPolygon, 80);
}

void CCutScene::addScrollContent()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    int nIndex = 0;
    for (int i = 0; i < 5; i++)
    {
        CFoodInfo* pFood = CGlobalData::getSingleton()->getPanziFood(i);
        if (pFood == NULL) continue;
        if (pFood->getFoodType() == FT_ORIGIN)
        {
            addSprite("panzi.png", m_pContentLayer, Vec2(visibleSize.width - 200 - 400 * nIndex, 150), 0, Vec2::ANCHOR_MIDDLE);
            
            std::vector<int> vMaterial = pFood->getMaterials();
            MATERIAL_ID id = (MATERIAL_ID)vMaterial[0];
            if (id >= MI_MAX) return;
            std::string sName = MATERIAL_CONFIG[id].sName;
            CFoodMaterial* pFoodMaterial = CFoodMaterial::create(sName.c_str());
            if (pFoodMaterial != NULL)
            {
                m_pContentLayer->addChild(pFoodMaterial, 1);
                pFoodMaterial->setPosition(Vec2(visibleSize.width - 200 - 400 * nIndex, 150));
                std::vector<int> vMaterials;
                vMaterials.clear();
                vMaterials.push_back(id);
                int aTastes[2] = {0, 0};
                pFoodMaterial->initProperty(FT_ORIGIN, vMaterials, aTastes, pFood->getPanziIndex());
            }
            
            m_aFoods[nIndex ++] = pFoodMaterial;
        }
        
        PANZI_POSITION[i] = Vec2(visibleSize.width - 200 - 400 * i, 150);
    }
}

void CCutScene::update(float dt)
{
    if (_blade && _blade->getPath().size() > 3)
    {
        _deltaRemainder += dt * 60 * 1.2f;
        int pop = (int)roundf(_deltaRemainder);
        _deltaRemainder -= pop;
        _blade->pop(pop);
    }
}

void CCutScene::toolSceneTouchBegin(Touch *touch)
{
    Vec2 location = touch->getLocation();
    _startPoint = location;
    _endPoint = location;
    
    for (Blade* blade : _blades)
    {
        if (blade->getPath().size() == 0)
        {
            _blade = blade;
            _blade->push(location);
            break;
        }
    }
}

void CCutScene::toolSceneTouchMove(Touch *touch)
{
    Point location = touch->getLocation();
    _endPoint = location;
    
    if ((_startPoint - _endPoint).getLength() > 25)
    {
        _startPoint = _endPoint;
    }
    
    _blade->push(location);
    
    m_v2Delta = touch->getLocation() - touch->getPreviousLocation();
    auto func = CC_CALLBACK_3(CCutScene::slice, this);
    _world->rayCast(func, touch->getPreviousLocation(), touch->getLocation(), nullptr);
}

void CCutScene::toolSceneTouchEnd(Touch *touch)
{
    _blade->setDim(true);
}

void CCutScene::toolSceneTouchCancel(Touch *touch)
{
    _blade->setDim(true);
}

void CCutScene::dragFood(Touch *touch)
{
    m_bDraged = true;
    if (m_pCurTouchedFood == NULL)
    {
        if (m_nTouchedPanzi < 0 || m_nTouchedPanzi >= 5) return;
        if (m_aFoods[m_nTouchedPanzi] == NULL) return;
        
        
        
        std::vector<int> vMaterial = m_aFoods[m_nTouchedPanzi]->getMaterials();
        MATERIAL_ID id = (MATERIAL_ID)vMaterial[0];
        if (id >= MI_MAX) return;
        std::string sName = MATERIAL_CONFIG[id].sName;
        m_pCurTouchedFood = CFoodMaterial::create(sName.c_str());
        if (m_pCurTouchedFood != NULL)
        {
            this->addChild(m_pCurTouchedFood, CSZ_OVER);
            std::vector<int> vMaterials;
            vMaterials.clear();
            vMaterials.push_back(id);
            int aTastes[2] = {0, 0};
            m_pCurTouchedFood->initProperty(FT_ORIGIN, vMaterials, aTastes);
            m_pCurTouchedFood->setPanziIndex(m_aFoods[m_nTouchedPanzi]->getPanziIndex());
        }
        
        m_aFoods[m_nTouchedPanzi]->setVisible(false);
    }
    
    m_pCurTouchedFood->setPosition(convertTouchToNodeSpace(touch));
}


bool CCutScene::isTouchEndFoodBack()
{
    return m_bHasFood;
}

void CCutScene::putFoodToScene(Touch* pTouch)
{
    std::vector<int> vMaterials = m_pCurTouchedFood->getMaterials();
    MATERIAL_ID eId = MI_MAX;
    if(vMaterials.size() != 0)
    {
        eId = (MATERIAL_ID)vMaterials[0];
    }
    
    CFoodCut* pFood = CFoodCut::create(eId, m_pCurTouchedFood->getPanziIndex(), m_nTouchedPanzi);
    if (pFood != NULL)
    {
        float fWidth = MATERIAL_CONFIG[eId].nSideLen / 2.0f;
        pFood->setPosition(convertTouchToNodeSpace(pTouch) - Vec2(fWidth, fWidth));
        pFood->getPhysicsBody()->setTag(_sliceTag);
        pFood->getPhysicsBody()->setGravityEnable(false);
        addChild(pFood, 80);
        
        m_vCutFoods.push_back(pFood);
    }
    m_bHasFood = true;
}

bool CCutScene::slice(PhysicsWorld &world, const PhysicsRayCastInfo& info, void *data)
{
    log("slice called %f, %f, %lld", info.contact.x, info.contact.y, m_lLastSlice);
    if (!m_bHasFood) return true;
    
    if (info.shape->getBody()->getTag() != _sliceTag)
    {
        return true;
    }
    
    long long llLastSlice = 0;
    PhysicsBody* pBody = info.shape->getBody();
    if (pBody == NULL) return true;
    CFoodCut* pFood = (CFoodCut*)info.shape->getBody()->getNode();
    if (pFood == NULL) return true;
    llLastSlice = pFood->getBirthTime();
    
    if (getCurTime() - llLastSlice <= 200) return true;
    m_v2Delta.normalize();
    Vec2 v2Start = info.contact - m_v2Delta * 100;
    Vec2 v2End = info.contact + m_v2Delta * 500;
    
    if (!info.shape->containsPoint(v2Start) && !info.shape->containsPoint(v2End))
    {
        Vec2 normal = v2End - v2Start;
        normal = normal.getPerp().getNormalized();
        float dist = v2Start.dot(normal);
        
        clipPoly(dynamic_cast<PhysicsShapePolygon*>(info.shape), normal, dist);
        clipPoly(dynamic_cast<PhysicsShapePolygon*>(info.shape), -normal, -dist);
        
        Vec2 v2Direct = (v2End - v2Start).getNormalized();
        Vec2 v2Tmp = Vec2::ZERO;
        for (int i = 0; i < PARTICLE_COUNT; i++)
        {
            v2Tmp = info.contact + v2Direct * 80 * (i - 1);
            if (!info.shape->containsPoint(v2Tmp))
            {
                continue;
            }
            else
            {
                m_pEmitter[i]->setPosition(v2Tmp);
                m_pEmitter[i]->resetSystem();
            }
        }
        
        std::vector<CFoodCut*>::iterator it;
        for (it = m_vCutFoods.begin(); it != m_vCutFoods.end(); it++)
        {
            CFoodCut* pTmp = *it;
            if (pTmp == info.shape->getBody()->getNode())
            {
                m_vCutFoods.erase(it);
                break;
            }
        }
        m_nSliceCount--;
        info.shape->getBody()->removeFromWorld();
        info.shape->getBody()->getNode()->removeFromParent();
        
        checkFoodSliced();
    }
    
    return true;
}

void CCutScene::clipPoly(PhysicsShapePolygon* shape, Point normal, float distance)
{
    PhysicsBody* body = shape->getBody();
    int count = shape->getPointsCount();
    int pointsCount = 0;
    Point* points = new Point[count + 1];
    
    Vector2dVector vcPoints;
    vcPoints.clear();
    Vector2d v2Point(0, 0);
    
    for (int i=0, j=count-1; i<count; j=i, ++i)
    {
        Point a = body->local2World(shape->getPoint(j));
        float aDist = a.dot(normal) - distance;
        
        if (aDist < 0.0f)
        {
            points[pointsCount] = a;
            ++pointsCount;
        }
        
        Point b = body->local2World(shape->getPoint(i));
        float bDist = b.dot(normal) - distance;
        
        if (aDist*bDist < 0.0f)
        {
            float t = std::fabs(aDist)/(std::fabs(aDist) + std::fabs(bDist));
            Vec2 v2Tmp = a.lerp(b, t);
            points[pointsCount] = v2Tmp;
            ++pointsCount;
        }
    }
    
    Point center = PhysicsShape::getPolyonCenter(points, pointsCount);
    
    for (int i = 0; i < pointsCount; i++)
    {
        points[i] = body->world2Local(points[i]);
        vcPoints.push_back(Vector2d(points[i].x, points[i].y));
    }
    
    PhysicsBody* polyon = PhysicsBody::createPolygon(points, pointsCount);
    
    CFoodCut* pNode = (CFoodCut*)(body->getNode());
    std::vector<int> vMaterials;
    vMaterials.clear();
    vMaterials = pNode->getMaterials();
    MATERIAL_ID eId = MI_MAX;
    if (vMaterials.size() != 0)
    {
        eId = (MATERIAL_ID)vMaterials[0];
    }
    
    CFoodCut *filledPolygon = CFoodCut::create(eId, vcPoints, pNode->getPanziIndex(), pNode->getTouchedIndex());
    filledPolygon->setPhysicsBody(polyon);
    int nTmp = rand() % 50 + 50;
    int nTmpRotate = rand() % 30 - 60;
    filledPolygon->setPosition(body->getPosition());
    //filledPolygon->setRotation(filledPolygon->getRotation() + nTmpRotate);
    filledPolygon->getPhysicsBody()->setTag(_sliceTag);
    filledPolygon->getPhysicsBody()->setGravityEnable(false);
    
    
    polyon->setVelocity(body->getVelocityAtWorldPoint(center));
    //polyon->setAngularVelocity(body->getAngularVelocity());
    polyon->setTag(_sliceTag);
    
    float fMass = polyon->getMass();
    float fV = 80;
    float fImpulse = fMass * fV;
    float fTmpX = (float)(Random() % 30) / 100.0f - 0.15f;
    float fTmpY = (float)(rand() % 30) / 100.0f - 0.15f;
    polyon->applyImpulse((normal + Vec2(fTmpX, fTmpY)) * -fImpulse);
    polyon->setLinearDamping(0.8f);
    addChild(filledPolygon, 80);
    filledPolygon->setBirthTime(getCurTime());
    m_vCutFoods.push_back(filledPolygon);
    m_nSliceCount ++;
    delete[] points;
}

void CCutScene::checkFoodSliced()
{
    if (m_nSliceCount >= 8)
    {
        //todo:暂时不能切,播放庆祝特效
        
        m_nSliceCount = 0;
        CFoodCut* pFood = NULL;
        int nIndex = -1;
        int nCount = m_vCutFoods.size();
        for (int i = 0; i < nCount; i++)
        {
            pFood = m_vCutFoods[i];
            if (pFood != NULL)
            {
                nIndex = pFood->getTouchedIndex();
                Vec2 v2Dest = convertToNodeSpace(m_pContentLayer->convertToWorldSpace(PANZI_POSITION[nIndex]));
                float fSpeed = 1200;
                float fDis = pFood->getPosition().distance(v2Dest);
                pFood->runAction(Sequence::create(DelayTime::create(0.08f * i),
                                                  MoveTo::create(fDis / fSpeed, v2Dest),
                                                  CallFunc::create([this, pFood, nCount, nIndex](){
                    static int nTmp = 0;
                    nTmp ++;
                    if (nTmp >= nCount)
                    {
                        nTmp = 0;
                        //todo: 在盘子上创建碎食材
                        std::vector<int> vMaterials = pFood->getMaterials();
                        MATERIAL_ID eId = MI_MAX;
                        if (vMaterials.size() != 0)
                        {
                            eId = (MATERIAL_ID)vMaterials[0];
                        }

                        int aTastes[TT_MAX] = {0};
                        CFoodPiece* pFoodPiece = CFoodPiece::create(eId);
                        if (pFoodPiece != NULL)
                        {
                            pFoodPiece->initProperty(FT_SUIPIAN, vMaterials, aTastes);
                            m_pContentLayer->addChild(pFoodPiece, 1);
                            pFoodPiece->setPosition(PANZI_POSITION[nIndex]);
                        }
                        
                        CGlobalData::getSingleton()->setPanziFood(pFood->getPanziIndex(), pFood);
                    }
                    
                    pFood->removeFromParent();
                }), NULL));
            }
        }
        m_vCutFoods.clear();
        m_bHasFood = false;
    }
}
