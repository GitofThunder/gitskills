//
//  CEatingRoleBasic.cpp
//  TravelDemo
//
//  Created by kids on 15/8/24.
//
//

#include "CEatingRoleBasic.h"
using namespace std;

CEatingRoleBasic::CEatingRoleBasic()
{
    m_between_index = 1;
    m_food_score = 0;
    m_animation_state = nullptr;
    m_touch = nullptr;
    m_first_flag = true;
    _count_step = 10;
    m_eat_times = 0;
    m_change_to_default = false;
    m_food = nullptr;
    
    m_eye_name.clear();
    m_eye_name_extra.clear();
}

CEatingRoleBasic::~CEatingRoleBasic()
{
    armature->getCCEventDispatcher()->removeAllEventListeners();
    _eventDispatcher->removeEventListener(_listener);
}

bool CEatingRoleBasic::createArmature(int RoleID)
{
    if (RoleID >= MAX_ROLE_NUM) {
        return false;
    }
    
    roleID = RoleID;
    
    const char* buf = EATING_ROLE_MEMBERS_NAMES[roleID].c_str();
    armature = DBCCFactory::getInstance()->buildArmatureNode(buf);
    this->addChild(armature);
    return true;
}


bool CEatingRoleBasic::createObject(int _RoleID)
{    
    if (createArmature(_RoleID)) {
        m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
        
        //添加动画的事件处理
        armature->getCCEventDispatcher()->addCustomEventListener(EventData::COMPLETE, CC_CALLBACK_1(CEatingRoleBasic::eventHandler, this));
        armature->getCCEventDispatcher()->addCustomEventListener(EventData::LOOP_COMPLETE, CC_CALLBACK_1(CEatingRoleBasic::eventHandler, this));
        
        setCollisionRange();
        //这里的几个参数比较重要，他们决定了人物的嘴的碰撞区域大小
        float _temp_width = 100;
        float _temp_height_origin = 110;
        float _temp_height = 50;
        float fOriginX = collisionRange.origin.x;
        float fOriginY = collisionRange.origin.y;
        float fWidth = collisionRange.size.width;
        float fHeight = collisionRange.size.height;
        //if (_RoleID == Guest04) {
            collisionRange.setRect(fOriginX + _temp_width, fOriginY + _temp_height_origin, fWidth - 2 * _temp_width, _temp_height);
        //}
//        if (_RoleID == Guest05) {
//            collisionRange.setRect(fOriginX + _temp_width, fOriginY + _temp_height_origin, fWidth - 2 * _temp_width, _temp_height);
//        }
        
        //设置眼睛的名称
        m_eye_name = EATING_ROLE_EYES_NAMES[roleID * 2];
        m_eye_name_extra = EATING_ROLE_EYES_NAMES[roleID * 2 + 1];
        
        initEyePos();
        
        _listener = EventListenerTouchOneByOne::create();
        _listener->onTouchBegan = CC_CALLBACK_2(CEatingRoleBasic::onTouchBegan, this);
        _listener->onTouchMoved = CC_CALLBACK_2(CEatingRoleBasic::onTouchMoved, this);
        _listener->onTouchEnded = CC_CALLBACK_2(CEatingRoleBasic::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
        
        return true;
    }
    
    return false;
}


void CEatingRoleBasic::playAnimation(const char *pAniName)
{
    if (pAniName == NULL) {
        return;
    }
    
    m_animation_state = armature->getAnimation()->gotoAndPlay(pAniName);
//    if (strncmp(pAniName, "Default", 7)) {
//        roleState = AS_DEFAULT;
//    }
//    else if (strncmp(pAniName, "Click", 5))
//    {
//        roleState = AS_CLICK;
//    }
//    else
//    {
//        roleState = AS_OTHER;
//    }
}

void CEatingRoleBasic::setCollisionRange()
{
    armature->advanceTime(0);
    armatureBox = armature->getBoundingBox();
    //float fX = DB_ROLE_POSITION[roleID].x;
    //float fY = DB_ROLE_POSITION[roleID].y;
    float fX = this->getPositionX();
    float fY = this->getPositionY();
    collisionRange = Rect(fX - armatureBox.size.width/2, fY, armatureBox.size.width, armatureBox.size.height);
}

void CEatingRoleBasic::initEyePos()
{
    //对眼睛有关的数据进行赋值
    m_offset_y = 264;
    m_offset_length = 9;
    
    m_eyes_pos = Vec2(this->getPositionX(), this->getPositionY() + m_offset_y);
}

void CEatingRoleBasic::eventHandler(EventCustom* event)
{
    EventData* eventData = static_cast<EventData*>(event->getUserData());
    
    switch (eventData->getType()) {
        case EventData::EventType::COMPLETE:
        {
            //如果动画循环播放完毕有相应的事要做，在这里处理
            if (strcmp(eventData->animationState->name.c_str(), "eat") == 0) {
                
                afterEating();
                break;
                
            }
            else if (strcmp(eventData->animationState->name.c_str(), "like01") == 0) {
                
                m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                break;
                
            }
            else if (strcmp(eventData->animationState->name.c_str(), "like02") == 0) {
                
                m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                break;
                
            }
            else if (strcmp(eventData->animationState->name.c_str(), "normal") == 0) {
                
                m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                break;
                
            }
            else if (strcmp(eventData->animationState->name.c_str(), "hate01") == 0) {
                if (m_taste == -1) {
                    
                    m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                    
                }
                else if (m_taste == TT_SUAN)
                {
                    m_animation_state = armature->getAnimation()->gotoAndPlay("sour");
                }
                else if (m_taste == TT_LA)
                {
                    m_animation_state = armature->getAnimation()->gotoAndPlay("hot");
                }
                break;
            }
            else if (strcmp(eventData->animationState->name.c_str(), "hate02") == 0) {
                if (m_taste == -1) {
                    
                    m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                    
                }
                else if (m_taste == TT_SUAN)
                {
                    m_animation_state = armature->getAnimation()->gotoAndPlay("sour");
                }
                else if (m_taste == TT_LA)
                {
                    m_animation_state = armature->getAnimation()->gotoAndPlay("hot");
                }
                break;
            }
            else if (strcmp(eventData->animationState->name.c_str(), "sour") == 0) {
                
                m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                break;
                
            }
            else if (strcmp(eventData->animationState->name.c_str(), "hot") == 0) {
                
                m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                break;
                
            }
            else if (strcmp(eventData->animationState->name.c_str(), "overeat") == 0) {
                
                m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                break;
                
            }
           
            for (int i = 0; i < EATING_ROLE_ARMATURE_BETWEEN_NUM[roleID]; ++i) {
                char buf[12];
                sprintf(buf, "between0%d", i + 1);
                if (strcmp(eventData->animationState->name.c_str(), buf) == 0) {
                    m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                    break;
                }
            }
            break;
        }
        case EventData::EventType::LOOP_COMPLETE:
        {
            if (strcmp(eventData->animationState->name.c_str(), "Default") == 0) {
                
                playBetween();
                
            }
            else if (strcmp(eventData->animationState->name.c_str(), "want01") == 0) {
                if (m_change_to_default) {
                    
                    m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
                    m_change_to_default = false;
                    
                }
            }
            break;
        }

        default:
            break;
    }
}

bool CEatingRoleBasic::checkTouchPoint(const cocos2d::Vec2 &_touch)
{
    //log("min.x = %f, min.y = %f, max.x = %f, max.y = %f", collisionRange.getMinX(), collisionRange.getMinY(), collisionRange.getMaxX(), collisionRange.getMaxY());
    return collisionRange.containsPoint(_touch);
}

bool CEatingRoleBasic::checkCollision(cocos2d::Rect rect)
{
    return collisionRange.intersectsRect(rect);
}

//测试
bool CEatingRoleBasic::checkOpenMouse(cocos2d::Rect _rect)
{
    return m_openMouse_collision.intersectsRect(_rect);
}


Rect CEatingRoleBasic::getCollisionRange()
{
    return collisionRange;
}

bool CEatingRoleBasic::onTouchBegan(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    unschedule(schedule_selector(CEatingRoleBasic::EyesReset));
    schedule(schedule_selector(CEatingRoleBasic::BeginEyesMove), 0.02);
    
    m_end_offset = Vec2(0, 0);
    m_touch = _touch;
    return true;
}

void CEatingRoleBasic::onTouchMoved(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
}

void CEatingRoleBasic::onTouchEnded(cocos2d::Touch *_touch, cocos2d::Event *_event)
{
    unschedule(schedule_selector(CEatingRoleBasic::BeginEyesMove));
    unschedule(schedule_selector(CEatingRoleBasic::EyesMove));
    
    m_end_offset = Vec2(armature->getArmature()->getSlot(m_eye_name)->offset.x, armature->getArmature()->getSlot(m_eye_name)->offset.y);
    
    if (m_end_offset.length()) {
        schedule(schedule_selector(CEatingRoleBasic::EyesReset));
    }
    
    if (!m_eye_name_extra.empty()) {
        m_end_offset_extra = Vec2(armature->getArmature()->getSlot(m_eye_name_extra)->offset.x, armature->getArmature()->getSlot(m_eye_name_extra)->offset.y);
    }
    
    m_first_flag = true;

}

void CEatingRoleBasic::EyesReset(float dt)
{
    Vec2 _step = m_end_offset/10;
    
    armature->getAnimation()->stop();
    armature->getArmature()->getSlot(m_eye_name)->offset.x = armature->getArmature()->getSlot(m_eye_name)->offset.x - _step.x;
    armature->getArmature()->getSlot(m_eye_name)->offset.y = armature->getArmature()->getSlot(m_eye_name)->offset.y - _step.y;
    
    if (!m_eye_name_extra.empty())
    {
        Vec2 _step_extra = m_end_offset_extra/10;
        
        armature->getArmature()->getSlot(m_eye_name_extra)->offset.x = armature->getArmature()->getSlot(m_eye_name_extra)->offset.x - _step_extra.x;
        armature->getArmature()->getSlot(m_eye_name_extra)->offset.y = armature->getArmature()->getSlot(m_eye_name_extra)->offset.y - _step_extra.y;
    }
    
    --_count_step;
    if (!_count_step) {
        armature->getArmature()->getSlot(m_eye_name)->offset.x = 0;
        armature->getArmature()->getSlot(m_eye_name)->offset.y = 0;
        if (!m_eye_name_extra.empty()) {
            armature->getArmature()->getSlot(m_eye_name_extra)->offset.x = 0;
            armature->getArmature()->getSlot(m_eye_name_extra)->offset.y = 0;
        }
        unschedule(schedule_selector(CEatingRoleBasic::EyesReset));
        _count_step = 10;
    }
    armature->getAnimation()->play();
}

void CEatingRoleBasic::BeginEyesMove(float dt)
{

    schedule(schedule_selector(CEatingRoleBasic::EyesMove));
    unschedule(schedule_selector(CEatingRoleBasic::BeginEyesMove));
}

void CEatingRoleBasic::EyesMove(float dt)
{
    if (m_animation_state) {
        if (m_animation_state->name == "want01" || m_animation_state->name == "want02")
        {
            if(roleID == Guest07)
            {
                auto _vect = m_touch->getLocation() - m_eyes_pos;
                auto _temp = _vect/_vect.getLength() * m_offset_length;
                
                log("_temp.x = %f", _temp.x);
                
                armature->getAnimation()->stop();
                armature->getArmature()->getSlot(m_eye_name)->offset.x = -_temp.x;
                armature->getArmature()->getSlot(m_eye_name)->offset.y = -_temp.y;
                
                if (!m_eye_name_extra.empty()) {
                    armature->getArmature()->getSlot(m_eye_name_extra)->offset.x = _temp.x;
                    armature->getArmature()->getSlot(m_eye_name_extra)->offset.y = -_temp.y;
                }
                armature->getAnimation()->play();
            }
            else
            {
                auto _vect = m_touch->getLocation() - m_eyes_pos;
                auto _temp = _vect/_vect.getLength() * m_offset_length;
                
                armature->getAnimation()->stop();
                armature->getArmature()->getSlot(m_eye_name)->offset.x = _temp.x;
                armature->getArmature()->getSlot(m_eye_name)->offset.y = -_temp.y;
                
                if (!m_eye_name_extra.empty()) {
                    armature->getArmature()->getSlot(m_eye_name_extra)->offset.x = _temp.x;
                    armature->getArmature()->getSlot(m_eye_name_extra)->offset.y = -_temp.y;
                }
                armature->getAnimation()->play();
            }
        }
    }
}

int CEatingRoleBasic::getRoleID()
{
    return roleID;
}


void CEatingRoleBasic::Eating(float _food_score, float _sour_degree, float _hot_degree)
{
    m_food_score = _food_score;
    m_sour_degree = _sour_degree;
    m_hot_degree = _hot_degree;
    
    m_animation_state = armature->getAnimation()->gotoAndPlay("eat");
    ++m_eat_times;
}

void CEatingRoleBasic::Drinking(float _food_score, float _sour_degree, float _hot_degree)
{
    m_food_score = _food_score;
    m_sour_degree = _sour_degree;
    m_hot_degree = _hot_degree;
}

void CEatingRoleBasic::EatingSoup(float _food_score, float _sour_degree, float _hot_degree)
{
    m_food_score = _food_score;
    m_sour_degree = _sour_degree;
    m_hot_degree = _hot_degree;
}

void CEatingRoleBasic::Eating()
{
    if (m_food_score > 0) {
        m_animation_state = armature->getAnimation()->gotoAndPlay("eat");
        ++m_eat_times;
    }
}

void CEatingRoleBasic::Drinking()
{
    if (m_food_score > 0) {
        
    }
}

void CEatingRoleBasic::EatingSoup()
{
    if (m_food_score > 0) {
        
    }
}

//afterEating可能也要改
void CEatingRoleBasic::afterEating()
{
    if (m_eat_times > 5) {
        m_animation_state = armature->getAnimation()->gotoAndPlay("overeat");
        m_eat_times = 0;
        return;
    }
    m_eat_times = 0;
    if (m_food_score >= 80)
    {
        m_animation_state = armature->getAnimation()->gotoAndPlay("like02");
    }
    else if (m_food_score >= 60 && m_food_score < 80)
    {
        m_animation_state = armature->getAnimation()->gotoAndPlay("like01");
    }
    else if (m_food_score >= 40 && m_food_score < 60)
    {
        m_animation_state = armature->getAnimation()->gotoAndPlay("normal");
    }
    else if (m_food_score >= 20 && m_food_score < 40)
    {
        m_animation_state = armature->getAnimation()->gotoAndPlay("hate01");
    }
    else
    {
        m_animation_state = armature->getAnimation()->gotoAndPlay("hate02");
    }
}

void CEatingRoleBasic::playBetween()
{
    int _index = rand()%EATING_ROLE_ARMATURE_BETWEEN_NUM[roleID] + 1;
    if (_index == m_between_index) {
        _index = (_index + 1) % EATING_ROLE_ARMATURE_BETWEEN_NUM[roleID] + 1;
    }
    m_between_index = _index;
    
    char buf[32];
    sprintf(buf, "between0%d", m_between_index);
    m_animation_state = armature->getAnimation()->gotoAndPlay(buf);
}

void CEatingRoleBasic::Wait(bool is_dirty, CFood* food)
{
    if (is_dirty) {
        calcFoodScore();
        calcTasteScore();
    }
    
    if (m_animation_state->name == "Default" || m_animation_state->name == "want02" || m_animation_state->name == "between01" || m_animation_state->name == "between02" || m_animation_state->name == "between03" || m_animation_state->name == "between04" || m_animation_state->name == "between05" || m_animation_state->name == "between06")
    {
        m_animation_state = armature->getAnimation()->gotoAndPlay("want01");
    }
}

void CEatingRoleBasic::Want()
{
    //if (m_animation_state->name != "want02" && m_animation_state->name != "eat")
    if (m_animation_state->name == "want01")
    {
        //if (m_food_score > 0) {
        if (true) {
            m_animation_state = armature->getAnimation()->gotoAndPlay("want02");
        }
        else
        {
            //播拒绝的动画，应该只有猫和羊有这种特殊情况
        }
    }
}

void CEatingRoleBasic::Default()
{    
    m_change_to_default = true;
    //m_animation_state = armature->getAnimation()->gotoAndPlay("Default");
}


void CEatingRoleBasic::changeAnimation(float dt)
{
    m_animation_state = armature->getAnimation()->gotoAndPlay(m_animation_name);
}

void CEatingRoleBasic::calcFoodScore()
{
    if (m_food) {
        std::vector<int> _materials = m_food->getMaterials();
        for (int i = 0; i < _materials.size(); ++i) {
            m_food_score += EatingRoleData::getInstance()->getRoleMaterialScore(roleID, _materials.at(i));
        }
        m_food_score /= _materials.size();
    }
}

void CEatingRoleBasic::calcTasteScore()
{
    int _suan_tmp = 0;
    int _la_tmp = 0;
    if (m_food) {
        if (m_food->getTastes(TT_SUAN) > EatingRoleData::getInstance()->getRoleTasteBearScore(roleID, TT_SUAN)) {
            _suan_tmp = m_food->getTastes(TT_SUAN);
        }
        if (m_food->getTastes(TT_LA) > EatingRoleData::getInstance()->getRoleTasteBearScore(roleID, TT_LA)) {
            _la_tmp = m_food->getTastes(TT_LA);
        }
    }
    
    if (_suan_tmp == 0 && _la_tmp == 0) {
        m_taste = -1;
    }
    else if (_la_tmp > _suan_tmp) {
        m_taste = TT_LA;
    }
    else
    {
        m_taste = TT_SUAN;
    }
}