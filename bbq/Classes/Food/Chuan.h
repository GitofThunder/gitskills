#ifndef __CHUAN_H__
#define __CHUAN_H__

#include "cocos2d.h"
#include "Food.h"
#include "PRFilledPolygon.h"

class CChuan : public CFood
{
public:
    CChuan();
    virtual ~CChuan();
    CREATE_FUNC(CChuan);
    static CChuan* create(const char *pszFileName);
    virtual bool init();
    void myUpdate(float fEscapeTime);
    
private:
    
};

#endif // __FOOD_MATERIAL_H__
