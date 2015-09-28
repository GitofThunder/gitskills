#include "Drink.h"

CDrink::CDrink()
{
    m_eFoodType = FT_ORIGIN;
}

CDrink::~CDrink()
{
    
}

CDrink* CDrink::create(const char *pszFileName)
{
    CDrink* pRet = new (std::nothrow) CDrink();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool CDrink::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    schedule(schedule_selector(CDrink::myUpdate));
    return true;
}

void CDrink::myUpdate(float fEscapeTime)
{
    
}

