#ifndef __GUEST_H__
#define __GUEST_H__

#include "cocos2d.h"
#include "DragonBones.h"
#include "DBCCRenderHeaders.h"

USING_NS_CC;
USING_NS_DB;

class CGuest : public Layer
{
public:
    CGuest();
    virtual ~CGuest();
    CREATE_FUNC(CGuest);
    virtual bool init();
    
    
private:
    DBCCArmatureNode* armature;		//动画动作
};

#endif
