//
//  CEatingTest.cpp
//  TravelDemo
//
//  Created by kids on 15/8/24.
//
//

#include "CEatingTest.h"
#include "EatingRoleData.h"
#include "GlobalData.h"
#include "stdio.h"
#include "BBQChooseLayer.h"

Scene* CEatingTest::createScene()
{
    auto _scene = Scene::create();
    
    auto _layer = CEatingTest::create();
    
    _scene->addChild(_layer);
    
    return _scene;
}


bool CEatingTest::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    LayerColor* _layer = LayerColor::create(Color4B(255, 255, 0, 125));
    this->addChild(_layer);
//    for (int i = 0; i < MAX_ROLE_NUM; ++i) {
//        std::string _boneXML = EATING_ROLE_MEMBERS_NAMES[i] + ".xml";
//        DBCCFactory::getInstance()->loadDragonBonesData(_boneXML, EATING_ROLE_MEMBERS_NAMES[i]);
//        std::string _textureXML = EATING_ROLE_MEMBERS_NAMES[i] + "0.xml";
//        DBCCFactory::getInstance()->loadTextureAtlas(_textureXML, EATING_ROLE_MEMBERS_NAMES[i]);
//    }
    
    addRole();
    addTouch();
    
    addFood();
    addButton();
    
    m_tmp_food = nullptr;
    
    m_touch_enable = true;
    
    m_last_index = -1;
    
    return true;
}


//void CEatingTest::addRole()
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    
//    _testRole = CEatingRoleBasic::create();
//    if (_testRole) {
//        _testRole->setPosition(visibleSize.width/2, visibleSize.height/4);
//        _testRole->createObject(Cowboy, ERAI_MIDDLE_BOTTOM, 0);
//        _testRole->initEyePos();
//        this->addChild(_testRole);
//    }
//}

//测试用
//int tempindex[4] = {Guest02, Guest07, Guest09, Guest10};
//void CEatingTest::addRole()
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    
//    for (int i = 0; i < 4; ++i) {
//        auto roleTemp = CEatingRoleBasic::create();
//        if (roleTemp) {
//            roleTemp->setPosition(visibleSize.width/5*(i + 1),visibleSize.height/5 * 3);
//            roleTemp->createObject(tempindex[i]);
//            roleTemp->initEyePos();
//            this->addChild(roleTemp);
//            m_testRoles.pushBack(roleTemp);
//            
////            auto _rect = roleTemp->getCollisionRange();
////            auto _layer = LayerColor::create(Color4B(255, 0, 0, 255));
////            this->addChild(_layer);
////            _layer->setPosition(_rect.origin);
////            _layer->setContentSize(_rect.size);
//        }
//    }
//}


void CEatingTest::addRole()
{
    int size = EatingRoleData::getInstance()->getSizeofRoleID();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    for (int i = 0; i < size; ++i) {
        int RoleID = EatingRoleData::getInstance()->getRoleID(i);
        if (RoleID > -1) {
            auto roleTemp = CEatingRoleBasic::create();
            if (roleTemp) {
                roleTemp->setPosition(visibleSize.width/5*(i + 1), visibleSize.height/5 * 3);
                roleTemp->createObject(RoleID);
                this->addChild(roleTemp);
                m_testRoles.pushBack(roleTemp);
            }
        }
    }
}

void CEatingTest::addTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CEatingTest::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CEatingTest::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CEatingTest::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(CEatingTest::onTouchCancelled, this);
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


bool CEatingTest::onTouchBegan(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    m_touch = _touch;
    //这里要判断有没有选择食物，测试时没有写
    for (int i = 0; i < m_foods.size(); ++i) {
        if (m_foods.at(i)->getBoundingBox().containsPoint(_touch->getLocation())) {
            
            m_tmp_food = m_foods.at(i);
            m_tmp_food_begin_pos = m_tmp_food->getPosition();
            
            for (int i = 0; i < m_testRoles.size(); ++i)
            {
                if (m_last_index == i) {
                    m_testRoles.at(i)->Wait(false, m_tmp_food);
                }
                else
                {
                    m_testRoles.at(i)->Wait(true, m_tmp_food);
                    m_last_index = i;
                }
                
            }
            schedule(schedule_selector(CEatingTest::FoodPositionUpdate));
            return true;
        }
    }
    
    return false;
}

void CEatingTest::onTouchMoved(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
//    auto _pos = _touch->getLocation();
//    for (auto _iter = m_testRoles.begin(); _iter < m_testRoles.end(); ++_iter) {
//        if ((*_iter)) {
//            if ((*_iter)->checkTouchPoint(_pos)) {
//                (*_iter)->Want();
//            }
//            else
//            {
//                (*_iter)->Wait();
//            }
//        }
//    }
    if (m_tmp_food) {
        m_tmp_food->setPosition(m_tmp_food->getPosition() + _touch->getDelta());
    }
}

void CEatingTest::onTouchEnded(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    auto _pos = _touch->getLocation();
    bool is_eated = false;
    if (m_tmp_food) {
        for (auto _iter = m_testRoles.begin(); _iter < m_testRoles.end(); ++_iter) {
            if ((*_iter)) {
                if ((*_iter)->checkCollision(m_tmp_food->getBoundingBox())) {
                    int _score = rand()%100;
                    int _sour = rand()%100;
                    int _hot = rand()%100;
                    (*_iter)->Eating(_score, _sour, _hot);
                    is_eated = true;
                }
                else
                {
                    (*_iter)->Default();
                }
            }
        }
        
        if (!is_eated) {
            m_tmp_food->setPosition(m_tmp_food_begin_pos);
            m_tmp_food = nullptr;
        }
        else
        {
            //本来吃了应该按下述的方法处理，但是为了保证测试的无限循环，现改为食物不会小时的版本
//            m_tmp_food->removeFromParent();
//            auto _iter = m_foods.find(m_tmp_food);
//            m_foods.erase(_iter);
//            m_tmp_food = nullptr;
            
            m_tmp_food->setPosition(m_tmp_food_begin_pos);
            m_tmp_food = nullptr;
            m_last_index = -1;
        }
    }
    
    unschedule(schedule_selector(CEatingTest::FoodPositionUpdate));
}


void CEatingTest::addFood()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    for (int i = 0; i < 4; ++i) {
        //setPosition(visibleSize.width/5*(i + 1),visibleSize.height/5 * 3);
        //CFood* _food = CGlobalData::getSingleton()->createFoodByInfo(i);
        CFood* _food = (CFood*)Sprite::create("food.png");
        if (_food) {
            _food->setPosition(visibleSize.width/5*(i + 1),visibleSize.height/5);
            this->addChild(_food);
            m_foods.pushBack(_food);
            log("food is not null!!");
        }
    }
}

void CEatingTest::FoodPositionUpdate(float dt)
{
    auto _pos = m_touch->getLocation();
    for (auto _iter = m_testRoles.begin(); _iter < m_testRoles.end(); ++_iter) {
        if ((*_iter)) {
            if ((*_iter)->checkCollision(m_tmp_food->getBoundingBox())) {
                (*_iter)->Want();
            }
            else
            {
                (*_iter)->Wait(false, m_tmp_food);
            }
        }
    }
}

void CEatingTest::addButton()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto _label = Label::createWithTTF("切换到厨房", "fonts/wawati.ttf", 60);
    _label->setColor(Color3B(255,255,255));
    _label->setPosition(visibleSize.width/3 * 2, visibleSize.height/2 + 50);
    this->addChild(_label);
    
    auto _menuItem2 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(CEatingTest::ButtonCallBack, this));
    _menuItem2->setPosition(visibleSize.width/3 * 2, visibleSize.height/2);
    _menuItem2->setTag(11);
    
    auto _menu = Menu::create();
    //_menu->addChild(_menuItem);
    _menu->addChild(_menuItem2);
    _menu->setPosition(Vec2::ZERO);
    this->addChild(_menu);
}

void CEatingTest::ButtonCallBack(cocos2d::Ref *ref)
{
    auto scene = BBQChooseLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}