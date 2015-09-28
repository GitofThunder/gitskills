#ifndef __DRINK_H__
#define __DRINK_H__

#include "cocos2d.h"
#include "Food.h"
#include "PRFilledPolygon.h"

class CDrink : public CFood
{
public:
    CDrink();
    virtual ~CDrink();
    CREATE_FUNC(CDrink);
    static CDrink* create(const char *pszFileName);
    virtual bool init();
    void myUpdate(float fEscapeTime);
    
private:
    
};

#endif // __DRINK_H__
