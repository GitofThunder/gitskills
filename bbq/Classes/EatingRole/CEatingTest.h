//
//  CEatingTest.h
//  TravelDemo
//
//  Created by kids on 15/8/24.
//
//

#ifndef __TravelDemo__CEatingTest__
#define __TravelDemo__CEatingTest__

#include <stdio.h>
#include "cocos2d.h"
#include "GlobalData.h"
#include "CEatingRoleBasic.h"
#include "Food.h"
USING_NS_CC;

class CEatingTest : public Layer
{
public:
    CREATE_FUNC(CEatingTest);
    bool init();
    static Scene* createScene();
    
    void addTouch();
    bool onTouchBegan(Touch* _touch, Event* _event);
    void onTouchMoved(Touch* _touch, Event* _event);
    void onTouchEnded(Touch* _touch, Event* _event);
    void addRole();
    
    void addFood();
    void FoodPositionUpdate(float dt);
    
    void addButton();
    void ButtonCallBack(Ref* ref);

private:
    Vector<CEatingRoleBasic*> m_testRoles;
    CEatingRoleBasic* _testRole;
    
    Touch* m_touch;  //用于在测试里代表食物
    Vector<CFood*> m_foods;   //这里要换成Food类，而不是Sprite
    CFood* m_tmp_food;
    Vec2 m_tmp_food_begin_pos;
    
    int m_last_index;
    
    //测试
    void delay(float dt);
    bool m_touch_enable;
};

#endif /* defined(__TravelDemo__CEatingTest__) */
