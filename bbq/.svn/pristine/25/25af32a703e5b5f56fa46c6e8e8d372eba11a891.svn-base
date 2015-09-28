//
//  FruitCutNinjaScene.cpp
//  RockChipmunk2D
//
//  Created by ChildhoodAndy on 14-4-16.
//
//

#include "Food.h"
#include "FoodCut.h"
#include "FoodMaterial.h"
#include "FoodPiece.h"
#include "GlobalData.h"
#include "GlobalFunction.h"
#include "HelloWorldScene.h"
#include "JuicingScene.h"
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

#define CONTENT_HEIGHT  300

CJuicingScene::CJuicingScene()
{
    
}

CJuicingScene::~CJuicingScene()
{

}

Scene* CJuicingScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -1));
    scene->getPhysicsWorld()->setSpeed(8);
    //scene->getPhysicsWorld()->set
    
	auto layer = CJuicingScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool CJuicingScene::init()
{
    if (!CToolSceneBase::init())
    {
        return false;
    }
    
    return true;
}

void CJuicingScene::createBackground()
{

}

void CJuicingScene::addScrollContent()
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

void CJuicingScene::update(float dt)
{

}

void CJuicingScene::toolSceneTouchBegin(Touch *touch)
{

}

void CJuicingScene::toolSceneTouchMove(Touch *touch)
{

}

void CJuicingScene::toolSceneTouchEnd(Touch *touch)
{

}

void CJuicingScene::toolSceneTouchCancel(Touch *touch)
{

}

void CJuicingScene::dragFood(Touch *touch)
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


bool CJuicingScene::isTouchEndFoodBack()
{
    return true;
}

void CJuicingScene::putFoodToScene(Touch* pTouch)
{

}
