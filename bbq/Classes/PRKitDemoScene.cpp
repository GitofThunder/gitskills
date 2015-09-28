//
//  PRKitDemoScene.cpp
//  RockChipmunk2D
//
//  Created by ChildhoodAndy on 14-4-16.
//
//
#include "PRKitDemoScene.h"
#include "PRFilledPolygon.h"
#include "triangulate.h"


Scene* PRKitDemoScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PRKitDemoScene::create();
    scene->addChild(layer);
    return scene;
}

bool PRKitDemoScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto color_bg = LayerColor::create(Color4B(125, 125, 125, 125));
    addChild(color_bg);
    
    //--------------------- START
    Vector2dVector polygonPoints;
    /*
    polygonPoints.push_back(Vector2d(0, 0));
    polygonPoints.push_back(Vector2d(0, 256));
    polygonPoints.push_back(Vector2d(256, 256));
    polygonPoints.push_back(Vector2d(256, 128));
     */
    /*
    polygonPoints.push_back(Vector2d(-128, -128));
    polygonPoints.push_back(Vector2d(-128, 128));
    polygonPoints.push_back(Vector2d(128, 128));
    polygonPoints.push_back(Vector2d(128, 0));
    */
    
    polygonPoints.push_back(Vector2d(100, 100));
    polygonPoints.push_back(Vector2d(200, 100));
    polygonPoints.push_back(Vector2d(300, 200));
    polygonPoints.push_back(Vector2d(400, 300));
    polygonPoints.push_back(Vector2d(500, 500));
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("pineapple.png");
    
    PRFilledPolygon *filledPolygon = PRFilledPolygon::filledPolygonWithPointsAndTexture(polygonPoints, texture);
    addChild(filledPolygon,1);
    filledPolygon->setPosition(Vec2(256, 256));
    //filledPolygon->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    //filledPolygon->runAction(MoveBy::create(10, Vec2(1000, 1000)));
    //---------------------- END
    
    return true;
}

std::string PRKitDemoScene::demo_info() const
{
    return "PRKit使用例子";
}

void PRKitDemoScene::restartCallback(Ref *pSender)
{
    Director::getInstance()->replaceScene(PRKitDemoScene::createScene());
}

void PRKitDemoScene::backCallback(Ref *pSender)
{
    //Director::getInstance()->replaceScene(ContentLayer::createScene());
}