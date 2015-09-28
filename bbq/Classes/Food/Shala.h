#ifndef __SHALA_H__
#define __SHALA_H__

#include "cocos2d.h"
#include "Food.h"
#include "PRFilledPolygon.h"

class CShala : public CFood
{
public:
    CShala();
    virtual ~CShala();
    CREATE_FUNC(CShala);
    static CShala* create(const char *pszFileName);
    virtual bool init();
    void myUpdate(float fEscapeTime);
    
private:
    
};

#endif // __SHALA_H__
