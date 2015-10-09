//
//  BBQChooseLayer.cpp
//  testFridge
//
//  Created by kids on 15/8/27.
//
//

#include "BBQChooseLayer.h"
#include "EatingRoleData.h"
#include "Kitchen.h"
#include "CEatingTest.h"

static const float DistanceBuffer = 50;
static const int sprite_num = 12;
static const float Scale_Bigger = 0.9;
static const float Scale_Normal = 0.8;
const static float DELTA_HEIGHT = 50;
const static float DELTA_DESK_HEIGHT = 140;

enum BBQ_CHOOSEN_ZORDER
{
    WALL,
    CHAIR,
    ROLE,
    TABLE,
    CHOOSING_LAYER,
};

BBQChooseLayer::BBQChooseLayer():
m_choosing_layer(nullptr),
m_max_length(0),
m_min_length(0),
m_node_length(0),
m_interval_length(0),
m_begin_pos_x(0),
visibleSize(Size::ZERO),
NUM_NODE(sprite_num),
NODE_SPEED(1200),
LAYER_SPEED(300),
m_choosing_index(-1),
m_clicked_times(0),
m_is_in_choosing_layer(false),
m_chosen_index(-1),
m_countTime(0)
{
    m_choosing_nodes.clear();
    
    m_chosen_nodes.clear();
    
    m_labels.clear();
    
    m_pos_label_index.clear();
    

    for (int i = 0; i < MAX_ROLE_NUM; ++i) {
        std::string _boneXML = EATING_ROLE_MEMBERS_NAMES[i] + ".xml";
        DBCCFactory::getInstance()->loadDragonBonesData(_boneXML, EATING_ROLE_MEMBERS_NAMES[i]);
        std::string _textureXML = EATING_ROLE_MEMBERS_NAMES[i] + "0.xml";
        DBCCFactory::getInstance()->loadTextureAtlas(_textureXML, EATING_ROLE_MEMBERS_NAMES[i]);
    }
}

BBQChooseLayer::~BBQChooseLayer()
{
    m_choosing_nodes.clear();
    
    m_chosen_nodes.clear();
    
    m_labels.clear();
    
    m_pos_label_index.clear();
}


Scene* BBQChooseLayer::createScene()
{
    auto _scene = Scene::create();
    
    auto _layer = BBQChooseLayer::create();
    
    _scene->addChild(_layer);
    
    return _scene;
}

bool BBQChooseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //LayerColor* _layer = LayerColor::create(Color4B(255, 255, 0, 125));
    //this->addChild(_layer);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    addBackGround();
    
    addChoosingLayer();
    
    addTouch();
    
    addLabel();
    
    //测试用
    addButton();
    return true;
}

static const int pos_chair[4] = {
    -600,
    -210,
    210,
    600
};
void BBQChooseLayer::addBackGround()
{
    auto _wall = Sprite::create("wall.png");
    _wall->setPosition(visibleSize/2);
    this->addChild(_wall, WALL);
    
    auto _table = Sprite::create("table.png");
    _table->setPosition(visibleSize.width/2, visibleSize.height/2 - DELTA_DESK_HEIGHT);
    this->addChild(_table, TABLE);
    
    for (int i = 0; i < 4; ++i) {
        auto _chair = Sprite::create("chair.png");
        _chair->setPosition(visibleSize.width/2 + pos_chair[i], visibleSize.height/2 + 350 - DELTA_DESK_HEIGHT);
        this->addChild(_chair, CHAIR);
    }
}


void BBQChooseLayer::addTouch()
{
    auto _listener = EventListenerTouchOneByOne::create();
    _listener->onTouchBegan = CC_CALLBACK_2(BBQChooseLayer::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(BBQChooseLayer::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(BBQChooseLayer::onTouchEnded, this);
    _listener->onTouchCancelled = CC_CALLBACK_2(BBQChooseLayer::onTouchCancelled, this);
    _listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

bool BBQChooseLayer::onTouchBegan(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    auto _touch_pos = _touch->getLocation();
    m_is_in_choosing_layer = false;
    m_choosing_layer->stopAllActions();
    
    //触摸的行为是移动选项层，所以开启移动触摸时间定时器
    unschedule(schedule_selector(BBQChooseLayer::countTime));
    schedule(schedule_selector(BBQChooseLayer::countTime));
    m_countTime = 0;
    
    //开启判断点击是否在所点中的选项的头部
    m_temp = nullptr;
    m_isInHead = false;
    m_touch = _touch;
    unschedule(schedule_selector(BBQChooseLayer::searchForHead));
    schedule(schedule_selector(BBQChooseLayer::searchForHead));
    
    
    //判断触摸点击在不在选项层的node上
    for (int i = 0; i < m_choosing_nodes.size(); ++i)
    {
        Rect boundingBox = m_choosing_nodes.at(i)->getBoundingBox();
        if (boundingBox.containsPoint(m_choosing_layer->convertToNodeSpace(_touch_pos)))
        {
            m_choosing_index = i;
            m_temp = m_choosing_nodes.at(m_choosing_index);
            m_choosing_nodes.at(i)->setScale(Scale_Bigger);
            m_is_in_choosing_layer = true;
            
            ++m_clicked_times;
            
            if (m_clicked_times == 2) {
                auto _temp_node = BBQChoosingRole::create(m_choosing_nodes.at(m_choosing_index)->getRoleID());
                //_temp_node->playAnimation("Stand");
                _temp_node->playAnimation("Drag");
                _temp_node->setPosition(m_choosing_layer->convertToWorldSpace(m_choosing_nodes.at(m_choosing_index)->getPosition()));
                _temp_node->setScale(Scale_Bigger);
                this->addChild(_temp_node, CHOOSING_LAYER);
                
                m_temp = _temp_node;
                m_chosen_nodes.pushBack(_temp_node);
                m_choosing_nodes.at(m_choosing_index)->removeFromParent();
                m_choosing_nodes.erase(m_choosing_index);
                m_choosing_index = -1;
                
                m_isInHead = true;
                unschedule(schedule_selector(BBQChooseLayer::searchForHead));
                
                handleMoveOut();
            }
            
            m_chosen_index = -1;
            return true;
        }
    }
    
    //触控点击的范围是在选项层上,但是没点击到node
    if (m_choosing_layer->getBoundingBox().containsPoint(_touch_pos))
    {
        m_is_in_choosing_layer = true;
        m_chosen_index = -1;
        return true;
    }

    //触控点击的范围不在选项或选项框上，而是在主场景中的node上
    for (int i = 0; i < m_chosen_nodes.size(); ++i)
    {
        Rect boundingBox = m_chosen_nodes.at(i)->getBoundingBox();
        if (boundingBox.containsPoint(_touch_pos)) {
            m_is_in_choosing_layer = false;
            //if (i == m_chosen_index) {
                m_chosen_nodes.at(i)->stopAllActions();
            //}
            m_chosen_index = i;
            m_temp = m_chosen_nodes.at(m_chosen_index);
            m_temp->playAnimation("Drag");
            m_temp->setZOrder(CHOOSING_LAYER);
            m_chosen_nodes.at(i)->setScale(Scale_Bigger);
            return true;
        }
    }
    
    return false;
}


void BBQChooseLayer::onTouchMoved(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    if (m_is_in_choosing_layer)
    { //在选择层进行的点击
        if (m_clicked_times < 2)
        { //点击一次不进行对选项层里的精灵进行移动，而是选项层进行移动
            if (m_choosing_index != -1 && m_isInHead)
            {//此时触摸的高度高于选择层的高度，此时应将被点击的node拖出
                m_temp = nullptr;
                unschedule(schedule_selector(BBQChooseLayer::searchForHead));
                
                m_clicked_times = 2;
                
                auto _temp_node = BBQChoosingRole::create(m_choosing_nodes.at(m_choosing_index)->getRoleID());
                _temp_node->playAnimation("Drag");
                _temp_node->setPosition(m_choosing_layer->convertToWorldSpace(m_choosing_nodes.at(m_choosing_index)->getPosition()));
                _temp_node->setScale(Scale_Bigger);
                this->addChild(_temp_node, CHOOSING_LAYER);
                
                m_chosen_nodes.pushBack(_temp_node);
                m_choosing_nodes.at(m_choosing_index)->removeFromParent();
                m_choosing_nodes.erase(m_choosing_index);
                m_choosing_index = -1;
                
                handleMoveOut();
            }
            else
            {
                if (m_clicked_times == 1)
                { //只要有移动，点击次数就重新计算
                    m_clicked_times = 0;
                }
                if (m_max_length - m_min_length <= 0)
                {  //此时不能对层进行移动
                    return;
                }
                m_choosing_layer->setPositionX(m_choosing_layer->getPositionX() + _touch->getDelta().x);
                auto _pos_x = m_choosing_layer->getPositionX();
                if (_pos_x < m_min_length)
                {
                    m_choosing_layer->setPositionX(m_min_length);
                }
                else if (_pos_x > m_max_length)
                {
                    m_choosing_layer->setPositionX(m_max_length);
                }
                return;
            }
        }
        else
        {
            auto _temp_node = m_chosen_nodes.at(m_chosen_nodes.size() - 1);
            if (m_isInHead) {
                m_temp = nullptr;
                unschedule(schedule_selector(BBQChooseLayer::searchForHead));
                
                _temp_node->setPosition(_temp_node->getPosition() + _touch->getDelta());
            }
        }
    }
    else
    {
        if (m_chosen_index != -1) {
            auto _temp_node = m_chosen_nodes.at(m_chosen_index);
            if (m_isInHead) {
                m_temp = nullptr;
                unschedule(schedule_selector(BBQChooseLayer::searchForHead));
                
                _temp_node->setPosition(_temp_node->getPosition() + _touch->getDelta());
            }
        }
    }
}

void BBQChooseLayer::onTouchEnded(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    unschedule(schedule_selector(BBQChooseLayer::countTime));
    unschedule(schedule_selector(BBQChooseLayer::searchForHead));
    m_isInHead = false;
    m_touch = nullptr;
    
    if (m_is_in_choosing_layer)
    {//在选择层进行的点击
        if (m_clicked_times == 2)
        {
            m_clicked_times = 1;
            Rect boundingBox = m_chosen_nodes.at(m_chosen_nodes.size() - 1)->getBoundingBox();
            if (!m_choosing_layer->getBoundingBox().intersectsRect(boundingBox))
            {
                for (int i = 0; i < m_labels.size(); ++i) {
                    auto _temp_node = m_chosen_nodes.at(m_chosen_nodes.size() - 1);
                    Rect _temp_node_boundingbox = _temp_node->getBoundingBox();
                    auto _labelBox = m_labels.at(i)->getBoundingBox();
                    Rect _label_rect = Rect(_labelBox.origin.x - 50, _labelBox.origin.y - 50, _labelBox.size.width + 100, _labelBox.size.height + 100);
                    if (_label_rect.intersectsRect(_temp_node_boundingbox)) {
                        float _time = (m_chosen_nodes.at(m_chosen_nodes.size() - 1)->getPosition() - m_labels.at(i)->getPosition()).length()/(NODE_SPEED* 3);
                        //log("_time1 = %f", _time);
                        auto _moveTo = MoveTo::create(_time, m_labels.at(i)->getPosition());
                        auto _seq = Sequence::createWithTwoActions(_moveTo, CallFunc::create([this](){m_chosen_nodes.at(m_chosen_nodes.size() - 1)->playAnimation("Sit");}));
                        m_chosen_nodes.at(m_chosen_nodes.size() - 1)->stopAllActions();
                        m_chosen_nodes.at(m_chosen_nodes.size() - 1)->setZOrder(ROLE);
                        m_chosen_nodes.at(m_chosen_nodes.size() - 1)->runAction(_seq);
                        m_chosen_nodes.at(m_chosen_nodes.size() - 1)->setScale(Scale_Normal);
                        
                        //这里才是确定是否有元素被添加到m_chosen_nodes中去
                        m_pos_label_index.push_back(i);
                        //判断这个位置上是否已经有东西了
                        for (int j = 0; j < m_pos_label_index.size() - 1; ++j) {
                            if (m_pos_label_index.at(j) == i) {
                                m_chosen_index = j;
                                handleMoveIn();
                                
                                m_pos_label_index.erase(m_pos_label_index.begin() + j);
                                m_chosen_nodes.at(m_chosen_index)->removeFromParent();
                                m_chosen_nodes.erase(m_chosen_index);
                                break;
                            }
                        }
                        
                        return;
                    }
                }
            }
            m_chosen_index = m_chosen_nodes.size() - 1;
            handleMoveIn();
            
            m_chosen_nodes.at(m_chosen_index)->removeFromParent();
            m_chosen_nodes.erase(m_chosen_index);
        }
        else
        {   //此时为对层的左右移动操作，需要进行缓动
            if (m_choosing_index != -1) {
                m_choosing_nodes.at(m_choosing_index)->setScale(Scale_Normal);
                m_choosing_nodes.at(m_choosing_index)->playAnimation("Stand");
                m_choosing_index = -1;
            }
            
            afterTouchLayerMoved(_touch);
        }
    }
    else
    { //在主场景中进行的点击
        if (m_chosen_index != -1)
        {
            //拖回选择层
            if (m_choosing_layer->getBoundingBox().intersectsRect(m_chosen_nodes.at(m_chosen_index)->getBoundingBox())) {
                handleMoveIn();
                
                m_chosen_nodes.at(m_chosen_index)->removeFromParent();
                m_chosen_nodes.erase(m_chosen_index);
                //这里确定是不是要删除主场景中已经被选择的元素
                m_pos_label_index.erase(m_pos_label_index.begin() + m_chosen_index);
            }
            else
            {   //没有拖回选择层
                for (int i = 0; i < m_labels.size(); ++i)
                {
                    auto _temp_node = m_chosen_nodes.at(m_chosen_index);
                    _temp_node->setScale(Scale_Normal);
                    _temp_node->setZOrder(CHOOSING_LAYER);
                    auto _labelBox = m_labels.at(i)->getBoundingBox();
                    Rect _label_rect = Rect(_labelBox.origin.x - 50, _labelBox.origin.y - 50, _labelBox.size.width + 100, _labelBox.size.height + 100);
                    
                    if (_label_rect.intersectsRect(_temp_node->getBoundingBox()))
                    {
                        //判断这个位置上是否已经有东西了
                        for (int j = 0; j < m_pos_label_index.size(); ++j) {
                            if (m_pos_label_index.at(j) == i && m_chosen_index != j) {
                                m_pos_label_index.at(j) = m_pos_label_index.at(m_chosen_index);
                                auto _temp_pos = m_labels.at(m_pos_label_index.at(j))->getPosition();
                                float _time = (m_chosen_nodes.at(j)->getPosition() - _temp_pos).length()/(NODE_SPEED * 3);
                                log("_time2 = %f", _time);
                                auto _moveTo = MoveTo::create(_time, _temp_pos);
                                //这里的置为-1因为延时会有问题
                                auto _temp_node = m_chosen_nodes.at(j);
                                _temp_node->setZOrder(ROLE);
                                auto _seq = Sequence::createWithTwoActions(_moveTo, CallFunc::create([this, _temp_node](){_temp_node->playAnimation("Sit");}));
                                m_chosen_nodes.at(j)->stopAllActions();
                                m_chosen_nodes.at(j)->runAction(_seq);
                                break;
                            }
                        }
                        m_pos_label_index.at(m_chosen_index) = i;
                        break;
                    }
                }
                auto _temp_pos = m_labels.at(m_pos_label_index.at(m_chosen_index))->getPosition();
                float _time = (m_chosen_nodes.at(m_chosen_index)->getPosition() - _temp_pos).length()/(NODE_SPEED * 3);
                log("_time3 = %f", _time);
                auto _moveTo = MoveTo::create(_time, _temp_pos);
                //这里的置为-1因为延时会有问题
                auto _temp_node = m_chosen_nodes.at(m_chosen_index);
                _temp_node->setZOrder(ROLE);
                auto _seq = Sequence::createWithTwoActions(_moveTo, CallFunc::create([this, _temp_node](){_temp_node->playAnimation("Sit");}));
                m_chosen_nodes.at(m_chosen_index)->stopAllActions();
                m_chosen_nodes.at(m_chosen_index)->runAction(_seq);
                
            }
        }
    }
}

void BBQChooseLayer::onTouchCancelled(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    this->onTouchEnded(_touch, _event);
}

void BBQChooseLayer::calcLength()
{
    m_max_length = 0;
    m_min_length = -visibleSize.width - 800;
    
    //auto _sprite = Sprite::create("Icon.png");
    m_node_length = 250;
    m_interval_length = (m_max_length - m_min_length + visibleSize.width - sprite_num * m_node_length) / (sprite_num + 1);
    
    m_begin_pos_x = m_interval_length + m_node_length/2;
}

void BBQChooseLayer::addChoosingLayer()
{
    calcLength();
    
    m_choosing_layer = Layer::create();
    m_choosing_layer->setContentSize(Size(m_max_length - m_min_length + visibleSize.width, 324));
    m_choosing_layer->setPosition(Vec2::ZERO);
    this->addChild(m_choosing_layer, CHOOSING_LAYER);
    
    auto _back = Sprite::create("chooseback.png");
    _back->setAnchorPoint(Vec2::ZERO);
    _back->setPosition(Vec2::ZERO);
    m_choosing_layer->addChild(_back);
    
    _back = Sprite::create("chooseback.png");
    _back->setAnchorPoint(Vec2::ZERO);
    _back->setPosition(_back->getBoundingBox().size.width, 0);
    m_choosing_layer->addChild(_back);
    
    for (int i = 0; i < NUM_NODE; ++i) {
        auto roleID = i % MAX_ROLE_NUM;
        auto _sprite = BBQChoosingRole::create(roleID);
        _sprite->playAnimation("Stand");
        _sprite->setScale(Scale_Normal);
        _sprite->setPosition(m_begin_pos_x + (m_node_length + m_interval_length) * i, _sprite->getBoundingBox().size.height/2 + DELTA_HEIGHT);
        m_choosing_layer->addChild(_sprite);
        m_choosing_nodes.pushBack(_sprite);
    }
}

std::string BBQLABEL[4] = {"1", "2", "3", "4"};
void BBQChooseLayer::addLabel()
{
    for (int i = 0; i < 4; ++i) {
        auto _label = Label::createWithTTF(BBQLABEL[i], "fonts/arial.ttf", 60);
        _label->setColor(Color3B(255,255,255));
        _label->setPosition(visibleSize.width/5 * (i + 1), visibleSize.height/4 * 3 - DELTA_DESK_HEIGHT);
        this->addChild(_label);
        m_labels.pushBack(_label);
    }
}

void BBQChooseLayer::addButton()
{
//    auto _menuItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(BBQChooseLayer::ButtonCallBack, this));
//    _menuItem->setPosition(visibleSize.width/3, visibleSize.height/2);
//    _menuItem->setTag(10);
    
    auto _label = Label::createWithTTF("切换到厨房", "fonts/wawati.ttf", 60);
    _label->setColor(Color3B(255,255,255));
    _label->setPosition(visibleSize.width/3 * 2, visibleSize.height/2 + 50);
    this->addChild(_label, 10);
    
    auto _menuItem2 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(BBQChooseLayer::ButtonCallBack, this));
    _menuItem2->setPosition(visibleSize.width/3 * 2, visibleSize.height/2);
    _menuItem2->setTag(11);
    
    auto _menu = Menu::create();
    //_menu->addChild(_menuItem);
    _menu->addChild(_menuItem2);
    _menu->setPosition(Vec2::ZERO);
    this->addChild(_menu, 10);
}

void BBQChooseLayer::ButtonCallBack(Ref* ref)
{
    MenuItemImage* _temp = (MenuItemImage*)ref;
    if (_temp->getTag() == 10) {
        static bool _flag = true;
        if (_flag)
        {
            ChoosingLayerAppear();
            _flag = false;
        }
        else
        {
            ChoosingLayerDisappear();
            _flag = true;
        }

    }
    else
    {
        ChangeLayer();
    }
}

void BBQChooseLayer::handleMoveOut()
{
    m_choosing_layer->stopAllActions();
    
    if (m_max_length - m_min_length > 0) {
        auto _pos_layer = m_choosing_layer->getPositionX();
        if (_pos_layer - m_min_length < (m_interval_length + m_node_length)/2) {
            auto _delta = (m_interval_length + m_node_length)/2 - (_pos_layer - m_min_length);
            auto _time = fabsf(_delta)/LAYER_SPEED;
            auto _moveTo = MoveTo::create(_time, Vec2(_pos_layer + _delta, m_choosing_layer->getPositionY()));
            m_choosing_layer->runAction(_moveTo);
        }
        else if (m_max_length - _pos_layer < (m_interval_length + m_node_length)/2)
        {
            auto _delta = (m_interval_length + m_node_length)/2 - (m_max_length - _pos_layer);
            auto _time = fabsf(_delta)/LAYER_SPEED;
            auto _moveTo = MoveTo::create(_time, Vec2(_pos_layer - _delta, m_choosing_layer->getPositionY()));
            m_choosing_layer->runAction(_moveTo);
        }
    }
    
    m_min_length += (m_interval_length + m_node_length)/2;
    m_max_length -= (m_interval_length + m_node_length)/2;
    m_begin_pos_x += (m_interval_length + m_node_length)/2;
    
    if (m_max_length - m_min_length < 0) {
        auto _pos_layer = m_choosing_layer->getPositionX();
        auto length = visibleSize.width + m_max_length - m_min_length;
        auto _mid_node = m_begin_pos_x - m_interval_length - m_node_length/2 + length/2;
        auto _visible_mid = m_choosing_layer->convertToNodeSpace(visibleSize/2).x;
        auto _delta = _mid_node - _visible_mid;
        if (_delta) {
            auto _moveTo =  MoveTo::create(0.04, Vec2(_pos_layer - _delta, m_choosing_layer->getPositionY()));
            m_choosing_layer->runAction(_moveTo);
        }
    }
    
    for (int i = 0; i < m_choosing_nodes.size(); ++i) {
        float _time = fabsf(m_choosing_nodes.at(i)->getPositionX() - m_begin_pos_x - (m_interval_length + m_node_length) * i)/NODE_SPEED;
        auto _moveTo = MoveTo::create(_time, Vec2(m_begin_pos_x + (m_interval_length + m_node_length) * i, m_choosing_nodes.at(i)->getPositionY()));
        m_choosing_nodes.at(i)->stopAllActions();
        m_choosing_nodes.at(i)->runAction(_moveTo);
    }
}


void BBQChooseLayer::handleMoveIn()
{
    m_choosing_layer->stopAllActions();
    auto _chosen_node = m_chosen_nodes.at(m_chosen_index);
    _chosen_node->setZOrder(CHOOSING_LAYER);
    auto _pos_node = m_choosing_layer->convertToNodeSpace(_chosen_node->getPosition());
    
    m_min_length -= (m_interval_length + m_node_length)/2;
    m_max_length += (m_interval_length + m_node_length)/2;
    m_begin_pos_x -= (m_interval_length + m_node_length)/2;
    
    auto _temp_node = BBQChoosingRole::create(_chosen_node->getRoleID());
    _temp_node->playAnimation("Stand");
    _temp_node->setScale(Scale_Normal);
    m_choosing_layer->addChild(_temp_node);
    _temp_node->setPosition(_pos_node);
    
    int _size = m_choosing_nodes.size();
    if (!m_choosing_nodes.size())
    {   //在没有元素的时候插入
        m_choosing_nodes.pushBack(_temp_node);
    }
    else if (m_choosing_nodes.at(0)->getPositionX() > _pos_node.x)
    {   //在第一个之前插入
        m_choosing_nodes.insert(0, _temp_node);
    }
    else if (m_choosing_nodes.at(_size - 1)->getPositionX() < _pos_node.x)
    {   //往最后插入
        m_choosing_nodes.insert(_size, _temp_node);
    }
    else
    {
        int i = 0;
        for (; i < m_choosing_nodes.size() - 1; ++i) {
            if (m_choosing_nodes.at(i)->getPositionX() <= _pos_node.x && m_choosing_nodes.at(i + 1)->getPositionX() >= _pos_node.x) {
                m_choosing_nodes.insert(i + 1, _temp_node);
                break;
            }
        }
    }
    
    for (int i = 0; i < m_choosing_nodes.size(); ++i) {
        //float _time = (m_choosing_nodes.at(i)->getPosition() - Vec2(m_begin_pos_x + (m_interval_length + m_node_length) * i, m_choosing_nodes.at(i)->getBoundingBox().size.height/2)).length()/NODE_SPEED;
        //float _time = fabsf(m_choosing_nodes.at(i)->getPositionX() - m_begin_pos_x - (m_interval_length + m_node_length) * i)/(NODE_SPEED);
        float _time = 0.3;
        auto _moveTo = MoveTo::create(_time, Vec2(m_begin_pos_x + (m_interval_length + m_node_length) * i, m_choosing_nodes.at(i)->getBoundingBox().size.height/2 + DELTA_HEIGHT));
        m_choosing_nodes.at(i)->stopAllActions();
        m_choosing_nodes.at(i)->runAction(_moveTo);
    }
}

void BBQChooseLayer::ChoosingLayerAppear()
{
    if (!m_choosing_nodes.size()) {
        return;
    }
    
    for (int i = 0; i < m_choosing_nodes.size(); ++i) {
        float _time = fabsf(m_choosing_nodes.at(i)->getPositionX() - m_begin_pos_x - (m_interval_length + m_node_length) * i)/NODE_SPEED;
        auto _moveTo = MoveTo::create(_time, Vec2(m_begin_pos_x + (m_interval_length + m_node_length) * i, m_choosing_layer->getBoundingBox().size.height/2));
        m_choosing_nodes.at(i)->stopAllActions();
        m_choosing_nodes.at(i)->runAction(_moveTo);
    }
}


void BBQChooseLayer::ChoosingLayerDisappear()
{
    if (!m_choosing_nodes.size()) {
        return;
    }
    
    //选择层的元素向两边移动时的目的位置的X坐标
    auto _posX_left = m_choosing_layer->convertToNodeSpace(Vec2(0 - m_interval_length - m_node_length, 0)).x;
    auto _posX_right = m_choosing_layer->convertToNodeSpace(Vec2(visibleSize.width + m_interval_length + m_node_length, 0)).x;
    
    int _index = 0;
    auto _mid_x_node = m_choosing_layer->convertToNodeSpace(visibleSize/2).x;
    for (; _index < m_choosing_nodes.size() - 1; ++_index) {
        auto _posX_before = m_choosing_nodes.at(_index)->getPositionX();
        auto _posX_after = m_choosing_nodes.at(_index + 1)->getPositionX();
        if (_posX_before <= _mid_x_node && _posX_after > _mid_x_node) {
            break;
        }
    }
    
    for (int i = 0; i <= _index; ++i) {
        float _time = (m_choosing_nodes.at(i)->getPositionX() - _posX_left)/NODE_SPEED;
        auto _moveTo = MoveTo::create(_time, Vec2(_posX_left, m_choosing_nodes.at(i)->getPositionY()));
        m_choosing_nodes.at(i)->stopAllActions();
        m_choosing_nodes.at(i)->runAction(_moveTo);
    }
    
    for (int i = _index + 1; i < m_choosing_nodes.size(); ++i) {
        float _time = (_posX_right - m_choosing_nodes.at(i)->getPositionX())/NODE_SPEED;
        auto _moveTo = MoveTo::create(_time, Vec2(_posX_right, m_choosing_nodes.at(i)->getPositionY()));
        m_choosing_nodes.at(i)->stopAllActions();
        m_choosing_nodes.at(i)->runAction(_moveTo);
    }
}

void BBQChooseLayer::afterTouchLayerMoved(cocos2d::Touch *_touch)
{
    auto _touch_distance = _touch->getLocation() - _touch->getStartLocation();
    if (m_countTime < 15 && fabsf(_touch_distance.x) > DistanceBuffer) {
        auto _touch_deltaX = _touch_distance.x;
        auto _pos_x = m_choosing_layer->getPositionX();
        if (_pos_x + _touch_deltaX > m_max_length) {
            _touch_deltaX = m_max_length - _pos_x;
        }
        else if(_pos_x + _touch_deltaX < m_min_length)
        {
            _touch_deltaX = m_min_length - _pos_x;
        }
        auto _action = EaseSineOut::create(MoveBy::create(0.8, Vec2(_touch_deltaX, 0)));
        m_choosing_layer->runAction(_action);
    }
}

void BBQChooseLayer::countTime(float dt)
{
    ++m_countTime;
}


Rect BBQChooseLayer::GetArmatureRect(dragonBones::DBCCArmatureNode *temp)
{
    float fX = temp->getPositionX();
    float fY = temp->getPositionY();
    auto armatureBox = temp->getBoundingBox().size * temp->getScale();
    //log("width = %f, height = %f, scale = %f", armatureBox.width, armatureBox.height, temp->getScale());
    Rect collisionRange = Rect(fX - armatureBox.width/2, fY, armatureBox.width, armatureBox.height);
    return collisionRange;
}


void BBQChooseLayer::searchForHead(float dt)
{
//    if (m_touch) {
//        if (m_temp) {
//            if (m_temp->isTouchHead(m_touch)) {
//                m_temp->playAnimation("Drag");
//                m_isInHead = true;
//                unschedule(schedule_selector(BBQChooseLayer::searchForHead));
//            }
//        }
//    }
    
    if (m_touch) {
        if (m_touch->getLocation().y > visibleSize.height/3) {
            m_isInHead = true;
            unschedule(schedule_selector(BBQChooseLayer::searchForHead));
        }
    }
}


void BBQChooseLayer::ChangeLayer()
{
    for (int i = 0; i < m_pos_label_index.size(); ++i) {
        EatingRoleData::getInstance()->saveRoleID(m_pos_label_index.at(i), m_chosen_nodes.at(i)->getRoleID());
        log("_index = %d, roleID = %d", m_pos_label_index.at(i), m_chosen_nodes.at(i)->getRoleID());
    }
    
    if (m_pos_label_index.size()) {
        //auto scene = CKitchen::createScene();
        auto scene = CEatingTest::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}