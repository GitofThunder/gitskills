//
//  TestArmatrue.h
//  TravelDemo
//
//  Created by kids on 15/8/31.
//
//

#ifndef __TravelDemo__TestArmatrue__
#define __TravelDemo__TestArmatrue__

#include <stdio.h>
#include "cocos2d.h"
#include "DragonBones.h"
#include "DBCCRenderHeaders.h"
#include "MacroVariable.h"
#include "GlobalData.h"
USING_NS_CC;
USING_NS_DB;

class CTestChageLayer : public Layer
{
public:
    static Scene* createScene();
    CREATE_FUNC(CTestChageLayer);
    bool init();
    
    bool onTouchBegan(Touch* touch, Event* unusedevent);
    void onTouchMoved(Touch* touch, Event* unusedevent);
    void onTouchEnded(Touch* touch, Event* unusedevent);
    
    void changeAnimation(float dt);
    void eventHandler(EventCustom* event);
    
    void addcsb();
private:
    DBCCArmatureNode* armature;
    bool m_flag;
    
    Node* m_node;
    Node* m_tmp;
};

#endif /* defined(__TravelDemo__TestArmatrue__) */
