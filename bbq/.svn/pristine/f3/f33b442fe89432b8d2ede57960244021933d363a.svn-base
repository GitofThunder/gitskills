//
//  BBQChoosingRole.h
//  TravelDemo
//
//  Created by kids on 15/9/7.
//
//

#ifndef __TravelDemo__BBQChoosingRole__
#define __TravelDemo__BBQChoosingRole__

#include <stdio.h>
#include "cocos2d.h"
#include "DBCCFactory.h"
USING_NS_CC;
USING_NS_DB;

class BBQChoosingRole : public Node
{
public:
    BBQChoosingRole();
    static BBQChoosingRole* create(int RoleID);
    bool init(int RoleID);
    
    //void setCollisionRect();
    
    bool isTouchHead(Touch* touch);
    
    void playAnimation(std::string animation);
    
    void eventHandler(EventCustom* event);
    
    int getRoleID();
    
private:
    DBCCArmatureNode* m_armature;
    Rect m_headRect;
    LayerColor* _layer_head;
    int m_roleID;
};

#endif /* defined(__TravelDemo__BBQChoosingRole__) */
