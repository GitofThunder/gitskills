//
//  CEatingRoleBasic.h
//  TravelDemo
//
//  Created by kids on 15/8/24.
//
//

#ifndef __TravelDemo__CEatingRoleBasic__
#define __TravelDemo__CEatingRoleBasic__

#include <stdio.h>
#include "cocos2d.h"
#include "DragonBones.h"
#include "DBCCRenderHeaders.h"
#include "MacroVariable.h"
#include "GlobalData.h"
#include "EatingRoleData.h"
#include "Food.h"
USING_NS_CC;
USING_NS_DB;


//enum EATING_ROLE_STATE
//{
//    ERS_DEFAULT,     //人物的正常状态,没有食物被点击
//    ERS_WAIT,        //有食物被点击和拖动，但没有移动到人物嘴边的判定区域
//    ERS_WANT,        //有食物被点击并拖动到人物嘴边的判定区域，但没有结束touch事件，动画为张嘴
//    ERS_NOT_WANT,    //有食物被点击并拖动到人物嘴边的判定区域，但没有结束touch事件，动画为嫌弃不张嘴
//    ERS_EATING,      //吃东西
//    ERS_LIKE,        //吃了东西之后的表情，喜欢
//    ERS_LOVE,        //吃了东西之后的表情，很喜欢
//    ERS_NORMAL,      //吃了东西之后的表情，一般
//    ERS_HATE,        //吃了东西之后的表情，讨厌
//    ERS_BADLY_HATE,  //吃了东西之后的表情，很讨厌
//    ERS_SOUR,        //吃了东西之后的表情，酸
//    ERS_HOT,         //吃了东西之后的表情，辣
//    ERS_OVEREAT,     //吃了东西之后的表情，撑
//};

class CEatingRoleBasic : public Node
{
public:
    CREATE_FUNC(CEatingRoleBasic);
    CEatingRoleBasic();
    ~CEatingRoleBasic();
    
public:
    bool createArmature(int RoleID);
    bool createObject(int _RoleID);
    
    virtual void playAnimation(const char* pAniName);
    virtual void setCollisionRange();
    Rect getCollisionRange();
    
    virtual void eventHandler(EventCustom* event);
    
    bool checkTouchPoint(const Vec2& _touch);
    bool checkCollision(Rect rect);
    
    void initEyePos();
    
    bool onTouchBegan(Touch* _touch, Event* _event);
    void onTouchMoved(Touch* _touch, Event* _event);
    void onTouchEnded(Touch* _touch, Event* _event);
    
    void EyesReset(float dt);
    void BeginEyesMove(float dt);
    void EyesMove(float dt);
    
    int getRoleID();
    
    //赵剑加的角色吃东西的方法
    void Eating(float _food_score, float _sour_degree, float _hot_degree);
    void Drinking(float _food_score, float _sour_degree, float _hot_degree);
    void EatingSoup(float _food_score, float _sour_degree, float _hot_degree);
    
    void Eating();
    void Drinking();
    void EatingSoup();
    void afterEating();
    
    //用于计算食物的分数
    void calcFoodScore();
    //用于处理味道的逻辑
    void calcTasteScore();
    
    void playBetween();
    
    void Wait(bool is_dirty, CFood* food);
    void Want();
    void Default();
protected:
    DBCCArmatureNode* armature;
    int roleID;
    int roleState;
    Rect collisionRange;
    Rect armatureBox;
    EventListenerTouchOneByOne* _listener;
    
protected:
    //眼睛位置有关的数据
    float m_offset_y;
    Vec2 m_eyes_pos;
    float m_offset_length;
    Vec2 m_end_offset;
    
    //两个眼睛原件的情况下，第二个眼睛的相关数据
    Vec2 m_end_offset_extra;
    
    //以下是与人物状态有关的变量和函数
protected:
    int m_between_index;
    float m_food_score;
    float m_sour_degree;
    float m_hot_degree;
    AnimationState* m_animation_state;
    Touch* m_touch;
    bool m_first_flag;
    int _count_step;
    int m_eat_times;
    bool m_change_to_default;
    //新添加的东西，之后m_food_score，m_sour_degree，m_hot_degree这三个函数在吃东西的接口修改之后就应该删除不用了,m_food_score要用，酸和辣等口味需要一个变量来保存。
    CFood* m_food;
    int m_taste;
    
    //眼睛的名字
    std::string m_eye_name;
    std::string m_eye_name_extra;
    
    //需要播放的动画的名称  测试
    std::string m_animation_name;
    void changeAnimation(float dt);
    Rect m_openMouse_collision;
public:
    bool checkOpenMouse(Rect _rect);
};



#endif /* defined(__TravelDemo__CEatingRoleBasic__) */
